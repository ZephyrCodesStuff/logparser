#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "SensorLogLexer.h"
#include "SensorLogParser.h"

#include "mmap.hpp"
#include "parallelism.hpp"

using namespace antlr4;
namespace fs = std::filesystem;

constexpr const std::array< char, 2 > MAGIC = { '$', ' ' };
constexpr const char PAD_START = '\\';
constexpr const char PAD_ALIGN = 0x1C;
constexpr const char* FILENAME_REGEX = R"(LOG(\d{4}))";

// Build Content map from the parsed ANTLR FileContext
std::vector< Device > build_content_from_ast(
    logfile::SensorLogParser::FileContext* fileCtx )
{
    std::vector< Device > devices;

    auto* devDefs = fileCtx->deviceDefinitions();
    if ( devDefs == nullptr )
    {
        return devices;
    }

    for ( auto* devDefCtx : devDefs->deviceDefinition() )
    {
        auto* devContent = devDefCtx->deviceContent();
        if ( devContent == nullptr )
        {
            continue;
        }

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

        for ( auto* sensorCtx : devContent->sensorDefinition() )
        {
            Field field;
            field.name = sensorCtx->sensorName()->getText();
            field.type = sensorCtx->dataType()->getText();
            field.unit = sensorCtx->unitOfMeasurement()->getText();
            dev.fields.push_back( std::move( field ) );
        }

        devices.push_back( std::move( dev ) );
    }

    return devices;
}

// Split file bytes into sections separated by 0x1c1c1c1c
std::vector< Section > split_sections( const uint8_t* data, size_t size )
{
    std::vector< Section > sections;
    std::array< uint8_t, 4 > sep = { PAD_ALIGN, PAD_ALIGN, PAD_ALIGN,
                                     PAD_ALIGN };

    size_t start = 0;
    for ( size_t i = 0; i + 4 <= size; ++i )
    {
        if ( std::memcmp( &data[i], sep.data(), 4 ) == 0 )
        {
            sections.push_back( { start, i - start } );
            start = i + 4;
            i += 3;  // skip separator bytes
        }
    }
    if ( start < size )
    {
        sections.push_back( { start, size - start } );
    }

    return sections;
}

void write_csv_for_device( const Device& dev, const fs::path& outdir )
{
    if ( dev.fields.empty() )
    {
        return;
    }
    std::string filename = dev.name;
    std::replace( filename.begin(), filename.end(), ' ', '_' );

    fs::path csv_output_path = outdir / ( filename + ".csv" );
    std::ofstream ofs( csv_output_path );
    if ( !ofs.is_open() )
    {
        std::cerr << "Failed to open " << csv_output_path << " for writing\n";
        return;
    }

    // titles
    for ( size_t i = 0; i < dev.fields.size(); ++i )
    {
        ofs << dev.fields[i].name << " [" << dev.fields[i].unit << "]";
        if ( i + 1 < dev.fields.size() )
        {
            ofs << ',';
        }
    }
    ofs << '\n';

    // number of rows: min size among fields
    size_t rows = dev.fields.front().data.size();
    for ( const auto& field : dev.fields )
    {
        rows = std::max( rows, field.data.size() );
    }

    for ( size_t row = 0; row < rows; ++row )
    {
        for ( size_t col = 0; col < dev.fields.size(); ++col )
        {
            const auto& vec = dev.fields[col].data;
            if ( row < vec.size() )
            {
                ofs << vec[row];
            }
            if ( col + 1 < dev.fields.size() )
            {
                ofs << ',';
            }
        }
        ofs << '\n';
    }

    ofs.close();
    std::cout << "Wrote " << csv_output_path << " (" << rows << " rows)\n";
}

bool has_header( const std::string& path )
{
    std::ifstream file( path, std::ios::in );
    if ( !file.is_open() )
    {
        std::cerr << "Failed to open file: " << path << "\n";
        return false;
    }

    std::array< char, 2 > file_magic{};
    if ( !file.get( file_magic[0] ) || !file.get( file_magic[1] ) )
    {
        std::cerr << "Failed to read from file: " << path << "\n";
        return false;
    }

    return file_magic == MAGIC;
}

