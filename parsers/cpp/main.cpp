#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "SensorLogLexer.h"
#include "SensorLogParser.h"

using namespace antlr4;
namespace fs = std::filesystem;

size_t typename_to_size( const std::string& type )
{
    if ( type == "s8" || type == "u8" ) return 1;
    if ( type == "s16" || type == "u16" ) return 2;
    if ( type == "s32" || type == "u32" ) return 4;
    if ( type == "s64" || type == "u64" ) return 8;
    if ( type == "float" ) return sizeof( float );
    if ( type == "double" ) return sizeof( double );
    return 0;
}

struct Field {
    std::string name;
    std::string type;
    std::string unit;
    std::vector< std::string > data;  // store as strings for simple CSV output
};

struct Device {
    std::string name;
    uint32_t id;
    std::vector< Field > fields;
};

struct Section {
    size_t offset;
    size_t length;
};

// Build Content map from the parsed ANTLR FileContext
std::vector< Device > build_content_from_ast(
    logfile::SensorLogParser::FileContext* fileCtx )
{
    std::vector< Device > devices;

    auto devDefs = fileCtx->deviceDefinitions();
    if ( !devDefs ) return devices;

    for ( auto devDefCtx : devDefs->deviceDefinition() )
    {
        auto devContent = devDefCtx->deviceContent();
        if ( !devContent ) continue;

        Device dev;
        dev.name = devContent->deviceName()->getText();

        // device id is a DEVICE_ID_NUMBER token; parse as hex
        std::string idText =
            devContent->deviceId()->DEVICE_ID_NUMBER()->getText();
        try
        {
            dev.id =
                static_cast< uint32_t >( std::stoul( idText, nullptr, 16 ) );
        } catch ( const std::exception& ) { dev.id = 0; }

        for ( auto sensorCtx : devContent->sensorDefinition() )
        {
            Field f;
            f.name = sensorCtx->sensorName()->getText();
            f.type = sensorCtx->dataType()->getText();
            f.unit = sensorCtx->unitOfMeasurement()->getText();
            dev.fields.push_back( std::move( f ) );
        }

        devices.push_back( std::move( dev ) );
    }

    return devices;
}

// Split file bytes into sections separated by 0x1c1c1c1c
std::vector< Section > split_sections(
    const uint8_t* data, size_t size )
{
    std::vector< Section > sections;
    const uint8_t sep[4] = { 0x1c, 0x1c, 0x1c, 0x1c };

    size_t start = 0;
    for ( size_t i = 0; i + 4 <= size; ++i )
    {
        if ( std::memcmp( &data[i], sep, 4 ) == 0 )
        {
            sections.push_back( { start, i - start } );
            start = i + 4;
            i += 3; // skip separator bytes
        }
    }
    if ( start < size )
        sections.push_back( { start, size - start } );

    return sections;
}

// helper to read little-endian integers/floats safely
template < typename T >
T read_le( const uint8_t* ptr )
{
    T v;
    std::memcpy( &v, ptr, sizeof( T ) );
    return v;
}

// compute entry size for a device
size_t calc_entry_size( const Device& dev )
{
    size_t s = 0;
    for ( const auto& f : dev.fields )
        s += typename_to_size( f.type );
    return s;
}

// convert field value at byte buffer to string according to type
std::string read_field_as_string( const uint8_t* ptr, const std::string& type )
{
    if ( type == "u8" )
    {
        uint8_t v = read_le< uint8_t >( ptr );
        return std::to_string( static_cast<unsigned>( v ) );
    }
    if ( type == "u16" )
    {
        uint16_t v = read_le< uint16_t >( ptr );
        return std::to_string( static_cast<unsigned>( v ) );
    }
    if ( type == "u32" )
    {
        uint32_t v = read_le< uint32_t >( ptr );
        return std::to_string( static_cast<unsigned long long>( v ) );
    }
    if ( type == "u64" )
    {
        uint64_t v = read_le< uint64_t >( ptr );
        return std::to_string( static_cast<unsigned long long>( v ) );
    }
    if ( type == "s8" )
    {
        int8_t v = read_le< int8_t >( ptr );
        return std::to_string( static_cast<int>( v ) );
    }
    if ( type == "s16" )
    {
        int16_t v = read_le< int16_t >( ptr );
        return std::to_string( static_cast<int>( v ) );
    }
    if ( type == "s32" )
    {
        int32_t v = read_le< int32_t >( ptr );
        return std::to_string( static_cast<long long>( v ) );
    }
    if ( type == "s64" )
    {
        int64_t v = read_le< int64_t >( ptr );
        return std::to_string( static_cast<long long>( v ) );
    }
    if ( type == "float" )
    {
        float v = read_le< float >( ptr );
        return std::to_string( v );
    }
    if ( type == "double" )
    {
        double v = read_le< double >( ptr );
        return std::to_string( v );
    }
    return std::string();
}

