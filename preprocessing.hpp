#ifndef PREPROC_H_
#define PREPROC_H_

#include <unordered_map>
#include "tokens.hpp"

class MacroDef {
 public:
    string name;
    vector<string> arguments;
    vector<TokenLine> lines;
};

vector<TokenLine> expandMacro (TokenLine&, unordered_map<string,MacroDef>&);

// Modifies the input.
// Assumes there's no errors.
// Creates new vector of lines.
vector<TokenLine> preprocessMacro (vector<TokenLine>& tokenLines) {
    unordered_map<string,MacroDef> macroTable;
    vector<TokenLine> output;
    // First, scan program for macros;
    for (int i = 0; i < tokenLines.size(); ++i) {
        if (tokenLines[i].tokens.size() > 2 && tokenLines[i].tokens[2] == "MACRO") {
            MacroDef newMacro;
            newMacro.name = tokenLines[i].tokens[0];
            for (int j = 3; j < tokenLines[i].tokens.size(); j+=2) {
                newMacro.arguments.push_back(tokenLines[i].tokens[j]);
            }
            tokenLines[i].ignore = true;
            ++i;
            for (string line = ""; line != "ENDMACRO"; line = tokenLines[i].originalText) {
                newMacro.lines.push_back(tokenLines[i]);
                tokenLines[i].ignore = true;
                ++i;
            }
            tokenLines[i].ignore = true; // Ignoring ENDMACRO line.
            macroTable.insert(make_pair(newMacro.name,newMacro));

            // For debug, remove later
            // cout << "MACRO: " << newMacro.name << endl;
            // cout << "arguments: ";
            // for (auto it : newMacro.arguments) {
            //     cout << it << " ";
            // }
            // cout << endl << "lines: ";
            // for (auto it : newMacro.lines) {
            //     cout << it.originalText << endl;
            // }
            // cout << endl;
        }
    }

    // Replace Macro references.
    // Again, assume they're correctly formatted.
    //
    for (int i = 0; i < tokenLines.size(); ++i) {
        if (tokenLines[i].ignore == false) {
            vector<TokenLine> expandedMacro = expandMacro(tokenLines[i], macroTable);
            for (auto line : expandedMacro) {
                output.push_back(line);
            }
        }
    }
    return output;
}

// Recursive function to expand a macro that might itself contain a macro.
// Does NOT deal with infinite loops, assumes a macro will not call itself.
// Make sure not to change macroTable.
vector<TokenLine> expandMacro (TokenLine& tokenLine, unordered_map<string, MacroDef>& macroTable) {
    vector<TokenLine> output;
    if (tokenLine.ignore == false) {
        string token = tokenLine.tokens[0];
        unordered_map<string, MacroDef>::iterator macroDef = macroTable.find(token);
        if (macroDef != macroTable.end()) {
            unordered_map<string,string> aliasMap;
            // Assuming all the tokens are in the correct position here. No error checking at all.
            for (int i = 0; i < macroDef->second.arguments.size(); ++i) {
                aliasMap.insert(make_pair(macroDef->second.arguments[i], tokenLine.tokens[i*2+1]));
            }
            for (int i = 0; i < macroDef->second.lines.size(); ++i) {
                TokenLine newTokenLine = macroDef->second.lines[i];
                for (int j = 0; j < macroDef->second.lines[i].tokens.size(); ++j) {
                    string token = macroDef->second.lines[i].tokens[j];
                    unordered_map<string,string>::iterator it = aliasMap.find(token);
                    if (it != aliasMap.end()) {
                        // Replace Ampersand-prefixed macro variable.
                        newTokenLine.tokens[j] = it->second;
                    }
                }
                // Recursive call.
                vector<TokenLine> recursiveOutput = expandMacro(newTokenLine, macroTable);
                for (auto t : recursiveOutput) {
                    output.push_back(t);
                }
            }
        } else {
            // Stop condition - base case.
            output.push_back(tokenLine);
        }
    }
    return output;
}

// Modifies the input.
// EQUs are all before SECTION TEXT.
// Assumes there's no errors.
void preprocessEQUandIF (vector<TokenLine>& tokenLines) {

    unordered_map<string, string> equTable;
    int i = 0;
    for (string line = ""; line != "SECTION TEXT"; line = tokenLines[i].originalText) {
        string alias = tokenLines[i].tokens[2];
        string value = tokenLines[i].tokens[3];
        equTable.insert(make_pair(alias, value));
        tokenLines[i].ignore = true;
        ++i;
    }
    // Replace all EQUs. Skip SECTION TEXT line.
    for (i = i + 1; i < tokenLines.size(); ++i) {
        for (int j = 0; j < tokenLines[i].tokens.size(); ++j) {
            string token = tokenLines[i].tokens[j];
            unordered_map<string, string>::iterator it = equTable.find(token);
            if (it != equTable.end()) {
                tokenLines[i].tokens[j] = it->second;
            }
        }
    }
    // Replace IFs.
    // Assumes IFs are correctly formatted.
    for (i = 0; i < tokenLines.size() - 1; ++i) {
        if (tokenLines[i].ignore == false) {
            if (tokenLines[i].tokens[0] == "IF") {
                int value = stoi(tokenLines[i].tokens[1], NULL, 0);
                if (value == 0) {
                    // Ignore next line if IF condition doesn't hold.
                    tokenLines[i+1].ignore = true;
                }
                tokenLines[i].ignore = true; // We don't want to print this line, so ignore it.
            }
        }
    }
}










#endif