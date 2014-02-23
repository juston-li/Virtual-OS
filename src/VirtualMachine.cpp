#include <iostream>
#include <fstream>
#include <string>
#include "VirtualMachine.h"

VirtualMachine::VirtualMachine() {
	//set registers and clock to starting values
}

void VirtualMachine::load_mem(string executable) {
	int code;
	mem.resize(256);
	ifstream program(executable.c_str());

	/*set base register*/
	base = 0; //base is always zero since currently only support 1 program loaded

	if (program.is_open()) {
		for(int i = 0; program >> code; i++) {
			cout << code << '\n'; //testing
			mem[i] = code;
			limit = i; //set the limit register
		}
		program.close();
	} else {
		cerr << "Unable to load program";
	} 
	if (limit >= 256) {
		cerr << "Not enough memory";
	}
}

void VirtualMachine::execute() {
	//while instruction isn't halt or error, run corresponding function for instruction in mem[i], i++
	// use shifts and & to parse instruction
	//opcode = opcode >> 11
	//rd = rd & 0x00000300 then rd >> 9 
	//
	// array of function pointers?  instruction[opcode] = function
}
void VirtualMachine::load() {
}
void VirtualMachine::store(){
}
void VirtualMachine::add(){
}
void VirtualMachine::addc(){
}
void VirtualMachine::sub(){
}
void VirtualMachine::subc(){
}
void VirtualMachine::and_op(){
}
void VirtualMachine::xor_op(){
}
void VirtualMachine::compl_op(){
}
void VirtualMachine::shl(){
}
void VirtualMachine::shla(){
}
void VirtualMachine::shra(){
}
void VirtualMachine::compr(){
}
void VirtualMachine::compri(){
}
void VirtualMachine::getstat(){
}
void VirtualMachine::putstat(){
}
void VirtualMachine::jump(){
}
void VirtualMachine::jumpl(){
}
void VirtualMachine::jumpe(){
}
void VirtualMachine::jumpg(){
}
void VirtualMachine::call(){
}
void VirtualMachine::return_op(){
}
void VirtualMachine::read(){
}
void VirtualMachine::write(){
}
void VirtualMachine::halt(){
}
void VirtualMachine::noop(){
}
