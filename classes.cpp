#include "classes.hpp"

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
            unordered_map<string,int>::iterator it = symbolTable.find(arg.name);
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