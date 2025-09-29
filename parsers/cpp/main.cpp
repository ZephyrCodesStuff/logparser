#include <fstream>
#include <iostream>
#include "SensorLogLexer.h"
#include "SensorLogParser.h"

using namespace antlr4;

int main( int argc, const char* argv[] )
{
    if ( argc < 2 )
    {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    std::ifstream stream;
    stream.open( argv[1] );

    if ( !stream.is_open() )
    {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 2;
    }

    ANTLRInputStream input( stream );
    logfile::SensorLogLexer lexer( &input );
    CommonTokenStream tokens( &lexer );
    logfile::SensorLogParser parser( &tokens );

    tree::ParseTree* tree = parser.file();
    std::cout << tree->toStringTree( &parser ) << std::endl;

    return 0;
}
