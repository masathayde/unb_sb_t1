#include "error.hpp"

bool isProperlyFormattedNumber (string token) {
    int i = 0;
    // Hexadecimal number.
    if (token.size() > 2 && token[0] == '0' && (token[1] == 'X' || token[1] == 'x') ) {
        i = 2;
        for (; i < token.size(); ++i) {
            if (!((token[i] >= '0' && token[i] <= '9') || (token[i] >= 'A' && token[i] <= 'F')))
                return false;
        }
    } else {
    // Decimal number.
        // Negative number.
        if (token.size() > 1 && token[0] == '-') {
            i = 1;
        }
        for (; i < token.size(); ++i) {
            if (token[i] < '0' || token[i] > '9')
            return false; 
        }
    }
    return true;
}

// Returns index of first invalid char, if there is one. Otherwise, returns -1.
int isValidLabel (string token) {
    for (int i = 0; i < token.size(); ++i) {
        char c = token[i];
        if ( !((c >= ASCII_UPPERCASE_START && c <= ASCII_UPPERCASE_START + ALPHABET_SIZE) || (c >= '0' && c <= '9') || c == '_' || c == ':' || c == '+' || c == ',') )
            return i;
    }
    return -1;
}

// Alters input: Flags incorrect lines so they won't be checked for syntactic or semantic errors.
vector<string> checkLexicalErrors (vector<TokenLine>& tokenLines) {
    vector<string> output;
    for (int i = 0; i < tokenLines.size(); ++i) {
        bool hasError = false;
        for (int j = 0; j < tokenLines[i].tokens.size(); ++j) {
            string token = tokenLines[i].tokens[j];
            // Number.
            if ((token[0] >= '0' && token[0] <= '9') || token[0] == '-') {
                if (!isProperlyFormattedNumber(token)) {
                    string error = "Linha " + to_string(tokenLines[i].lineNumber) + ": Erro lexico: numero inical em rotulo: " + token;
                    output.push_back(error);
                    hasError = true;
                }
            } else {
            // Not a number.
                int wrongCharIndex = isValidLabel(token);
                if (wrongCharIndex > 0) {
                    string error = "Linha " + to_string(tokenLines[i].lineNumber) + ": Erro lexico: carater invalido em " + token +
                    ": carater: " + token[wrongCharIndex];
                    output.push_back(error);
                    hasError = true;
                }
            }
        }
        if (hasError) {
            tokenLines[i].ignore = true;
        }
    }
    return output;
}

// Returns information about data directive in underline-prefixed inputs.
string checkDataLineSyntaxAndBuildDataDirective (TokenLine& line, string& _label, DataDirective& _dataD) {

    // Data lines must always have a least 3 tokens, and no more than 4.
    // LABEL: KEYWORD [optional argument for SPACE directive].
    if (line.tokens.size () < 3 || line.tokens.size() > 4) {
        return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: numero incorreto de tokens: " + to_string(line.tokens.size());
    }

    // Initial token has to be a keyword. We only check the first character.
    // Assumes lexical error checking was done first, and that this token is valid.
    if (line.tokens[0][0] < 'A' || line.tokens[0][0] > 'Z') {
        return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: token inicial deve ser uma palavra. Token incorreto: " + line.tokens[0];
    }

    // Second token always colon.
    if (line.tokens[1] != ":") {
        return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: token inesperado: " + line.tokens[1];
    }

    string directive = line.tokens[2];

    if (directive == "SPACE") {
        // SPACE has an optional argument. Has to be a number and bigger than 0;
        if (line.tokens.size() == 4) {
            if (line.tokens[3][0] < '0' || line.tokens[3][0] > '9') {
                return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: argumento dado nao e_ numero valido: " + line.tokens[3];
            }
            int allotedSpace = stoi(line.tokens[3], NULL, 0);
            if (allotedSpace < 1) {
                return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: argumento de SPACE deve ser maior que zero: " + line.tokens[3];
            }
            _dataD.size = allotedSpace;
        } else {
            _dataD.size = 1;
        }
        _dataD.value = 0;
    } else if (directive == "CONST") {
        if (line.tokens.size() != 4) {
            return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: diretiva CONST precisa de argumento: ";
        }
        // Argument of CONST can be a decimal or a hexadecimal, and can also be negative.
        if ((line.tokens[3][0] < '0' || line.tokens[3][0] > '9') && line.tokens[3][0] != '-' ) {
            return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: argumento dado nao e_ numero: " + line.tokens[3];
        }
        int constValue = stoi(line.tokens[3], NULL, 0);
        _dataD.size = 1;
        _dataD.value = constValue;
    } else {
        return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: instrucao ou diretiva inexistente: " + directive;
    }

    _label = line.tokens[0];
    return "";
}

