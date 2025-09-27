#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "gen/SensorLogLexer.h"
#include "gen/SensorLogParser.h"

using namespace antlr4;

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    std::ifstream stream;
    stream.open(argv[1]);
    ANTLRInputStream input(stream);
    SensorLogLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    SensorLogParser parser(&tokens);

    tree::ParseTree* tree = parser.file();
    std::cout << tree->toStringTree(&parser) << std::endl;

    return 0;
}
