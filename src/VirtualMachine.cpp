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
