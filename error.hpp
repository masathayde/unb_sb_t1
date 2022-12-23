#ifndef ERROR_H_
#define ERROR_H_

#include <string>
#include "tokens.hpp"
#include "common.hpp"

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

bool isProperlyFormattedNumber (string token) {
    int i = 0;
    // Hexadecimal number.
    if (token.size() > 2 && token[0] == '0' && (token[1] == 'X' || token[1] == 'x') ) {
        i = 2;
    }
    // Negative number.
    if (token.size() > 1 && token[0] == '-') {
        i = 1;
    }
    for (; i < token.size(); ++i) {
        if (token[i] < '0' || token[i] > '9')
           return false; 
    }
    return true;
}

// Returns index of first invalid char, if there is one. Otherwise, returns -1.
int isValidLabel (string token) {
    for (int i = 0; i < token.size(); ++i) {
        char c = token[i];
        if ( !((c >= ASCII_UPPERCASE_START && c <= ASCII_UPPERCASE_START + ALPHABET_SIZE) || (c >= '0' && c <= '9') || c == '_' || c == ':' || c == '+' || c == ',') )
            return i;
    }
    return -1;
}

vector<string> checkLexicalErrors (vector<TokenLine>& tokenLines) {
    vector<string> output;
    for (int i = 0; i < tokenLines.size(); ++i) {
        for (int j = 0; j < tokenLines[i].tokens.size(); ++j) {
            string token = tokenLines[i].tokens[j];
            // Number.
            if ((token[0] >= '0' && token[0] <= '9') || token[0] == '-') {
                if (!isProperlyFormattedNumber(token)) {
                    string error = "Linha " + to_string(tokenLines[i].lineNumber) + ": Erro lexico: numero inical em rotulo: " + token;
                    output.push_back(error);
                }
            } else {
            // Not a number.
                int wrongCharIndex = isValidLabel(token);
                if (wrongCharIndex > 0) {
                    string error = "Linha " + to_string(tokenLines[i].lineNumber) + ": Erro lexico: carater invalido em " + token +
                    ": carater: " + token[wrongCharIndex];
                    output.push_back(error);
                }
            }
        }
    }
    return output;
}

#endif