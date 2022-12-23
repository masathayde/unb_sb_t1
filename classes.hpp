#include <string>
#include <vector>

using namespace std;


class SymbolTable {};


class Instruction {



 public:
    string name;
    int code;
    int line;
    vector<string> arguments;
    
    virtual string convertToText ();
    string convertToMachineCode (SymbolTable table);

};

string Instruction::convertToText() {

    string output = name;
    if (arguments.size() > 0) {
        output = output + " " + arguments[0];
        if (arguments.size() > 1) {
            output = output + "," + arguments[1];
        }
    }
    return output;
}

string Instruction::convertToMachineCode(SymbolTable table) {

    string output = to_string(code);
    int address = 0;
    if (arguments.size() > 0) {
        int address = table.getAddress(arguments[0]);
        output = output + " " + to_string(address);
        if (arguments.size() > 1) {
            int address = table.getAddress(arguments[1]);
            output = output + " " + to_string(address);
        }   
    }
    return output;
} 