// Parse a memory buffer (concatenated files) into CSV output directory
bool parse_buffer_into_csv( const uint8_t* data, size_t fileSize,
                            const fs::path& outdir )
{
    // make sure file starts with magic `$`
    if ( fileSize < 2 || data[0] != MAGIC[0] || data[1] != MAGIC[1] )
    {
        std::cerr << "Invalid magic in buffer\n";
        return false;
    }

    // use memory buffer to find sections
    auto sections = split_sections( data, fileSize );
    if ( sections.empty() )
    {
        std::cerr << "No sections found in buffer\n";
        return false;
    }

    // Extract header: search entire buffer for the ASCII header start "$ " and
    // the terminating backslash (prefer the 5-byte sequence 0x5C 0x1C 0x1C 0x1C 0x1C).
    std::string headerText;
    try
    {
        const std::array< uint8_t, 2 > startSeq = { 0x24, 0x20 };  // "$ "
        const std::array< uint8_t, 5 > term5 = {
            PAD_START, PAD_ALIGN, PAD_ALIGN, PAD_ALIGN, PAD_ALIGN };

        // find start using std::search (single pass helpers)
        const auto* itStart =
            std::search( data, data + fileSize, std::begin( startSeq ),
                         std::end( startSeq ) );
        if ( itStart == data + fileSize )
        {
            std::cerr << "Warning: '$ ' not found in buffer; using first "
                         "section as header\n";
            headerText.assign(
                (const char*)data + sections[0].offset,
                (const char*)data + sections[0].offset + sections[0].length );
        } else
        {
            // try to find the preferred 5-byte terminator after start
            auto itTerm = std::search( itStart, data + fileSize,
                                       std::begin( term5 ), std::end( term5 ) );
            if ( itTerm != data + fileSize )
            {
                // include the terminating backslash (first byte of term5)
                headerText.assign(
                    reinterpret_cast< const char* >( &*itStart ),
                    reinterpret_cast< const char* >( &*itTerm ) + 1 );
            } else
            {
                // fallback: first backslash after start
                auto itBack = std::find( itStart, data + fileSize, 0x5C );
                const char* endPtr =
                    ( itBack == data + fileSize )
                        ? reinterpret_cast< const char* >( data + fileSize )
                        : reinterpret_cast< const char* >( &*itBack ) + 1;
                headerText.assign( reinterpret_cast< const char* >( &*itStart ),
                                   endPtr );
            }
        }
    } catch ( const std::exception& ex )
    {
        std::cerr << "Failed to extract header: " << ex.what() << '\n';
        return false;
    }

    ANTLRInputStream input( headerText );
    logfile::SensorLogLexer lexer( &input );
    CommonTokenStream tokens( &lexer );
    logfile::SensorLogParser parser( &tokens );

    auto* fileCtx = parser.file();
    auto devices = build_content_from_ast( fileCtx );

    // map id -> device index
    std::unordered_map< uint32_t, size_t > id2idx;
    for ( size_t i = 0; i < devices.size(); ++i )
    {
        id2idx[devices[i].id] = i;
    }

    // ensure outdir exists
    if ( !fs::exists( outdir ) )
    {
        fs::create_directories( outdir );
    }

    // Convert buffer to vector for parallel processing
    std::vector< uint8_t > fileBytesVec( data, data + fileSize );

    // Use optimized parallel processing
    process_sections_parallel( fileBytesVec, sections, devices, id2idx );

    // write CSV per device
    for ( const auto& dev : devices )
    {
        write_csv_for_device( dev, outdir );
    }

    return true;
}

// Make parse_file_into_csv a thin wrapper around the buffer parser
bool parse_file_into_csv( const fs::path& input_file,
                          const fs::path& output_folder )
{
    if ( !fs::exists( input_file ) )
    {
        std::cerr << "File not found: " << input_file << '\n';
        return 2;
    }

    // read file into memory via mmap
    MappedFile input_mmap( input_file );
    return parse_buffer_into_csv( input_mmap.data(), input_mmap.size(),
                                  output_folder );
}

