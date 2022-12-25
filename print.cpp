#include "print.hpp"

void printProgram (vector<TokenLine> tokenLines) {

    for (int i = 0; i < tokenLines.size(); ++i) {
        if (tokenLines[i].ignore == false) {
            cout << getStringFromTokenLine(tokenLines[i]) << endl;
        }
    }
}

void saveProgramToFile (vector<TokenLine> tokenLines, string filename) {

    ofstream file;
    file.open(filename.c_str());
    for (int i = 0; i < tokenLines.size(); ++i) {
        string line = getStringFromTokenLine(tokenLines[i]);
        if (tokenLines[i].ignore == false) {
            file << line << endl;
        }
    }
    file.close();
}