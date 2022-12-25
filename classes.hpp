#ifndef CLASSES_H_
#define CLASSES_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

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

unordered_map<string, InstructionDef> makeInstructionDefTable ();
string translate (vector<Instruction>& instList, vector<DataDirective>& dataList, unordered_map<string,int>& symbolTable);

#endif