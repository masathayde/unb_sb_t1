#ifndef PREPROC_H_
#define PREPROC_H_

#include <unordered_map>
#include <vector>
#include <string>
#include "tokens.hpp"

class MacroDef {
 public:
    string name;
    vector<string> arguments;
    vector<TokenLine> lines;
};

// Modifies the input.
// Assumes there's no errors.
// Creates new vector of lines.
vector<TokenLine> preprocessMacro (vector<TokenLine>& tokenLines);

// Recursive function to expand a macro that might itself contain a macro.
// Does NOT deal with infinite loops, assumes a macro will not call itself.
// Make sure not to change macroTable.
vector<TokenLine> expandMacro (TokenLine& tokenLine, unordered_map<string, MacroDef>& macroTable);

// Modifies the input.
// EQUs are all before SECTION TEXT.
// Assumes there's no errors.
void preprocessEQUandIF (vector<TokenLine>& tokenLines);

#endif