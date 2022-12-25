#ifndef TOKENS_H_
#define TOKENS_H_

#include <sstream>
#include <fstream>
#include <vector>
#include <string>
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

string getStringFromTokenLine (TokenLine tokenLine);
vector<string> createTokensFromLine (string input);
vector<TokenLine> tokenizeProgram (char* filename);

#endif