#ifndef PREPROC_H_
#define PREPROC_H_

#include <unordered_map>
#include "tokens.hpp"

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