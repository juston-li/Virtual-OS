#include <iostream>
#include <fstream>
#include <string>
#include "VirtualMachine.h"
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

VirtualMachine::VirtualMachine() {
	pc = ir = sr = clock = base = limit = 0;
	sp = 256;
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
			exit(EXIT_FAILURE);
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
		clock+=1;
		r[rd] = costant;
	} else {
		clock+=4;
		r[rd] = addr;
	}
}

void VirtualMachine::store(){
	clock+=1;
	mem[addr] = r[rd];
}

void VirtualMachine::add(){
	clock+=1;
	//TODO: Juston - Add logic for function
}

void VirtualMachine::addc(){
	clock+=1;
	//TODO: Juston - Add logic for function
}

void VirtualMachine::sub(){
	clock+=1;
	//TODO: Juston - Add logic for function
}

void VirtualMachine::subc(){
	clock+=1;
	//TODO: Juston - Add logic for function	
}

void VirtualMachine::and_op(){
	clock+=1;
	if( immed == 0 ) {
		r[rd] = r[rd] & r[rs];
	} else {
		r[rd] = r[rd] & consant;
	}
}

void VirtualMachine::xor_op(){
	clock+=1;
	if( immed == 0 ) {
		r[rd] = r[rd] | r[rs];
	} else {
		r[rd] = r[rd] | constant;
	}
}

void VirtualMachine::compl_op(){
	clock+=1;
	r[rd] = ~r[rd]
}

void VirtualMachine::shl(){
	clock+=1;
	r[rd] = r[rd] << 1;
}

void VirtualMachine::shla(){
	clock+=1;
	
}

void VirtualMachine::shr(){
	clock+=1;

}

void VirtualMachine::shra(){
	clock+=1;

}

void VirtualMachine::compr(){
	clock+=1;
	if( immed == 0 ) {
		if( r[rd] < r[rs] ) {
			sr = sr & 0000000000011001; 
		} else if( r[rd] == r[rs] ) {
			sr = sr & 0000000000010101;
		} else if( r[rd] > r[rs] ) {
			sr = sr & 0000000000010011;
		}
	} else { 
		if( r[rd] < constant ) {
			sr = sr & 0000000000011001;
		}
	}
}

void VirtualMachine::getstat(){
	clock+=1;
	r[rd] = sr;
}

void VirtualMachine::putstat(){
	clock+=1;
	sr = r[rd];
}

void VirtualMachine::jump(){
	clock+=1;
	pc = addr;
}

void VirtualMachine::jumpl(){
	clock+=1;
	if( sr & 0000000000001000 >= 1 ) {
		pc = addr;
	}
}

void VirtualMachine::jumpe(){
	clock+=1;
	if( sr & 0000000000000100 >= 1 ) {
		pc = addr;
	}
}

void VirtualMachine::jumpg(){
	clock+=1;
	if( sr & 0000000000000010 >= 1 ) {
		pc = addr;
	}
}

void VirtualMachine::call(){
	clock+=1;
	
	if( stackFull() == false ) {
		mem[sp] = pc;
		sp--;
		mem[sp] = r[0];
		sp--;
		mem[sp] = r[1];
		sp--;
		mem[sp] = r[2];
		sp--;
		mem[sp] = r[3];
		sp--;
		mem[sp] = sr;
		sp--;
		pc = addr;
	} else {
		cerr << "Segmentation Fault\n";
		exit(EXIT_FAILURE);		
	}
}

void VirtualMachine::return_op(){
	clock+=1;
	
	if( stackEmpty() == false ) {
		sp++;
		sr = mem[sp];
		sp++;
		r[3] = mem[sp];
		sp++;
		r[2] = mem[sp];
		sp++;
		r[1] = mem[sp];
		sp++;
		r[0] = mem[sp];
		sp++;
		pc = mem[sp];
	} else {
		cerr << "Segmentation Fault\n";
		exit(EXIT_FAILURE);
	}
}

void VirtualMachine::read(){
	clock += 28;
	//Writing this with the assumption that the .in file has only one value in it to read in per program, removing the necessity for a line pointer
	
	std::ifstream input;
	input.open(filename."in", std::ifstream::in);
	if( input.good() ) {
		r[rd] = input.get();
	}
}

void VirtualMachine::write(){
	clock += 28;

	std::ofstream output;
	output.open(filename."out", std::ofstream::out | std::ofstream::app);
	if( output.good() )
		output << r[rd] << std::endl;
}

void VirtualMachine::halt(){
	clock+=1;
	halt_flag = true;
}

void VirtualMachine::noop(){
	clock+=1;
}

/* Helper functions for call and return instructions */
bool VirtualMaciine::stackEmpty() {
	return sp >= 250;
}

bool VirtualMacine::stackFull() {
	return sp <= limit;
}