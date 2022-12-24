#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "common.hpp"
#include "tokens.hpp"
#include "error.hpp"
#include "print.hpp"
#include "preprocessing.hpp"

using namespace std;

// Checar slide aula 4, pagina 27 para algoritmo de duas passagens, primeira passagem
// Segunda passagem no slides aula 5, pagina 5

int main (int argc, char* argv[]) {

    // string test = "llol losaaf+sfd,cxASKf;;// issaf";
    // toUpperCase(test);
    // cout << test << endl;

    vector<TokenLine> tokenizedProgram = tokenizeProgram((char*)"fatoriamacro.asm");
    for (int i = 0; i < tokenizedProgram.size(); ++i) {
        cout << "Line " << tokenizedProgram[i].lineNumber << ": " << " tokens: ";
        for (int j = 0; j < tokenizedProgram[i].tokens.size(); ++j) {
            cout << tokenizedProgram[i].tokens[j] << ' ';
        }
        cout << endl;
    }

    // vector<string> errors = checkLexicalErrors(tokenizedProgram);
    // for (auto it : errors)
    //     cout << it << endl;

    // int test = stoi("0X10", NULL, 0);
    // cout << test << endl;

    preprocessEQUandIF(tokenizedProgram);
    vector<TokenLine> programAfterMacro = preprocessMacro(tokenizedProgram);
    printProgram(programAfterMacro);
    // saveProgramToFile(programAfterMacro, "fatoriamacro.PRE");
    return 0;

}