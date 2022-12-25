#include "common.hpp"

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