bool join_files( const std::vector< std::string >& files,
                 const std::string& outputPath )
{
    std::cout << "Creating a new file: " << outputPath << '\n';
    std::ofstream out( outputPath, std::ios::binary );
    if ( !out.is_open() )
    {
        std::cerr << "Failed to open output file: " << outputPath << "\n";
        return false;
    }

    const size_t BUF_SZ = 1 << 20;  // 1 MiB buffer
    std::vector< char > buf;
    buf.reserve( BUF_SZ );
    buf.resize( BUF_SZ );

    for ( const auto& file : files )
    {
        std::error_code ec;
        auto fsize = fs::file_size( file, ec );
        if ( ec )
        {
            std::cerr << "Failed to stat input file: " << file << " ("
                      << ec.message() << ")\n";
            return false;
        }

        std::ifstream in( file, std::ios::binary );
        if ( !in.is_open() )
        {
            std::cerr << "Failed to open input file: " << file << "\n";
            return false;
        }

        // Read and write in chunks
        while ( in )
        {
            in.read( buf.data(), static_cast< std::streamsize >( buf.size() ) );
            std::streamsize n = in.gcount();
            if ( n > 0 )
            {
                out.write( buf.data(), n );
            }
            if ( out.fail() )
            {
                std::cerr << "Failed writing to output file: " << outputPath
                          << "\n";
                return false;
            }
        }

        in.close();
    }

    out.close();
    return true;
}

// Return whether the operation was successful.
bool join_files_batch( const std::vector< std::string >& inputFiles,
                       const fs::path& outFolder )
{
    if ( inputFiles.empty() )
    {
        return true;
    }

    std::vector< std::string > sorted = inputFiles;
    std::sort( sorted.begin(), sorted.end() );

    auto make_output_path = [&]( int idx ) {
        return ( outFolder /
                 fs::path( "outputBIN" + std::to_string( idx ) + ".bin" ) )
            .string();
    };

    std::vector< std::string > batch;
    int outIndex = 0;

    auto flush_batch = [&]() -> bool {
        if ( batch.empty() )
        {
            return true;
        }
        const std::string outPath = make_output_path( outIndex++ );
        if ( !join_files( batch, outPath ) )
        {
            return false;
        }
        batch.clear();
        return true;
    };

    for ( const auto& filePath : sorted )
    {
        // If this file starts a new logical recording (has header),
        // finalize the previous batch first.
        if ( has_header( filePath ) )
        {
            if ( !flush_batch() )
            {
                return false;
            }
        }

        batch.emplace_back( filePath );
    }

    // Flush any remaining files
    return flush_batch();
}

