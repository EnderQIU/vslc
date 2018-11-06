#include <iostream>

#include <llvm/IR/IRBuilder.h>

#include "utils/cmdline.h"
#include "lexical/logic/scanner.h"
#include "syntax/structure/input_buffer.h"
#include "syntax/logic/parser.h"
#include "utils/engine.h"


bool verboseMode = false;
bool shellMode = false;

bool endswith(std::string const& str, std::string const& what) {
    return what.size() <= str.size()
           && str.find(what, str.size() - what.size())!= str.npos;
}

/*
 * Shell Mode
 * Parse instructions line by line.
 */
int shell(){
    shellMode = true;
    cout<<"VSLC v0.1 interactive shell"<<endl;
    while (true){
        // Read from shell
        cout << ">>> ";
        string aline;
        getline(cin, aline);  // use getLine() because cin<< will ignore the space character

        if (aline == "exit"){
            return 0;
        }

        SourceCodeReader reader = SourceCodeReader();
        if (endswith(aline, "\\")){
            // multiple lines mode
            while (endswith(aline, "\\")){
                aline.erase(aline.end() - 1);
                reader.addLine(aline);
                cout << ">>> ";
                getline(cin, aline);
            }
        }else{
            reader.addLine(aline);  // single line mode
        }
        try {
            // Lexical analysis
            Scanner scanner = Scanner(reader);
            vector<Token> scanner_result = scanner.scan();

            // Clear non-grammatical tokens & initialize the input buffer
            vector<Symbol> symbols = vector<Symbol>();
            for (Token i : scanner_result) if (i.isGrammatical) symbols.emplace_back(i);
            symbols.emplace_back(SymbolType::HASHTAG);  // input buffer symbols --  end with $
            InputBuffer inputBuffer = InputBuffer(symbols);

            // Syntax analysis
            Parser parser = Parser(inputBuffer, reader);
            AST rootNode = parser.parse();
            if (verboseMode) {
                rootNode.print();
            }

            // IR code generation
            // save LLVM engine status
        }
        catch (ScanException & exc)
        {
            if (verboseMode) cerr << exc.what() << endl;
        }
        catch (ParseException & exc)
        {
            if (verboseMode) cerr << exc.what() << endl;
        }
        catch (CodeGenException & exc)
        {
            if (verboseMode) cerr << exc.what() << endl;
        }
    }
}


int main(int argc, char* argv[]) {
    // initialize configuration.
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
        return shell();  // Enter the shell mode
    }
    else inputFileName = cmdParser.rest()[0];

    // Read source code file
    SourceCodeReader reader = SourceCodeReader(inputFileName);

    try {
        // Lexical analysis
        Scanner scanner = Scanner(reader);
        vector<Token> scanner_result = scanner.scan();

        // Clear non-grammatical tokens & initialize the input buffer
        vector<Symbol> symbols = vector<Symbol>();
        for (Token i : scanner_result) if (i.isGrammatical) symbols.emplace_back(i);
        symbols.emplace_back(SymbolType::HASHTAG);  // input buffer symbols --  end with $
        InputBuffer inputBuffer = InputBuffer(symbols);

        // syntax analysis
        Parser parser = Parser(inputBuffer, reader);
        AST rootNode = parser.parse();
        if (verboseMode) rootNode.print();

        // IR code generation
        // convert to AST with code gen function

    }
    catch (ScanException & exc)
    {
        if (verboseMode) cerr << exc.what() << endl;
    }
    catch (ParseException & exc)
    {
        if (verboseMode) cerr << exc.what() << endl;
    }
    catch (CodeGenException & exc)
    {
        if (verboseMode) cerr << exc.what() << endl;
    }


    return 0;
}