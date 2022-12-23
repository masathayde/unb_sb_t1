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
bool isLowerCase (char input) {
    return (input >= ASCII_LOWERCASE_START && input <= ASCII_LOWERCASE_END); 
}

bool isUpperCase (char input) {
    return (input >= ASCII_UPPERCASE_START && input <= ASCII_UPPERCASE_END); 
}

bool isValidChar (char input) {
    return (isLowerCase(input) || isUpperCase(input));
}

char toLowerCase (char input) {
    if (isUpperCase(input))
        return input + ASCII_UPPER_TO_LOWER_OFFSET;
    else
        return input;
}

char toUpperCase (char input) {
    if (isLowerCase(input))
        return input + ASCII_LOWER_TO_UPPER_OFFSET;
    else
        return input;
}

void toUpperCase (std::string& input) {
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
}

#endif