#include <iostream>
#include <fstream>
#include <string>
#include "VirtualMachine.h"

VirtualMachine::VirtualMachine() {
	pc = ir = sr = sp = clock = base = limit = 0;
	halt_flag = false;
}

int VirtualMachine::load_mem(string executable) {
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
		cerr << "Unable to load program\n";
		return 0; 
	} 
	if (limit >= 256) { //FIXME:Vector would likely go out of bounds and crash if this is the case, catch earlier
		cerr << "Not enough memory\n";  
		return 0;
	}
	return 1;
}

void VirtualMachine::execute() {
	//array of function pointers
	static instruction instruct[] ={&VirtualMachine::load, &VirtualMachine::store, &VirtualMachine::add, &VirtualMachine::addc,
									&VirtualMachine::sub, &VirtualMachine::subc, &VirtualMachine::and_op, &VirtualMachine::xor_op,
									&VirtualMachine::compl_op, &VirtualMachine::shl, &VirtualMachine::shla, &VirtualMachine::shr,
									&VirtualMachine::shra, &VirtualMachine::compr, &VirtualMachine::getstat, &VirtualMachine::putstat,
									&VirtualMachine::jump, &VirtualMachine::jumpl, &VirtualMachine::jumpe, &VirtualMachine::jumpg,
									&VirtualMachine::call, &VirtualMachine::return_op, &VirtualMachine::read, &VirtualMachine::write,
									&VirtualMachine::halt, &VirtualMachine::noop};

	//while instruction isn't halt or error, run corresponding function for instruction in mem[pc], pc++
	while(halt_flag != true) {
		
		//pc must be within program memory bounds
		if(pc<base || pc > limit) {
			cerr << "Segmentation Fault\n"; 
			break;
		}
		//set IR to current pc, increment pc
		ir = mem[pc];
		pc++;
		
		//parse object code
		opcode = ir >> 11; //15:11
		rd = ir & 0x00000600; //10:9
		rd = rd >> 9;
		immed = ir & 0x00000100; //8
		immed = immed >> 8;
		rs = ir & 0x000000C0; //7:6
		rs = rs >> 6;
		addr = constant = ir & 0x000000FF; //7:0
		if(constant >= 128) { //2's complement, negative
			constant--;
			constant = constant xor 0x000000FF;
			constant *= -1;
		}
		//testing
		cout << opcode << ":" << rd << ":" << immed << ":" << rs << ":" << addr << ":" << constant << "\n";

		//function call
		((*this).*instruct[opcode])();
	}
	
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
void VirtualMachine::shr(){
}
void VirtualMachine::shra(){
}
void VirtualMachine::compr(){
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
	halt_flag = true;
}
void VirtualMachine::noop(){
}
