#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "common.hpp"
#include "classes.hpp"
#include "tokens.hpp"
#include "error.hpp"
#include "print.hpp"
#include "preprocessing.hpp"

using namespace std;

// Checar slide aula 4, pagina 27 para algoritmo de duas passagens, primeira passagem
// Segunda passagem no slides aula 5, pagina 5

int main (int argc, char* argv[]) {

    vector<TokenLine> tokenizedProgram = tokenizeProgram((char*)"fatoriamacro.asm");
    // for (int i = 0; i < tokenizedProgram.size(); ++i) {
    //     cout << "Line " << tokenizedProgram[i].lineNumber << ": " << " tokens: ";
    //     for (int j = 0; j < tokenizedProgram[i].tokens.size(); ++j) {
    //         cout << tokenizedProgram[i].tokens[j] << ' ';
    //     }
    //     cout << endl;
    // }

    preprocessEQUandIF(tokenizedProgram);
    for (int i = 0; i < tokenizedProgram.size(); ++i) {
        cout << "Line " << tokenizedProgram[i].lineNumber << ": " << " tokens: ";
        for (int j = 0; j < tokenizedProgram[i].tokens.size(); ++j) {
            cout << tokenizedProgram[i].tokens[j] << ' ';
        }
        cout << endl;
    }
    vector<TokenLine> programAfterMacro = preprocessMacro(tokenizedProgram);



    vector<string> lexErrors = checkLexicalErrors(programAfterMacro);
    for (auto it : lexErrors)
        cout << it << endl;

    unordered_map<string, InstructionDef> insDefTable = makeInstructionDefTable();
    vector<Instruction> instList;
    vector<DataDirective> dataList;
    unordered_map<string,int> symbolTable;
    vector<string> synErrors = checkSyntaxMakeInstructionListMakeSymbolTable(programAfterMacro, insDefTable, instList, dataList, symbolTable);
    for (auto it : synErrors)
        cout << it << endl;
    
    vector<string> semErrors = checkForSemanticErrors(instList, symbolTable);
    for (auto it : semErrors)
        cout << it << endl;

    if (lexErrors.size() + synErrors.size() + semErrors.size() == 0) {
        cout << translate(instList, dataList, symbolTable) << endl;
    }

    //printProgram(programAfterMacro);
    // saveProgramToFile(programAfterMacro, "fatoriamacro.PRE");

    return 0;

}