#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include "common.hpp"
#include "tokens.hpp"

using namespace std;

// Checar slide aula 4, pagina 27 para algoritmo de duas passagens, primeira passagem
// Segunda passagem no slides aula 5, pagina 5

int main (int argc, char* argv[]) {

    // string test = "llol";
    // toUpperCase(test);
    // cout << test << endl;

    ifstream file;
    file.open("fatoriamacro.asm");
    char c;
    string s;
    //file.seekg(-1);
    //file.get(c);
    while(!file.eof()) {
        getline(file, s);
        cout << s << endl;
        vector<string> test = createTokensFromLine(s, 1);
        cout << "tokens: ";
        for (int i = 0; i < test.size(); ++i) {
            cout << test[i] << ' ';
        }
        cout << endl;
    }




    return 0;

}