void write_csv_for_device( const Device& dev, const fs::path& outdir )
{
    if ( dev.fields.empty() ) return;
    std::string filename = dev.name;
    for ( auto& c : filename )
        if ( c == ' ' ) c = '_';
    fs::path p = outdir / ( filename + ".csv" );
    std::ofstream ofs( p );
    if ( !ofs.is_open() )
    {
        std::cerr << "Failed to open " << p << " for writing\n";
        return;
    }

    // titles
    for ( size_t i = 0; i < dev.fields.size(); ++i )
    {
        ofs << dev.fields[i].name << " [" << dev.fields[i].unit << "]";
        if ( i + 1 < dev.fields.size() ) ofs << ',';
    }
    ofs << '\n';

    // number of rows: min size among fields
    size_t rows = dev.fields.front().data.size();
    for ( const auto& f : dev.fields )
        rows = std::max( rows, f.data.size() );

    for ( size_t r = 0; r < rows; ++r )
    {
        for ( size_t c = 0; c < dev.fields.size(); ++c )
        {
            const auto& vec = dev.fields[c].data;
            if ( r < vec.size() ) ofs << vec[r];
            if ( c + 1 < dev.fields.size() ) ofs << ',';
        }
        ofs << '\n';
    }

    ofs.close();
    std::cout << "Wrote " << p << " (" << rows << " rows)\n";
}

#ifdef _WIN32
#  include <windows.h>
#else
#  include <sys/mman.h>
#  include <sys/stat.h>
#  include <fcntl.h>
#  include <unistd.h>
#endif

