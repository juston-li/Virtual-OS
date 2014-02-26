#include <iostream>
#include <fstream>
#include <string>
#include "VirtualMachine.h"
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

VirtualMachine::VirtualMachine() {
	pc = ir = sr = sp = clock = base = limit = 0;
	halt_flag = false;
}

int VirtualMachine::load_mem(string executable) {
	int code;
	mem.resize(260); //max is 256 but buffer in case
	ifstream program(executable.c_str());

	/*set base register*/
	base = 0; //base is always zero since currently only support 1 program loaded

	if (program.is_open()) {
		for(limit = base; program >> code; limit++) {
			cout << code << '\n'; //testing
			mem[limit] = code;
			if (unlikely(limit == 256)) {
				cerr << "Memory overflow\n";  
				return 0;
			}
		}
		program.close();
	} else {
		cerr << "Unable to load program\n";
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
		if (unlikely(pc < base || pc > limit)) {
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
	if( immed == 0 ) {
		r[rd] = costant;
	} else {
		r[rd] = addr;
	}
}

void VirtualMachine::store(){
	mem[addr] = r[rd];
}

void VirtualMachine::add(){
	//TODO: Juston - Add logic for function
}

void VirtualMachine::addc(){
	//TODO: Juston - Add logic for function
}

void VirtualMachine::sub(){
	//TODO: Juston - Add logic for function
}

void VirtualMachine::subc(){
	//TODO: Juston - Add logic for function	
}

void VirtualMachine::and_op(){
	if( immed == 0 ) {
		r[rd] = r[rd] & r[rs];
	} else {
		r[rd] = r[rd] & consant;
	}
}

void VirtualMachine::xor_op(){
	if( immed == 0 ) {
		r[rd] = r[rd] | r[rs];
	} else {
		r[rd] = r[rd] | constant;
	}
}

void VirtualMachine::compl_op(){
	r[rd] = ~r[rd]
}

void VirtualMachine::shl(){
	r[rd] = r[rd] << 1;
}

void VirtualMachine::shla(){
	//TODO - Joe or Juston - Add Logic
}

void VirtualMachine::shr(){
	//TODO - Joe or Juston - Add Logic
}

void VirtualMachine::shra(){
	//TODO - Joe or Juston - Add Logic
}

void VirtualMachine::compr(){
	if( immed == 0 ) {
		if( r[rd] < r[rs] ) {
			LESS = 1 ; EQUAL = 0 ; GREATER = 0; 
		} else if( r[rd] == r[rs] ) {
			EQUAL = 1 ; LESS = 0 ; GREATER = 0;
		} else if( r[rd] > r[rs] ) {
			GREATER = 1 ; EQUAL = 0 ; LESS = 0;
		}
	} else { 
		if( r[rd] < constant ) {
			LESS = 1 ; EQUAL = 0 ; GREATER = 0;
		}
	}
}

void VirtualMachine::getstat(){
	r[rd] = sr;
}

void VirtualMachine::putstat(){
	sr = r[rd];
}

void VirtualMachine::jump(){
	pc = addr;
}

void VirtualMachine::jumpl(){
	if( LESS == 1 ) {
		pc = addr;
	}
}

void VirtualMachine::jumpe(){
	if( EQUAL == 1 ) {
		pc = addr;
	}
}

void VirtualMachine::jumpg(){
	if( GREATER == 1 ) {
		pc = addr;
	}
}

void VirtualMachine::call(){
	//TODO Joe - Add Logic
}

void VirtualMachine::return_op(){
	//TODO Joe - Add Logic
}

void VirtualMachine::read(){
	//TODO Joe - Add Logic
}

void VirtualMachine::write(){
	//TODO Joe - Add Logic
}

void VirtualMachine::halt(){
	halt_flag = true;
}

void VirtualMachine::noop(){
}