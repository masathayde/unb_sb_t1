#include <sstream>
#include "common.hpp"
#include "classes.hpp"

using namespace std;

class TokenLine {
 public:
    vector<string> tokens;
    int lineNumber;

};


vector<string> createTokensFromLine (string input, int line_number) {
    vector<string> output;
    stringstream stream(input);
    char c = ' ';
    string token = "";
    while (!stream.eof()) {
        // Get rid of blank characters.
        stream.get(c);
        while (!stream.eof() && (c == ' ' || c == '\t')) {
            stream.get(c);
        }
        if (!stream.eof()) {
            stream.putback(c);
        } else {
            return output;
        }
        token = "";
        bool readingToken = true;
        while (readingToken && !stream.eof()) {
            stream.get(c);
            if ((c >= ASCII_UPPERCASE_START && c <= ASCII_UPPERCASE_START + ALPHABET_SIZE) || (c >= '0' && c <= '9') || c == '_') {
                // Valid character.
                if (stream.eof()) {
                    output.push_back(token);
                    readingToken = false;
                } else {
                    token = token + c;
                }
            } else if (c == ' ' || c == '\t') {
                output.push_back(token);
                readingToken = false;
            } else if (c == ':' || c == '+') {
                if (token != "") {
                    output.push_back(token);
                }
                token = c;
                output.push_back(token);
                readingToken = false;
            } else if (c == ';') {
                // Ignore everything else in the line, end function.
                if (token != "") {
                    output.push_back(token);
                }
                return output;
            } else {
                // Invalid character.
                // Throw error?
                throw runtime_error((string)"Linha " + to_string(line_number) + ": Erro lexico: carater nao permitido: " + c);
            }
        }
    }
    // if (token != "") {
    //     output.push_back(token);
    // }
    return output;
}

TokenLine tokenizeProgram () {


}
