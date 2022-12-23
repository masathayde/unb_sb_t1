#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "common.hpp"
#include "tokens.hpp"
#include "error.hpp"

using namespace std;

// Checar slide aula 4, pagina 27 para algoritmo de duas passagens, primeira passagem
// Segunda passagem no slides aula 5, pagina 5

int main (int argc, char* argv[]) {

    // string test = "llol";
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

    vector<string> errors = checkLexicalErrors(tokenizedProgram);

    for (auto it : errors)
        cout << it << endl;


    return 0;

}