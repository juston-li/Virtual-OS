//
//  Assembler.hpp
//  

#ifndef ____Assembler__
#define ____Assembler__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
class Assembler {
public:
    Assembler();
    ~Assembler();
    void getInput(std::string inFile);
    void splitInput(const std::string &inputString, std::vector<std::string> &elems);
    void getOperation(const std::string &instruct);
    void getDestRegister(const std::string &registerString);
    void getSrcRegister(const std::string &registerString);
    void getAddress(const std::string &addrString);
    string outputFile(string inputName);
    string Assemble(string inputProgram);
private:
    // The decimal value of the operation code
    int opcode;
    // The decimal representation of the object code
    int object_code;
    // The decimal value of the immediate value
    int immediate;
    // How many registers are used in the instruction
    int numRegisters;
    // The decimal value of the destination register
    int destReg;
    // The decimal value of the source register
    int srcReg;
    // The decimal value of the constant or address
    int addr;
    // A flag flipped if the instruction include an address of constant value
    int isAddr;
    // The original instruction string input to the assembler
    std::string input;
    // A vector to hold different parts of the input string
    std::vector<std::string> instructParts;
    // Object code file, ending with .o
    std::string outFile;
    // Vector of each instruction in assembly .s file
    std::vector<std::string> assemblyInstructs;
};
#endif /* defined(____Assembler__) */
