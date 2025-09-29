#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

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
std::vector< std::vector< uint8_t > > split_sections(
    const std::vector< uint8_t >& file )
{
    std::vector< std::vector< uint8_t > > sections;
    const uint8_t sep[4] = { 0x1c, 0x1c, 0x1c, 0x1c };

    size_t start = 0;
    for ( ;; )
    {
        size_t i = start;
        bool found = false;
        for ( ; i + 4 <= file.size(); ++i )
        {
            if ( memcmp( &file[i], sep, 4 ) == 0 )
            {
                found = true;
                break;
            }
        }
        if ( !found )
        {
            if ( start < file.size() )
                sections.emplace_back( file.begin() + start, file.end() );
            break;
        }
        sections.emplace_back( file.begin() + start, file.begin() + i );
        start = i + 4;
    }

    // remove last if empty
    if ( !sections.empty() && sections.back().empty() ) sections.pop_back();
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
    char buf[64];
    if ( type == "u8" )
    {
        uint8_t v = read_le< uint8_t >( ptr );
        std::snprintf( buf, sizeof( buf ), "%u", (unsigned)v );
        return std::string( buf );
    }
    if ( type == "u16" )
    {
        uint16_t v = read_le< uint16_t >( ptr );
        std::snprintf( buf, sizeof( buf ), "%u", (unsigned)v );
        return std::string( buf );
    }
    if ( type == "u32" )
    {
        uint32_t v = read_le< uint32_t >( ptr );
        std::snprintf( buf, sizeof( buf ), "%u", (unsigned)v );
        return std::string( buf );
    }
    if ( type == "s8" )
    {
        int8_t v = read_le< int8_t >( ptr );
        std::snprintf( buf, sizeof( buf ), "%d", (int)v );
        return std::string( buf );
    }
    if ( type == "s16" )
    {
        int16_t v = read_le< int16_t >( ptr );
        std::snprintf( buf, sizeof( buf ), "%d", (int)v );
        return std::string( buf );
    }
    if ( type == "s32" )
    {
        int32_t v = read_le< int32_t >( ptr );
        std::snprintf( buf, sizeof( buf ), "%d", (int)v );
        return std::string( buf );
    }
    if ( type == "float" )
    {
        float v = read_le< float >( ptr );
        std::snprintf( buf, sizeof( buf ), "%g", (double)v );
        return std::string( buf );
    }
    if ( type == "double" )
    {
        double v = read_le< double >( ptr );
        std::snprintf( buf, sizeof( buf ), "%g", v );
        return std::string( buf );
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
    std::ifstream ifs( infile, std::ios::binary );
    std::vector< uint8_t > fileBytes{ std::istreambuf_iterator< char >( ifs ),
                                      std::istreambuf_iterator< char >() };

    auto sections = split_sections( fileBytes );
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
        // search for start "$ " (0x24 0x20)
        size_t start = std::string::npos;
        for ( size_t i = 0; i + 2 <= fileBytes.size(); ++i )
        {
            if ( fileBytes[i] == 0x24 && fileBytes[i + 1] == 0x20 )
            {
                start = i;
                break;
            }
        }
        if ( start == std::string::npos )
        {
            std::cerr << "Warning: '$ ' not found in file; using first section "
                         "as header\n";
            headerText.assign( sections[0].begin(), sections[0].end() );
        } else {
            const uint8_t term5[5] = { 0x5C, 0x1C, 0x1C, 0x1C, 0x1C };
            size_t termPos = std::string::npos;
            for ( size_t i = start; i + 5 <= fileBytes.size(); ++i )
            {
                if ( memcmp( &fileBytes[i], term5, 5 ) == 0 )
                {
                    termPos = i;
                    break;
                }
            }
            if ( termPos == std::string::npos )
            {
                // fallback: first backslash after start
                for ( size_t i = start; i < fileBytes.size(); ++i )
                {
                    if ( fileBytes[i] == 0x5C )
                    {
                        termPos = i;
                        break;
                    }
                }
            }
            size_t endExclusive = ( termPos == std::string::npos )
                                      ? fileBytes.size()
                                      : ( termPos + 1 );
            headerText.assign( (const char*)fileBytes.data() + start,
                               (const char*)fileBytes.data() + endExclusive );
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
        auto& sec = sections[si];
        if ( sec.size() < 6 )
        {
            corrupt++;
            continue;
        }
        // checksum is last byte (XOR of all previous bytes)
        uint8_t cs = 0;
        for ( size_t i = 0; i + 1 < sec.size(); ++i )
            cs ^= sec[i];
        if ( cs != sec.back() )
        {
            corrupt++;
            continue;
        }

        // payload excludes last checksum byte
        if ( sec.size() < 5 )
        {
            corrupt++;
            continue;
        }
        const uint8_t* payload = sec.data();
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

        size_t payload_len = sec.size() - 1 - 4;  // remove checksum and id
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