// Simple RAII wrapper for a read-only memory-mapped file
class MappedFile {
public:
    MappedFile(const fs::path& path) : map_(nullptr), size_(0)
    {
        std::string p = path.string();
#ifdef _WIN32
        HANDLE h = CreateFileA(p.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (h == INVALID_HANDLE_VALUE) throw std::runtime_error("Failed to open file");
        LARGE_INTEGER li;
        if (!GetFileSizeEx(h, &li)) { CloseHandle(h); throw std::runtime_error("Failed to stat file"); }
        size_ = static_cast<size_t>(li.QuadPart);
        HANDLE fm = CreateFileMappingA(h, NULL, PAGE_READONLY, 0, 0, NULL);
        if (!fm) { CloseHandle(h); throw std::runtime_error("CreateFileMapping failed"); }
        map_ = MapViewOfFile(fm, FILE_MAP_READ, 0, 0, 0);
        CloseHandle(fm);
        CloseHandle(h);
        if (!map_ && size_ > 0) throw std::runtime_error("MapViewOfFile failed");
#else
        int fd = open(p.c_str(), O_RDONLY);
        if (fd < 0) throw std::runtime_error("Failed to open file");
        struct stat st;
        if (fstat(fd, &st) != 0) { close(fd); throw std::runtime_error("fstat failed"); }
        size_ = static_cast<size_t>(st.st_size);
        if (size_ > 0) {
            map_ = mmap(nullptr, size_, PROT_READ, MAP_PRIVATE, fd, 0);
            if (map_ == MAP_FAILED) { close(fd); throw std::runtime_error("mmap failed"); }
        } else {
            map_ = nullptr;
        }
        close(fd);
#endif
    }

    ~MappedFile()
    {
#ifdef _WIN32
        if (map_) UnmapViewOfFile(map_);
#else
        if (map_) munmap(map_, size_);
#endif
    }

    const uint8_t* data() const { return static_cast<const uint8_t*>(map_); }
    size_t size() const { return size_; }

private:
    void* map_;
    size_t size_;
};

int main( int argc, const char* argv[] )
{
    if ( argc < 2 )
    {
        std::cerr << "Usage: " << argv[0] << " <file> [outdir]" << std::endl;
        return 1;
    }

    fs::path infile = argv[1];
    fs::path outdir = ( argc >= 3 ) ? fs::path( argv[2] ) : fs::current_path();
    if ( !fs::exists( infile ) )
    {
        std::cerr << "File not found: " << infile << std::endl;
        return 2;
    }

    // read file into memory
    MappedFile mappedFile(infile);
    const uint8_t* fileBytes = mappedFile.data();
    size_t fileSize = mappedFile.size();

    // make sure file starts with magic `$`
    // TODO: merge with previous log files -- this is usually a segment of a larger file
    if ( fileSize < 2 || fileBytes[0] != '$' )
    {
        std::cerr << "Invalid magic: " << infile << std::endl;
        return 2;
    }

    // use memory-mapped buffer to find sections
    auto sections = split_sections( fileBytes, fileSize );
    if ( sections.empty() )
    {
        std::cerr << "No sections found in file" << std::endl;
        return 3;
    }

    // Extract header: search entire file for the ASCII header start "$ " and
    // the terminating backslash (prefer the 5-byte sequence 0x5C 0x1C 0x1C 0x1C 0x1C).
    std::string headerText;
    try
    {
        const uint8_t startSeq[2] = { 0x24, 0x20 }; // "$ "
        const uint8_t term5[5] = { 0x5C, 0x1C, 0x1C, 0x1C, 0x1C };

        // find start using std::search (single pass helpers)
        auto itStart = std::search(fileBytes, fileBytes + fileSize, std::begin(startSeq), std::end(startSeq));
        if ( itStart == fileBytes + fileSize )
        {
            std::cerr << "Warning: '$ ' not found in file; using first section as header\n";
            headerText.assign( (const char*)fileBytes + sections[0].offset,
                               (const char*)fileBytes + sections[0].offset + sections[0].length );
        }
        else
        {
            // try to find the preferred 5-byte terminator after start
            auto itTerm = std::search(itStart, fileBytes + fileSize, std::begin(term5), std::end(term5));
            if ( itTerm != fileBytes + fileSize )
            {
                // include the terminating backslash (first byte of term5)
                headerText.assign( reinterpret_cast<const char*>(&*itStart), reinterpret_cast<const char*>(&*itTerm) + 1 );
            }
            else
            {
                // fallback: first backslash after start
                auto itBack = std::find(itStart, fileBytes + fileSize, 0x5C);
                const char* endPtr = (itBack == fileBytes + fileSize) ? reinterpret_cast<const char*>(fileBytes + fileSize) : reinterpret_cast<const char*>(&*itBack) + 1;
                headerText.assign( reinterpret_cast<const char*>(&*itStart), endPtr );
            }
        }
    } catch ( const std::exception& ex )
    {
        std::cerr << "Failed to extract header: " << ex.what() << std::endl;
        return 4;
    }

    ANTLRInputStream input( headerText );
    logfile::SensorLogLexer lexer( &input );
    CommonTokenStream tokens( &lexer );
    logfile::SensorLogParser parser( &tokens );

    auto fileCtx = parser.file();
    auto devices = build_content_from_ast( fileCtx );

    // map id -> device index
    std::unordered_map< uint32_t, size_t > id2idx;
    for ( size_t i = 0; i < devices.size(); ++i )
        id2idx[devices[i].id] = i;

    // ensure outdir exists
    if ( !fs::exists( outdir ) ) fs::create_directories( outdir );

    size_t corrupt = 0;
    // parse data sections
    for ( size_t si = 1; si < sections.size(); ++si )
    {
        const auto& secInfo = sections[si];
        const uint8_t* secPtr = fileBytes + secInfo.offset;
        size_t secSize = secInfo.length;

        // each section must be at least 5 bytes (4-byte id + 1-byte checksum)
        if ( secSize < 5 )
        {
            corrupt++;
            continue;
        }

        // checksum is last byte (XOR of all previous bytes)
        uint8_t cs = 0;
        for ( size_t i = 0; i + 1 < secSize; ++i )
            cs ^= secPtr[i];
        if ( cs != secPtr[secSize - 1] )
        {
            corrupt++;
            continue;
        }

        // payload excludes last checksum byte
        if ( secSize < 5 )
        {
            corrupt++;
            continue;
        }
        const uint8_t* payload = secPtr;
        uint32_t id = read_le< uint32_t >( payload );
        // find device
        auto it = id2idx.find( id );
        if ( it == id2idx.end() )
        {
            // std::cerr << "Unknown ID: " << std::hex << id << std::dec << "\n";
            continue;
        }
        Device& dev = devices[it->second];
        size_t entrySize = calc_entry_size( dev );
        if ( entrySize == 0 ) continue;

        size_t payload_len = secSize - 1 - 4;  // remove checksum and id
        size_t num_entries = payload_len / entrySize;
        const uint8_t* cursor = payload + 4;

        for ( size_t e = 0; e < num_entries; ++e )
        {
            size_t off = e * entrySize;
            const uint8_t* p = cursor + off;
            for ( size_t f = 0; f < dev.fields.size(); ++f )
            {
                const auto& ftype = dev.fields[f].type;
                std::string val = read_field_as_string( p, ftype );
                dev.fields[f].data.push_back( val );
                p += typename_to_size( ftype );
            }
        }
    }

    std::cout << "Parsing done. Corrupt sections: " << corrupt << "\n";

    // write CSV per device
    for ( const auto& dev : devices )
        write_csv_for_device( dev, outdir );

    return 0;
}
