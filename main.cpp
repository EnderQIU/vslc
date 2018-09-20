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
    if (outputFileName.empty()){
        cerr<<"Please specify a output file."<<endl<<cmdParser.usage();
        return 0;
    }
    if (cmdParser.rest().empty()){
        cerr<<"Please specify a input file."<<endl<<cmdParser.usage();
        return 0;
    } else inputFileName = cmdParser.rest()[0];

    // Read source code file
    SourceCodeReader* reader = new SourceCodeReader(inputFileName);

    // Lexical analysis
    auto *scanner = new Scanner(reader);
    vector<Token*> scanner_result = scanner->scan(verboseMode);

    // Clear non-grammatical tokens & initialize the input buffer
    auto * symbols = new vector<Symbol>();
    for (Token *i : scanner_result) if (i->isGrammatical) symbols->push_back(Symbol(i));
    symbols->push_back(Symbol(SymbolType::DOLLAR));  // input buffer symbols --  end with $
    auto * inputBuffer = new InputBuffer(symbols);
    delete scanner;  // free scanner, useless afterwards

    // syntax analysis
    auto * parser  = new Parser(inputBuffer);
    AST* rootNode = parser->parse(verboseMode);

    return 0;
}