#ifndef TOKENS_H_
#define TOKENS_H_

#include <sstream>
#include <fstream>
#include "common.hpp"
// #include "classes.hpp"

using namespace std;

class TokenLine {
 public:
    vector<string> tokens;
    string originalText;
    int lineNumber;
    bool ignore {false};
};

string getStringFromTokenLine (TokenLine tokenLine) {
    string output = "";
    string token = "";
    string prevToken = "";
    for (int i = 0; i < tokenLine.tokens.size(); ++i) {
        string token = tokenLine.tokens[i];
        if (i != 0 && token != ":" && token != "+" && token != "," && prevToken != "+") {
            output = output + " ";
        }
        output = output + token;
        prevToken = token;
    }
    return output;
}


vector<string> createTokensFromLine (string input) {
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
            if (c == ' ' || c == '\t') {
                output.push_back(token);
                readingToken = false;
            } else if (c == ':' || c == '+' || c == ',') {
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
                if (stream.eof()) {
                    output.push_back(token);
                    readingToken = false;
                } else {
                    token = token + c;
                }
            }
        }
    }
    // if (token != "") {
    //     output.push_back(token);
    // }
    return output;
}

vector<TokenLine> tokenizeProgram (char* filename) {
    ifstream file;
    file.open(filename);
    string lineRead;
    vector<TokenLine> output;
    int lineCounter = 0;
    while(!file.eof()) {
        lineCounter++;
        getline(file, lineRead);
        toUpperCase(lineRead); // Converts lowercase to uppercase. VERY important.
        vector<string> tokens = createTokensFromLine(lineRead);
        if (!tokens.empty()) {
            TokenLine tokenLine;
            tokenLine.lineNumber = lineCounter;
            tokenLine.originalText = lineRead;
            tokenLine.tokens = tokens;
            output.push_back(tokenLine);
        }
    }
    file.close();
    return output;
}


// Symbol table stuff
#include <map>
map<string,int> createSymbolTable (vector<TokenLine>& tokenLines, int mode) {



}


// if ((c >= ASCII_UPPERCASE_START && c <= ASCII_UPPERCASE_START + ALPHABET_SIZE) || (c >= '0' && c <= '9') || c == '_') {
//                 // Valid character.
//                 if (stream.eof()) {
//                     output.push_back(token);
//                     readingToken = false;
//                 } else {
//                     token = token + c;
//                 }
//             } else 

#endif