// Returns after finding the first error in a line.
// Returns information about Instruction in some of the inputs.
// This is definitely not a good function. Does more than one thing. Doesn't just deal with error checking. It's huge. But w/e, deadlines exist.
string checkTextLineSyntaxAndBuildInstruction (TokenLine& line, unordered_map<string,InstructionDef>& insDefTable, string& _label, Instruction& _instruction) {

    // Initial token has to be a keyword. We only check the first character.
    // Assumes lexical error checking was done first, and that this token is valid.
    if (line.tokens[0][0] < 'A' || line.tokens[0][0] > 'Z') {
        return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: token inicial deve ser uma palavra. Token incorreto: " + line.tokens[0];
    }

    // Expected index of instruction name. If there's a label, it'll be changed to 2.
    int index = 0;
    // Labeled line. Check if there are multiple colons.
    if (line.tokens.size() > 1 && line.tokens[1] == ":") {
        for (int j = 2; j < line.tokens.size(); ++j) {
            if (line.tokens[j] == ":") {
                return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: mais de um rotulo na mesma linha";
            }
        }
        _label = line.tokens[0];
        // Case where line is just a label definition.
        if (line.tokens.size() == 2) {
            return "";
        }
        index = 2;
    }
    // Check if instruction exists.
    unordered_map<string, InstructionDef>::iterator it = insDefTable.find(line.tokens[index]);
    if (it == insDefTable.end()) {
        return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: instrucao ou diretiva inexistente: " + line.tokens[index];
    }
    InstructionDef definition = it->second;
    _instruction.definition = definition;

    int argumentCounter = 0;
    // Multiple arguments must be separated by comma.
    // As such, we check for the presence of at least two tokens per loop: argument and comma.
    for (++index; index < line.tokens.size(); index += 2) {
        string argumentName = line.tokens[index];
        Argument argument;
        argument.name = argumentName;
        // Arguments must be labels.
        if (argumentName[0] < 'A' || argumentName[0] > 'Z') {
            return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: argumento incorreto: " + argumentName;
        }
        // Look ahead for address modifiers.
        if (index+2 < line.tokens.size() && line.tokens[index+1] == "+") {
            // Modifier must be a number. Only check first character because lexical error check ensures it's all we need to check if it's a number.
            if (line.tokens[index+2][0] < '0' || line.tokens[index+2][0] > '9') {
                return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: modificador de rotulo nao e_ numero: " + line.tokens[index+2];
            }
            argument.modifier = stoi(line.tokens[index+2], NULL, 0);
            index += 2; // Changing loop counter inside the loop. DANGEROUS.
        }
        // Look ahead for comma separator.
        if (index+1 < line.tokens.size() && line.tokens[index+1] != ",") {
            return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: delimitador incorreto: " + line.tokens[index+1];
        }

        _instruction.arguments.push_back(argument);
        ++argumentCounter;
    }

    // At this point, the instruction is fully read. However, in the last loop, it's possible for an extra comma to be read and accepted.
    // That's a grammar error so another check is needed to verify if that extra token is there.
    if (index-1 < line.tokens.size() && line.tokens[index-1] == ",") {
        return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: token inesperado: " + line.tokens[index-1];
    }

    if (argumentCounter != definition.argumentCount) {
        return "Linha " + to_string(line.lineNumber) + ": Erro sintatico: quantidade incorreta de argumentos para instrucao " + definition.name
        + ": esperava(m)-se " + to_string(definition.argumentCount) + ", encontrado(s) " + to_string(argumentCounter);
    }

    // Finally, the instruction is complete. If this variable is equal to its initial construction value, that means the line was only a label definition.
    _instruction.originalLineNumber = line.lineNumber;
    return "";
}

