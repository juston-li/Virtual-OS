//
//  Assembler.cpp
//  
/* TODO     
 *      Eric
 *          Write logic to take input from file and run through assembler
 *          The loops for taking in lines from the input file will go in the assembler, not in the OS
 *          Write code to output object code into .o file
 *          Right code to check for comments
 *      Jack
 *          Error handling for invalid inputs
 *          Pushing fixes for negative constants
 *          Dealing with constant and address ranges
*/

#include "Assembler.hpp"
#include <vector>
#include <string>
#include <sstream>

/* Constructor initializes all integer values to 0 so as not to affect sum in Assemble function */
Assembler::Assembler():opcode(0),object_code(0),immediate(0),numRegisters(0),destReg(0),srcReg(0),addr(0),isAddr(0),isConst(0),invalidConstOrAddr(0),invalidInstruct(0),invalidRegister(0),invalidNumArguments(0),input(""){
}
Assembler::~Assembler(){
}
// Retrieves all instructions from assembly file and stores in assemblyInstructs vector
// Also erases any comments within the assembly code
void Assembler::getInput(std::string inFile){
	std::ifstream assemblyFile;
	std::string buff;
	std::size_t found;
	assemblyFile.open(inFile, std::ifstream::in);
    
    while (assemblyFile.good()){
    	getline(assemblyFile, buff);
    	found = buff.find("!");
    	if(found == std::string::npos)
    		assemblyInstructs.push_back(buff);

		else if (found != std::string::npos && found != 0){
			buff.erase(buff.begin() + found, buff.end());
			assemblyInstructs.push_back(buff);
		}
	}
	assemblyFile.close();
}
/* Found this on StackOverflow and haven't tested it yet, but it looked like a cool way to split the input string based on using spaces as delimiters */
void Assembler::splitInput(const std::string &inputString, std::vector<std::string> &elems) {
    std::stringstream ss(inputString);
    std::string buf;
    while (ss>>buf) {
        elems.push_back(buf);
        std::cout<<buf<<std::endl;
    }
    while (ss>>buf) {
        elems.push_back(buf);
    }
    if (elems.size()>3){
        invalidNumArguments = 1;
        std::cerr<<"Invalid number of command line arguments."<<std::endl;
    }
}
/* Takes string representation of operation.  Each if statement governs one or two operations and sets the opcode accordingly, shifting the correct number of bits.  Also sets the number of registers used for that operation and determines if there's an address or constant value. After the if-else if chain, the immediate value is shifted. */
void Assembler::getOperation(const std::string &instruct){
    if ((instruct == "load")||(instruct == "loadi")){
        numRegisters = 1;
        if (instruct == "loadi"){
            isConst = 1;
            immediate = 1;
        }
        else {
            isAddr = 1;
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
            isConst = 1;
        }
        opcode = 2 << 11;
    }
    else if ((instruct == "addc")||(instruct == "addci")){
        numRegisters = 2;
        if (instruct == "addci"){
            numRegisters = 1;
            isConst = 1;
            immediate = 1;
        }
        opcode = 3 << 11;
    }
    else if ((instruct == "sub")||(instruct == "subi")){
        numRegisters = 2;
        if (instruct == "subi"){
            numRegisters = 1;
            isConst = 1;
            immediate = 1;
        }
        opcode = 4 << 11;
    }
    else if ((instruct == "subc")||(instruct == "subci")){
        numRegisters = 2;
        if (instruct == "subci"){
            numRegisters = 1;
            isConst = 1;
            immediate = 1;
        }
        opcode = 5 << 11;
    }
    else if ((instruct == "and")||(instruct == "andi")){
        numRegisters = 2;
        if (instruct == "andi"){
            numRegisters = 1;
            isConst = 1;
            immediate = 1;
        }
        opcode = 6 << 11;
    }
    else if ((instruct == "xor")||(instruct == "xori")){
        numRegisters = 2;
        if (instruct == "xori"){
            numRegisters = 1;
            isConst = 1;
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
            isConst = 1;
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
    else {
        invalidInstruct = 1;
        std::cerr<<"Error: Invalid instruction. " << instruct << " is not a valid instruction." << std::endl;
    }
    
    // Shift of immediate value
    immediate = immediate << 8;
}
/* Takes string of destination register and converts to an int, then shifts the correct number of bits.  Note: This relies on the C++11 function std::stoi. */
void Assembler::getDestRegister(const std::string &registerString){
    for (std::string::const_iterator it = registerString.begin();it != registerString.end(); ++it){
        if (!std::isdigit(*it)){
            invalidRegister  = 1;
            std::cerr<<"Error: Invalid destination register. " << registerString << " is not a valid register." << std::endl;
            return;
        }
    }
    destReg = std::stoi(registerString);
    if ((destReg<0)||(destReg>3)){
        invalidRegister = 1;
        std::cerr<<"Error: Invalid destination register. " << destReg << " is not a valid register." << std::endl;
        return;
    }
    destReg = destReg << 9;
}
/* Same as above, except for the source register. */
void Assembler::getSrcRegister(const std::string &registerString){
    for (std::string::const_iterator it = registerString.begin();it != registerString.end(); ++it){
        if (!std::isdigit(*it)){
            invalidRegister  = 1;
            std::cerr<<"Error: Invalid source register. " << registerString << " is not a valid register." << std::endl;
            return;
        }
    }
    srcReg = std::stoi(registerString);
    if ((srcReg<0)||(srcReg>3)){
        invalidRegister = 1;
        std::cerr<<"Error: Invalid source register. " << srcReg << " is not a valid register." << std::endl;
        return;
    }
    srcReg = srcReg << 6;
}
/* Same as above, except for the address or constant, which does not need to be shifted. */
void Assembler::getAddressOrConstant(const std::string &addrString){
    for (std::string::const_iterator it = addrString.begin();it != addrString.end(); ++it){
        if ((!std::isdigit(*it))&&(*addrString.begin()!='-')){
            invalidConstOrAddr  = 1;
            std::cerr<<"Error: Invalid address or constant value. " << addrString << " is not a valid address or constant value." << std::endl;
            return;
        }
    }
    addr = std::stoi(addrString);
    if (isConst == 1) {
        if ((addr<(-128))||(addr>=128)){
            invalidConstOrAddr = 1;
            std::cerr<<"Error: Constant value out of bounds. " << addr << " is not a valid constant value." << std::endl;
            return;
        }
    }
    else {
        if ((addr<0)||(addr>=256)){
            invalidConstOrAddr = 1;
            std::cerr<<"Error: Address out of bounds. " << addr <<" is not a valid address."<<std::endl;
            return;
        }
    }
    addr = (((unsigned) addr)<<24)>>24;
}
// Returns name of program with the suffix changed to .o
void Assembler::outputFile(string inputName){
	outFile.assign(inputName);
	outFile.erase(outFile.size()-1);
	outFile.append("o");
}
/* Assemble function to use the others to generate the actual object code. Starts by splitting the input string into its components, then find out which operation is to be performed.  This will determine the number of registers involved and whether there's an address or a constant, and Assemble calls the some combination of the three functions above based on that. At the end, we sum all of the parts of object_code together to get the decimal representation.  Note that the components that are unused for that operation are initialized to 0 in the constructor, and will not affect this sum. */
std::string Assembler::Assemble(std::string inputProgram){
	ofstream objFile;

	getInput(inputProgram);
	outputFile(inputProgram);
	objFile.open(outFile);
	for (int i = 0; i < assemblyInstructs.size(); i++){
		isAddr = 0;
		immediate = 0;
		addr = 0;
		destReg = 0;
		srcReg = 0;
		splitInput(assemblyInstructs[i], instructParts);
        if (invalidNumArguments == 1){
            object_code = -1;
			invalidNumArguments = 0;
        }
        getOperation(instructParts.at(0));
        if (invalidInstruct == 1){
            object_code = -1;
			invalidInstruct = 0;
        }
        if (numRegisters > 0){
            getDestRegister(instructParts.at(1));
            if (numRegisters == 2){
                getSrcRegister(instructParts.at(2));
            }
        }
        if (invalidRegister == 1){
            object_code = -1;
			invalidRegister = 0;
        }
        if ((isAddr == 1)||(isConst==1)){
            if (numRegisters == 1){
                getAddressOrConstant(instructParts.at(2));
            }
            else {
                getAddressOrConstant(instructParts.at(1));
            }
			isAddr = 0;
			isConst = 0;
        }
        if (invalidConstOrAddr==1){
            object_code = -1;
        }
		object_code = opcode + immediate + srcReg + destReg + addr;
		objFile << object_code << endl;
		instructParts.clear();
	}
    return outFile;
}