#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <string>
#include <algorithm>
#define ASCII_UPPER_TO_LOWER_OFFSET 32
#define ASCII_LOWER_TO_UPPER_OFFSET -32
#define ASCII_UPPERCASE_START 65
#define ASCII_UPPERCASE_END 90
#define ASCII_LOWERCASE_START 97
#define ASCII_LOWERCASE_END 122
#define ALPHABET_SIZE 26

// Assumes ASCII.
bool isLowerCase (char input);
bool isUpperCase (char input);
bool isValidChar (char input);
char toLowerCase (char input);
char toUpperCase (char input);
void toUpperCase (std::string& input);

#endif