//
//  Assembler.cpp
//  


#include "Assembler.hpp"
#include <vector>
#include <string>
#include <sstream>

/* Constructor initializes all integer values to 0 so as not to affect sum in Assemble function */
Assembler::Assembler():opcode(0),object_code(0),immediate(0),numRegisters(0),destReg(0),srcReg(0),addr(0),isAddr(0),input(""){
    std::cout<<"Assembler constructed, initialized\n"<<std::endl;
}
Assembler::~Assembler(){
}
/* We'll probably want to rewrite this to something more sophisticated and workable, but this is just a stand-in for getting input to the assembler */
void Assembler::getInput(){
    getline(std::cin,input,'\n');
    std::cout << input << std::endl;
}
/* Found this on StackOverflow and haven't tested it yet, but it looked like a cool way to split the input string based on using spaces as delimiters */
void Assembler::splitInput(const std::string &inputString, std::vector<std::string> &elems) {
    std::cout<<inputString<<std::endl;
    std::stringstream ss(inputString);
    std::string buf;
    while (ss>>buf) {
        elems.push_back(buf);
        std::cout<<buf<<std::endl;
    }
}
/* Takes string representation of operation.  Each if statement governs one or two operations and sets the opcode accordingly, shifting the correct number of bits.  Also sets the number of registers used for that operation and determines if there's an address or constant value. After the if-else if chain, the immediate value is shifted. */
void Assembler::getOperation(const std::string &instruct){
    if ((instruct == "load")||(instruct == "loadi")){
        numRegisters = 1;
        isAddr = 1;
        if (instruct == "loadi"){
            immediate = 1;
            std::cout<<"operation is loadi \n"<<std::endl;
        }
        opcode = 0 << 11;
    }
    else if ((instruct == "store")){
        isAddr = 1;
        numRegisters = 1;
        opcode = 1 << 11;
    }
    else if ((instruct == "add")||(instruct == "addi")){
        numRegisters = 2;
        if (instruct == "addi"){
            immediate = 1;
            numRegisters = 1;
            isAddr = 1;
        }
        opcode = 2 << 11;
    }
    else if ((instruct == "addc")||(instruct == "addci")){
        numRegisters = 2;
        if (instruct == "addci"){
            numRegisters = 1;
            isAddr = 1;
            immediate = 1;
        }
        opcode = 3 << 11;
    }
    else if ((instruct == "sub")||(instruct == "subi")){
        numRegisters = 2;
        if (instruct == "subi"){
            numRegisters = 1;
            isAddr = 1;
            immediate = 1;
        }
        opcode = 4 << 11;
    }
    else if ((instruct == "subc")||(instruct == "subci")){
        numRegisters = 2;
        if (instruct == "subci"){
            numRegisters = 1;
            isAddr = 1;
            immediate = 1;
        }
        opcode = 5 << 11;
    }
    else if ((instruct == "and")||(instruct == "andi")){
        numRegisters = 2;
        if (instruct == "andi"){
            numRegisters = 1;
            isAddr = 1;
            immediate = 1;
        }
        opcode = 6 << 11;
    }
    else if ((instruct == "xor")||(instruct == "xori")){
        numRegisters = 2;
        if (instruct == "xori"){
            numRegisters = 1;
            isAddr = 1;
            immediate = 1;
        }
        opcode = 7 << 11;
    }
    else if (instruct == "compl"){
        numRegisters = 1;
        opcode = 8 << 11;
    }
    else if (instruct == "shl"){
        numRegisters = 1;
        opcode = 9 << 11;
    }
    else if (instruct == "shla"){
        numRegisters = 1;
        opcode = 10 << 11;
    }
    else if (instruct == "shr"){
        numRegisters = 1;
        opcode = 11 << 11;
    }
    else if (instruct == "shra"){
        numRegisters = 1;
        opcode = 12 << 11;
    }

    else if ((instruct == "compr")||(instruct == "compri")){
        numRegisters = 2;
        if (instruct == "compri"){
            numRegisters = 1;
            isAddr = 1;
            immediate = 1;
        }
        opcode = 13 << 11;
    }
    else if (instruct == "getstat"){
        numRegisters = 1;
        opcode = 14 << 11;
    }
    else if (instruct == "putstat"){
        numRegisters = 1;
        opcode = 15 << 11;
    }
    else if (instruct == "jump"){
        numRegisters = 0;
        isAddr = 1;
        opcode = 16 << 11;
    }
    else if (instruct == "jumpl"){
        numRegisters = 0;
        isAddr = 1;
        opcode = 17 << 11;
    }
    else if (instruct == "jumpe"){
        numRegisters = 0;
        isAddr = 1;
        opcode = 18 << 11;
    }
    else if (instruct == "jumpg"){
        numRegisters = 0;
        isAddr = 1;
        opcode = 19 << 11;
    }
    else if (instruct == "call"){
        numRegisters = 0;
        opcode = 20 << 11;
    }
    else if (instruct == "return"){
        numRegisters = 0;
        opcode = 21 << 11;
    }
    else if (instruct == "read"){
        numRegisters = 1;
        opcode = 22 << 11;
    }
    else if (instruct == "write"){
        numRegisters = 1;
        opcode = 23 << 11;
    }
    else if (instruct == "halt"){
        numRegisters = 0;
        opcode = 24 << 11;
    }
    else if (instruct == "noop"){
        numRegisters = 0;
        opcode = 25 << 11;
    }
    
    // Shift of immediate value
    immediate = immediate << 8;
    std::cout<<"Shifted immediate value\n"<<std::endl;
}
/* Takes string of destination register and converts to an int, then shifts the correct number of bits.  Note: This relies on the C++11 function std::stoi. */
void Assembler::getDestRegister(const std::string &registerString){
    destReg = std::stoi(registerString);
    destReg = destReg << 9;
}
/* Same as above, except for the source register. */
void Assembler::getSrcRegister(const std::string &registerString){
    srcReg = std::stoi(registerString);
    srcReg = srcReg << 6;
}
/* Same as above, except for the address or constant, which does not need to be shifted. */
void Assembler::getAddress(const std::string &addrString){
    addr = std::stoi(addrString);
}
/* Assemble function to use the others to generate the actual object code. Starts by splitting the input string into its components, then fins out which operation is to be performed.  This will determine the number of registers involved and whether there's an address or a constant, and Assemble calls the some combination of the three functions above based on that. At the end, we sum all of the parts of object_code together to get the decimal representation.  Note that the components that are unused for that operation are initialized to 0 in the constructor, and will not affect this sum. */
int Assembler::Assemble(){
    splitInput(input,instructParts);
    getOperation(instructParts.at(0));
    if (numRegisters > 0){
        std::cout << "We have at least one register\n" << std::endl;
        getDestRegister(instructParts.at(1));
        std::cout << "We have retrieved the destination register value\n"<<std::endl;
        if (numRegisters == 2){
            std::cout << "We have at two registers\n" << std::endl;
            getSrcRegister(instructParts.at(2));
        }
    }
    if (isAddr == 1){
        getAddress(instructParts.at(2));
    }
    object_code = opcode + immediate + srcReg + destReg + addr;
    return object_code;
}


