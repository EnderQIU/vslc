#include <iostream>

#include "utils/cmdline.h"
#include "lexical/logic/scanner.h"

int main(int argc, char* argv[]) {
    // initialize configuration.
    bool verboseMode;
    string inputFileName;
    string outputFileName = "a.out";

    // cmdline works
    cmdline::parser parser;
    parser.add("verbose", 'v', "Enable verbose mode, display the output of scanner and parser.");
    parser.add<string>("output", 'o', "Specify output file name. Default is a.out.", false, "a.out");
    parser.footer("filename");
    parser.set_program_name("vslc");

    parser.parse_check(argc, argv);

    // setup & check argv
    verboseMode = parser.exist("verbose");
    outputFileName = parser.get<string>("output");
    if (outputFileName.empty()){
        cerr<<"Please specify a output file."<<endl<<parser.usage();
        return 0;
    }
    if (parser.rest().empty()){
        cerr<<"Please specify a input file."<<endl<<parser.usage();
        return 0;
    } else inputFileName = parser.rest()[0];

    // Read source code file
    SourceCodeReader* reader = new SourceCodeReader(inputFileName);

    // lexical analysis
    auto *scanner = new Scanner(reader);
    vector<Token> scanner_result = scanner->scan(verboseMode);

    // clear non-grammatical tokens
    auto * tokens = new vector<Token>();
    for (auto &i : scanner_result) if (i.isGrammatical) tokens->push_back(i);
    delete scanner;  // free scanner, useless afterwards

    // syntax analysis

    return 0;
}