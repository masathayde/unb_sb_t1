#ifndef PRINT_H_
#define PRINT_H_

#include <iostream>
#include <fstream>
#include <string>
#include "tokens.hpp"

void printProgram (vector<TokenLine> tokenLines);
void saveProgramToFile (vector<TokenLine> tokenLines, string filename);

#endif