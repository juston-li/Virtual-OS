//
//  Assembler.hpp
//  

#ifndef ____Assembler__
#define ____Assembler__

#include <iostream>
#include <vector>
#include <string>
class Assembler {
public:
    Assembler();
    ~Assembler();
    void getInput();
    void splitInput(const std::string &inputString, std::vector<std::string> &elems);
    void getOperation(const std::string &instruct);
    void getDestRegister(const std::string &registerString);
    void getSrcRegister(const std::string &registerString);
    void getAddress(const std::string &addrString);
    int Assemble();
private:
    // The original instruction string input to the assembler
    std::string input;
    // A flag flipped if the instruction include an address of constant value
    int isAddr;
    // The decimal representation of the object code
    int object_code;
    // The decimal value of the operation code
    int opcode;
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
    // A vector to hold different parts of the input string
    std::vector<std::string> instructParts;
};
#endif /* defined(____Assembler__) */