int main( int argc, const char* argv[] )
{
    auto print_usage = []( const char* prog ) {
        std::cerr << "Usage: " << prog
                  << " [-j] [-p] <inputPath> <outputPath>\n";
        std::cerr << "  -j    join split files into merged .bin batches and "
                     "write to outputPath\n";
        std::cerr << "  -p    parse files (directory -> per-file parsing, or "
                     "single-file) into CSVs\n";
        std::cerr << "  -jp   join then parse the merged batches (like tar -cf "
                     "| tar -xf)\n";
    };

    bool cmd_join = false;
    bool cmd_parse = false;
    std::vector< std::string > positional;

    // Accept flags anywhere. Non-flag arguments are positional (inputPath, outputPath).
    for ( int i = 1; i < argc; ++i )
    {
        const char* arg = argv[i];
        if ( arg[0] == '-' && arg[1] != '\0' )
        {
            // allow combined short flags like -jp
            for ( size_t k = 1; k < strlen( arg ); ++k )
            {
                switch ( arg[k] )
                {
                    case 'j':
                        cmd_join = true;
                        break;
                    case 'p':
                        cmd_parse = true;
                        break;
                    default:
                        std::cerr << "Unknown flag: -" << arg[k] << '\n';
                        print_usage( argv[0] );
                        return 1;
                }
            }
        } else
        {
            positional.emplace_back( arg );
        }
    }

    if ( positional.size() < 2 )
    {
        std::cerr << "Missing required arguments: inputPath and outputPath\n";
        print_usage( argv[0] );
        return 1;
    }

    std::string inputPath = positional[0];
    std::string outputPath = positional[1];

    // If input is a directory, gather files and sort them using LOG(####) aware comparator
    std::vector< std::string > files;
    bool inputIsDir = fs::exists( inputPath ) && fs::is_directory( inputPath );

    if ( inputIsDir )
    {
        for ( const auto& entry :
              std::filesystem::directory_iterator( inputPath ) )
        {
            if ( std::filesystem::is_regular_file( entry.status() ) )
            {
                files.push_back( entry.path().string() );
            }
        }

        if ( files.empty() )
        {
            std::cerr << "No files found in directory: " << inputPath << '\n';
            return 2;
        }

        // Sort files by name, prefer numeric ordering for names matching LOG(####)
        std::regex log_re( FILENAME_REGEX, std::regex_constants::icase );
        auto stem = []( const std::string& p ) {
            return fs::path( p ).stem().string();
        };

        auto extract_lognumber = [&]( const std::string& haystack ) -> long {
            std::smatch match;
            if ( std::regex_search( haystack, match, log_re ) &&
                 match.size() >= 2 )
            {
                try
                {
                    return std::stol( match[1].str() );
                } catch ( const std::exception& )
                {
                    std::cerr << "Failed to parse log number in filename: "
                              << haystack << "\n";
                    return -1;
                }
            }
            return -1;
        };

        std::sort( files.begin(), files.end(),
                   [&]( const std::string& a_filename,
                        const std::string& b_filename ) {
                       auto a_stem = stem( a_filename );
                       auto b_stem = stem( b_filename );
                       long a_ln = extract_lognumber( a_stem );
                       long b_ln = extract_lognumber( b_stem );
                       if ( a_ln != -1 && b_ln != -1 && a_ln != b_ln )
                       {
                           return a_ln < b_ln;
                       }
                       if ( a_stem != b_stem )
                       {
                           return a_stem < b_stem;
                       }
                       return a_filename < b_filename;
                   } );
    }

    // Mode handling
    if ( cmd_join && !cmd_parse )
    {
        // join only
        if ( !inputIsDir )
        {
            std::cerr << "Join mode requires an input directory\n";
            return 2;
        }

        if ( !fs::exists( outputPath ) )
        {
            fs::create_directories( outputPath );
        }

        if ( !join_files_batch( files, fs::path( outputPath ) ) )
        {
            std::cerr << "Failed to join files\n";
            return 3;
        }

        std::cout << "Joined files written to: " << outputPath << '\n';
        return 0;
    }

    if ( cmd_parse && !cmd_join )
    {
        // parse only
        if ( inputIsDir )
        {
            if ( !fs::exists( outputPath ) )
            {
                fs::create_directories( outputPath );
            }

            unsigned int fileCount = 0;
            for ( const auto& file : files )
            {
                fs::path outdir =
                    fs::path( outputPath ) /
                    fs::path( "outputBIN" + std::to_string( fileCount++ ) );
                if ( !parse_file_into_csv( fs::path( file ), outdir ) )
                {
                    std::cerr << "Failed to parse file: " << file << '\n';
                    return 4;
                }
            }

            return 0;
        } else
        {
            // single file parse
            if ( !parse_file_into_csv( fs::path( inputPath ),
                                       fs::path( outputPath ) ) )
            {
                return 5;
            }
            return 0;
        }
    }

    if ( cmd_join && cmd_parse )
    {
        // join then parse
        if ( !inputIsDir )
        {
            std::cerr << "Join+Parse requires an input directory\n";
            return 2;
        }

        if ( !fs::exists( outputPath ) )
        {
            fs::create_directories( outputPath );
        }

        if ( !join_files_batch( files, fs::path( outputPath ) ) )
        {
            std::cerr << "Failed to join files\n";
            return 3;
        }

        // locate merged files and parse them
        std::vector< std::string > to_merge;
        for ( const auto& entry :
              std::filesystem::directory_iterator( outputPath ) )
        {
            if ( std::filesystem::is_regular_file( entry.status() ) )
            {
                const fs::path& path = entry.path();
                to_merge.push_back( path.string() );
            }
        }

        std::sort( to_merge.begin(), to_merge.end() );

        for ( const auto& file : to_merge )
        {
            fs::path path = file;
            std::string stemname = path.stem().string();  // e.g. outputBIN0
            fs::path outdir = fs::path( outputPath ) / fs::path( stemname );
            if ( !parse_file_into_csv( path, outdir ) )
            {
                std::cerr << "Failed to parse merged file: " << file << '\n';
                return 6;
            }
        }

        std::cout << "Joined and parsed batches written to: " << outputPath
                  << std::endl;
        return 0;
    }

    // Default: no flags -> parse single file
    if ( inputIsDir )
    {
        std::cerr << "No mode specified but input is a directory. Use -j, -p, "
                     "or -jp.\n";
        print_usage( argv[0] );
        return 1;
    }

    if ( !parse_file_into_csv( fs::path( inputPath ), fs::path( outputPath ) ) )
    {
        return 5;
    }

    return 0;
}
