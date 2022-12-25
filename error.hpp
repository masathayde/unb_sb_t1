#ifndef ERROR_H_
#define ERROR_H_

#include <string>
#include <unordered_map>
#include "tokens.hpp"
#include "common.hpp"
#include "classes.hpp"

using namespace std;

// Error checking stuff
/** Lista de erros:
 * Dois rotulos na mesma linha
 * Rotulo nao definido
 * Dado nao definido (nao sei o que eh isso)
 * Quantidade de argumentos errada
 * Secao TEXT faltando
 * Instrucao ou diretiva inexistente
 * Erros lexicos (caracteres especiais ou numero inicial em rotulo)
**/

bool isProperlyFormattedNumber (string token);

// Returns index of first invalid char, if there is one. Otherwise, returns -1.
int isValidLabel (string token);

// Alters input: Flags incorrect lines so they won't be checked for syntactic or semantic errors.
vector<string> checkLexicalErrors (vector<TokenLine>& tokenLines);

// Returns information about data directive in underline-prefixed inputs.
string checkDataLineSyntaxAndBuildDataDirective (TokenLine& line, string& _label, DataDirective& _dataD);

// Returns after finding the first error in a line.
// Returns information about Instruction in some of the inputs.
// This is definitely not a good function. Does more than one thing. Doesn't just deal with error checking. It's huge. But w/e, deadlines exist.
string checkTextLineSyntaxAndBuildInstruction (TokenLine& line, unordered_map<string,InstructionDef>& insDefTable, string& _label, Instruction& _instruction);

// Uses a subroutine to check syntax of very line and create a list of instructions.
vector<string> checkSyntaxMakeInstructionListMakeSymbolTable
(vector<TokenLine>& tokenLines, unordered_map<string,InstructionDef>& insDefTable, vector<Instruction>& _instList, vector<DataDirective>& _dataList,
unordered_map<string,int>& _symbolTable);

vector<string> checkForSemanticErrors (vector<Instruction>& instList, unordered_map<string,int>& symbolTable);
#endif