#ifndef CLASSES_H_
#define CLASSES_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;


class SymbolTable {};


class Argument {
 public:
    string name;
    int modifier {0};
};

class InstructionDef {
 public:
    string name {""};
    int argumentCount;
    int code;
};

class Instruction {
 public:
    InstructionDef definition;
    int originalLineNumber {0};
    int address {0};
    vector<Argument> arguments;
};

class DataDirective {
 public:
    int address {0};
    int value {0};
    int size {0};
};

// string Instruction::convertToText() {

//     string output = name;
//     if (arguments.size() > 0) {
//         output = output + " " + arguments[0];
//         if (arguments.size() > 1) {
//             output = output + "," + arguments[1];
//         }
//     }
//     return output;
// }

// string Instruction::convertToMachineCode(SymbolTable table) {

//     string output = to_string(code);
//     int address = 0;
//     if (arguments.size() > 0) {
//         int address = table.getAddress(arguments[0]);
//         output = output + " " + to_string(address);
//         if (arguments.size() > 1) {
//             int address = table.getAddress(arguments[1]);
//             output = output + " " + to_string(address);
//         }   
//     }
//     return output;
// } 

unordered_map<string, InstructionDef> makeInstructionDefTable () {
    unordered_map<string,InstructionDef> output;
    ifstream file;
    file.open("instructions.txt");
    if (file.is_open()) {
        string lineRead = "";
        while (!file.eof()) {
            getline(file, lineRead);
            if (lineRead[0] != ';') {
                stringstream ss(lineRead);
                string name;
                int code;
                int argCount;
                ss >> name >> code >> argCount;
                InstructionDef newInstructionDef;
                newInstructionDef.name = name;
                newInstructionDef.argumentCount = argCount;
                newInstructionDef.code = code;
                output.insert(make_pair(name,newInstructionDef));
            }
        }
    }
    return output;
}

string translate (vector<Instruction>& instList, vector<DataDirective>& dataList, unordered_map<string,int>& symbolTable) {
    string output = "";
    for (auto instruction : instList) {
        output = output + to_string(instruction.definition.code) + " ";
        for (auto arg : instruction.arguments) {
            unordered_map<string,int>::iterator it =  symbolTable.find(arg.name);
            int value = it->second + arg.modifier;
            output = output + to_string(value) + " ";
        }
    }
    for (auto dataD : dataList) {
        for (int i = 0; i < dataD.size; ++i) {
            output = output + to_string(dataD.value) + " ";
        }
    }
    return output;
}

#endif