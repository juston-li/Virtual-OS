//
//  Assembler.hpp
//  
//
//  Created by Jack Dempsey on 2/16/14.
//
//

#ifndef ____Assembler__
#define ____Assembler__

#include <iostream>
#include <std.bool.h>
class ASsembler {
public:
    Assembler::Assembler();
    Assembler::~Assember();
    void Assembler::splitInput(const std::string &inputString, std::vector<std::string> &elems);
    void Assembler::getOperation(std::string operationString);
    void Assembler::getRegisters(Std::string registerString);

private:
    int op[5];
    int immediate;
    int numRegisters;
    std::bool isAddr;
    int reg1;
    int reg2;
    int addr;
    vector<std::string> instructParts;
};
#endif /* defined(____Assembler__) */
