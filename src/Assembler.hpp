//
//  Assembler.hpp
//  

#ifndef ____Assembler__
#define ____Assembler__

#include <iostream>
#include <std.bool.h>
class Assembler {
public:
    Assembler::Assembler();
    Assembler::~Assember();
    void Assembler::getInput();
    void Assembler::splitInput(const std::string &inputString, std::vector<const std::string> &elems);
    void Assembler::getOperation(const std::string &operationString);
    void Assembler::getDestRegister(const std::string &registerString);
    void Assembler::getSrcRegister(const std::string &registerString);
    void Assembler::getAddress(const std::string &addrString);
    int Assembler::Assemble();
private:
    // The original instruction string input to the assembler
    std:string input;
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
    vector<const std::string> instructParts;
};
#endif /* defined(____Assembler__) */