// Uses a subroutine to check syntax of very line and create a list of instructions.
vector<string> checkSyntaxMakeInstructionListMakeSymbolTable
(vector<TokenLine>& tokenLines, unordered_map<string,InstructionDef>& insDefTable, vector<Instruction>& _instList, vector<DataDirective>& _dataList,
unordered_map<string,int>& _symbolTable) {

    vector<string> output;
    // Program must have at least 2 lines.
    if (tokenLines.size() < 2) {
        string error = "Linha 0: Erro sintatico: programa precisa ter ao menos 2 linhas";
        output.push_back(error);
        return output;
    }
    // Assumes first line is SECTION TEXT, followed by instructions, followed by SECTION DATA.
    // Check if text section is empty, in which case SECTION DATA is the second line.
    int i = 1;
    int address = 0; // Address of the instruction.
    // if (tokenLines[i].originalText == "SECTION DATA") {
    if (tokenLines[i].tokens[0] == "SECTION" && tokenLines[i].tokens[1] == "DATA") {
        string error = "Linha "  + to_string(tokenLines[i].lineNumber) + ": Erro sintatico: secao TEXT faltante";
        output.push_back(error);
    } else {
        // for (string line = tokenLines[i].originalText; line != "SECTION DATA"; ++i, line = tokenLines[i].originalText) {
        for (; !(tokenLines[i].tokens[0] == "SECTION" && tokenLines[i].tokens[1] == "DATA"); ++i) {
            if (tokenLines[i].ignore == false) {
                string label = "";
                Instruction newInstruction;
                newInstruction.originalLineNumber = 0;
                string error = "";
                error = checkTextLineSyntaxAndBuildInstruction(tokenLines[i], insDefTable, label, newInstruction);
                if (error == "") {
                    if (label != "") {
                        _symbolTable.insert(make_pair(label, address));
                    }
                    if (newInstruction.originalLineNumber != 0) {
                        newInstruction.address = address;
                        _instList.push_back(newInstruction);
                        address = address + 1 + newInstruction.definition.argumentCount; // Address increment = 1 + number of arguments in instruction.
                    }
                } else {
                    output.push_back(error);
                }
            }
        }
        // Done with text section, now for DATA. Skip "SECTION DATA".
        for (++i; i < tokenLines.size(); ++i) {
            if (tokenLines[i].ignore == false) {
                string label = "";
                DataDirective newDataD;
                newDataD.size = 0;
                string error = "";
                error = checkDataLineSyntaxAndBuildDataDirective(tokenLines[i], label, newDataD);
                if (error == "") {
                    _symbolTable.insert(make_pair(label, address));
                    newDataD.address = address;
                    _dataList.push_back(newDataD);
                    address = address + newDataD.size;
                } else {
                    output.push_back(error);
                }
            }
        }
    }
    return output;
}

vector<string> checkForSemanticErrors (vector<Instruction>& instList, unordered_map<string,int>& symbolTable) {

    vector<string> output;
    for (auto inst : instList) {
        for (auto arg : inst.arguments) {
            unordered_map<string,int>::iterator it = symbolTable.find(arg.name);
            if (it == symbolTable.end()) {
                string error = "Linha " + to_string(inst.originalLineNumber) + ": Erro semantico: simbolo nao definido: " + arg.name;
                output.push_back(error);
            }
        }
    }
    return output;
}