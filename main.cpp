#include <iostream>

#include "utils/cmdline.h"
#include "lexical/logic/scanner.h"
#include "syntax/structure/input_buffer.h"
#include "syntax/logic/parser.h"

int main(int argc, char* argv[]) {
    // initialize configuration.
    bool verboseMode;
    string inputFileName;
    string outputFileName = "a.out";

    // cmdline works
    cmdline::parser cmdParser;
    cmdParser.add("verbose", 'v', "Enable verbose mode, display the output of scanner and cmdParser.");
    cmdParser.add<string>("output", 'o', "Specify output file name. Default is a.out.", false, "a.out");
    cmdParser.footer("filename");
    cmdParser.set_program_name("vslc");

    cmdParser.parse_check(argc, argv);

    // setup & check argv
    verboseMode = cmdParser.exist("verbose");
    outputFileName = cmdParser.get<string>("output");
    if (outputFileName.empty()) {
        cerr << "Please specify a output file." << endl << cmdParser.usage();
        return 0;
    }
    if (cmdParser.rest().empty()) {
        cerr << "Please specify a input file." << endl << cmdParser.usage();
        return 0;
    }
    else inputFileName = cmdParser.rest()[0];

    // Read source code file
    SourceCodeReader reader = SourceCodeReader(inputFileName);

    // Lexical analysis
    Scanner scanner = Scanner(reader);
    vector<Token> scanner_result = scanner.scan(verboseMode);

    // Clear non-grammatical tokens & initialize the input buffer
    vector<Symbol> symbols = vector<Symbol>();
    for (Token i : scanner_result) if (i.isGrammatical) symbols.emplace_back(i);
    symbols.emplace_back(SymbolType::HASHTAG);  // input buffer symbols --  end with $
    InputBuffer inputBuffer = InputBuffer(symbols);

    // syntax analysis
    Parser parser = Parser(inputBuffer, reader);
    AST rootNode = parser.parse(verboseMode);
    if (verboseMode) {
        rootNode.print();
    }
    
    return 0;
}