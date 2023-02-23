// # Universidade de Brasilia - Ciencia da Computacao
// # Software Basico - 2/2022
// # Prof. Bruno Macchiavello
// # Marco Antonio Souza de Athayde - 18/0126814
// # Trabalho 1: Montador

#include <iostream>
#include <fstream>
#include <string>
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

    // Reading and interpreting arguments.
    if (argc != 3) {
        cout << "Erro: Numero errado de argumentos (devem ser 3)" << endl;
        return 0;
    }

    if (!((string) argv[1] == "-p" || (string) argv[1] == "-m" || (string) argv[1] == "-o")) {
        cout << "Erro: modo de operacao nao existente: " << argv[1] << endl;
        return 0;
    }

    ifstream file;
    file.open(argv[2]);
    if (!file.is_open()) {
        cout << "Erro: nao foi possivel abrir arquivo " + (string) argv[2] << endl;
        return 0;
    }
    file.close();

    int mode = 0;
    switch (argv[1][1]) {
        case 'p': mode = 1;
            break;
        case 'm': mode = 2;
            break;
        case 'o': mode = 3;
            break;
        default: cout << "Something went wrong." << endl;
            return 0;
    }

    vector<TokenLine> tokenizedProgram = tokenizeProgram(argv[2]);
    // for (int i = 0; i < tokenizedProgram.size(); ++i) {
    //     cout << "Line " << tokenizedProgram[i].lineNumber << ": " << " tokens: ";
    //     for (int j = 0; j < tokenizedProgram[i].tokens.size(); ++j) {
    //         cout << tokenizedProgram[i].tokens[j] << ' ';
    //     }
    //     cout << endl;
    // }

    // Preprocessing


    preprocessEQUandIF(tokenizedProgram);
    // for (int i = 0; i < tokenizedProgram.size(); ++i) {
    //     cout << "Line " << tokenizedProgram[i].lineNumber << ": " << " tokens: ";
    //     for (int j = 0; j < tokenizedProgram[i].tokens.size(); ++j) {
    //         cout << tokenizedProgram[i].tokens[j] << ' ';
    //     }
    //     cout << endl;
    // }

    if (mode == 1) {
        saveProgramToFile(tokenizedProgram, (string) argv[2] + ".PRE");
        cout << "Arquivo preprocessado (EQU e IF) salvo em " + (string) argv[2] + ".PRE" << endl;
        return 0;
    }

    vector<TokenLine> programAfterMacro = preprocessMacro(tokenizedProgram);

    if (mode == 2) {
        saveProgramToFile(programAfterMacro, (string) argv[2] + ".MCR");
        cout << "Arquivo preprocessado (EQU, IF e macros) salvo em " + (string) argv[2] + ".MCR" << endl;
        return 0;
    }

    

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
        //cout << translate(instList, dataList, symbolTable) << endl;
        ofstream ofile;
        ofile.open((string)argv[2] + ".OBJ");
        ofile << translate(instList, dataList, symbolTable) << endl;
        ofile.close();
        cout << "Programa montado salvo em " + (string) argv[2] + ".OBJ" << endl;
    }

    return 0;

}