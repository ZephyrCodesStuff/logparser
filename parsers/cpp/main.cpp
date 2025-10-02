#include <algorithm>
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

#include "mmap.hpp"
#include "parallelism.hpp"

using namespace antlr4;
namespace fs = std::filesystem;

#define TEMP_PATH ".JOIN_TEMP"
#define KEEP_JOINED_FILES 0

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
        } catch ( const std::exception& )
        {
            dev.id = 0;
        }

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
std::vector< Section > split_sections( const uint8_t* data, size_t size )
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
            i += 3;  // skip separator bytes
        }
    }
    if ( start < size ) sections.push_back( { start, size - start } );

    return sections;
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

bool has_header( const std::string& path )
{
    std::ifstream file( path, std::ios::in );
    if ( !file.is_open() )
    {
        std::cerr << "Failed to open file: " << path << "\n";
        return false;
    }

    char c;
    if ( file.get( c ) ) return c == '$';

    return false;
}

bool join_files( std::vector< std::string > files,
                 const std::string& outputPath )
{
    std::cout << "Joining File " << outputPath << std::endl;
    std::ofstream out( outputPath, std::ios::binary );
    if ( !out.is_open() )
    {
        std::cerr << "Failed to open output file: " << outputPath << "\n";
        return false;
    }

    for ( const auto& file : files )
    {
        std::ifstream in( file, std::ios::binary );
        if ( !in.is_open() )
        {
            std::cerr << "Failed to open input file: " << file << "\n";
            return false;
        }

        out << in.rdbuf();
    }

    return true;
}

bool join_files_batch( std::vector< std::string > files,
                       const std::string& outputFolderPath )
{
    sort( files.begin(), files.end() );

    std::vector< std::string > fileList;
    int fileIndex = 0;
    for ( std::string x : files )
    {
        if ( has_header( x ) )
        {
            if ( fileList.size() > 0 )
            {
                join_files(
                    fileList,
                    ( fs::path( outputFolderPath ) /
                      fs::path( "outputBIN" + std::to_string( fileIndex++ ) +
                                ".bin" ) )
                        .string() );
                fileList.clear();
            }
        }

        fileList.push_back( x );
    }

    if ( fileList.size() > 0 )
    {
        join_files(
            fileList,
            ( fs::path( outputFolderPath ) /
              fs::path( "outputBIN" + std::to_string( fileIndex ) + ".bin" ) )
                .string() );
    }
    return true;
}

bool parse_file_into_csv( fs::path infile, fs::path outdir )
{
    if ( !fs::exists( infile ) )
    {
        std::cerr << "File not found: " << infile << std::endl;
        return 2;
    }

    // read file into memory
    MappedFile mappedFile( infile );
    size_t fileSize = mappedFile.size();

    // make sure file starts with magic `$`
    // TODO: merge with previous log files -- this is usually a segment of a larger file
    if ( fileSize < 2 || mappedFile.data()[0] != '$' )
    {
        std::cerr << "Invalid magic: " << infile << std::endl;
        return 2;
    }

    // use memory-mapped buffer to find sections
    auto sections = split_sections( mappedFile.data(), fileSize );
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
        const uint8_t startSeq[2] = { 0x24, 0x20 };  // "$ "
        const uint8_t term5[5] = { 0x5C, 0x1C, 0x1C, 0x1C, 0x1C };

        // find start using std::search (single pass helpers)
        auto itStart =
            std::search( mappedFile.data(), mappedFile.data() + fileSize,
                         std::begin( startSeq ), std::end( startSeq ) );
        if ( itStart == mappedFile.data() + fileSize )
        {
            std::cerr << "Warning: '$ ' not found in file; using first section "
                         "as header\n";
            headerText.assign(
                (const char*)mappedFile.data() + sections[0].offset,
                (const char*)mappedFile.data() + sections[0].offset +
                    sections[0].length );
        } else {
            // try to find the preferred 5-byte terminator after start
            auto itTerm = std::search( itStart, mappedFile.data() + fileSize,
                                       std::begin( term5 ), std::end( term5 ) );
            if ( itTerm != mappedFile.data() + fileSize )
            {
                // include the terminating backslash (first byte of term5)
                headerText.assign(
                    reinterpret_cast< const char* >( &*itStart ),
                    reinterpret_cast< const char* >( &*itTerm ) + 1 );
            } else {
                // fallback: first backslash after start
                auto itBack =
                    std::find( itStart, mappedFile.data() + fileSize, 0x5C );
                const char* endPtr =
                    ( itBack == mappedFile.data() + fileSize )
                        ? reinterpret_cast< const char* >( mappedFile.data() +
                                                           fileSize )
                        : reinterpret_cast< const char* >( &*itBack ) + 1;
                headerText.assign( reinterpret_cast< const char* >( &*itStart ),
                                   endPtr );
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

    // Convert memory-mapped file to vector for parallel processing
    std::vector< uint8_t > fileBytesVec(
        mappedFile.data(), mappedFile.data() + mappedFile.size() );

    // Use optimized parallel processing
    process_sections_parallel( fileBytesVec, sections, devices, id2idx );

    // write CSV per device
    for ( const auto& dev : devices )
        write_csv_for_device( dev, outdir );

    return true;
}

int main( int argc, const char* argv[] )
{
    if ( argc < 3 )
    {
        std::cerr << "Usage: " << argv[0] << " <inputPath> [outputPath] *flags"
                  << std::endl;
        return 1;
    }
    std::string inputPath = argv[1], outputPath = argv[2];

    bool joinMode = false, multiMode = false;
    if ( argc > 3 )
    {
        for ( int i = 3; i < argc; i++ )
        {
            if ( argv[i][0] != '-' || strlen( argv[i] ) < 2 )
            {
                std::cerr << "Usage: " << argv[0]
                          << " <inputPath> [outputPath] *flags" << std::endl;
                return 1;
            }

            switch ( argv[i][1] )
            {
                case 'j':
                    joinMode = true;
                    break;
                case 'm':
                    multiMode = true;
                    break;
                default:
                    std::cerr << "Unknown Flag " << argv[i][1] << std::endl;
                    return 1;
            }
        }
    }

    if ( joinMode )
    {
        multiMode = true;

        if ( !fs::exists( inputPath ) || !fs::is_directory( inputPath ) )
        {
            std::cerr << "Join Folder not found: " << inputPath << std::endl;
            return 2;
        }

        if ( fs::exists( TEMP_PATH ) && fs::is_directory( TEMP_PATH ) )
            fs::remove_all( TEMP_PATH );

        fs::create_directory( TEMP_PATH );

        std::vector< std::string > files;

        for ( const auto& entry :
              std::filesystem::directory_iterator( inputPath ) )
        {
            if ( std::filesystem::is_regular_file( entry.status() ) )
                files.push_back( entry.path().string() );
        }

        for ( fs::path s : files )
        {
            if ( s.extension() != ".bin" && s.extension() != ".BIN" )
            {
                std::cerr << "Invalid Binary File : " << s.string()
                          << std::endl;
                return 2;
            }
        }

        join_files_batch( files, TEMP_PATH );

        inputPath = TEMP_PATH;
    }

    if ( multiMode )
    {
        if ( !fs::exists( inputPath ) || !fs::is_directory( inputPath ) )
        {
            std::cerr << "Input Folder not found: " << inputPath << std::endl;
            return 2;
        }

        if ( !fs::exists( outputPath ) ) fs::create_directory( outputPath );

        std::vector< std::string > files;

        for ( const auto& entry :
              std::filesystem::directory_iterator( inputPath ) )
        {
            if ( std::filesystem::is_regular_file( entry.status() ) )
                files.push_back( entry.path().string() );
        }

        for ( fs::path s : files )
        {
            if ( s.extension() != ".bin" && s.extension() != ".BIN" )
            {
                std::cerr << "Invalid Binary File : " << s.string()
                          << std::endl;
                return 2;
            }
        }

        unsigned int fileCount = 0;
        for ( std::string s : files )
        {
            parse_file_into_csv(
                fs::path( s ),
                fs::path( outputPath ) /
                    fs::path( "outputBIN" + std::to_string( fileCount++ ) ) );
        }
    } else {
        parse_file_into_csv( fs::path( inputPath ), fs::path( outputPath ) );
    }

    return 0;
}
