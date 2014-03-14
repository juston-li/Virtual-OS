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
	r.assign(4,0); 
	mem.assign(260,0); //max is 256 but buffer in case
}

int VirtualMachine::load_mem(string executable) {
	int code;
	this->filename = executable.substr(0, executable.size()-2); 
	ifstream program(executable.c_str());

	/*set base register*/
	base = 0; //base is always zero since currently only support 1 program loaded

	if (program.is_open()) {
		for(limit = base; program >> code; limit++) {
			//cout << code << '\n'; //testing
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
		//cout << opcode << ":" << rd << ":" << immed << ":" << rs << ":" << addr << ":" << constant << "\n";

		//function call
		((*this).*instruct[opcode])();
	}
	
}

void VirtualMachine::load() {
	if( immed == 0 ) {
		clock+=1;
		r[rd] = mem[addr];
	} else {
		clock+=4;
		r[rd] = constant;
	}
}

void VirtualMachine::store(){
	clock+=1;
	mem[addr] = r[rd];
}

void VirtualMachine::add(){
	if(immed == 0) {
		r[rd] = r[rd] + r[rs];
	} else if (immed == 1) {
		r[rd] = r[rd] + constant;
	}
	//check carry flag
	if(r[rd] & 0x00010000) {
		sr = sr | 0x00000001;
	} else {
		sr = sr & 0x0000001E;
	}
	//check for overflow
	if(r[rd] >= 32767 || r[rd] <= -32768) {
		sr = sr | 0x00000010; //set overflow bit to 1
	} 
	//sign extend, only care about first 16 bits
	if(r[rd] & 0x00008000) {//leading bit is 1
		r[rd] = r[rd] | 0xFFFF0000; //sign extend negative 
	} else {				//leading bit is 0
		r[rd] = r[rd] & 0x0000FFFF; //sign extend positive
	}
}

void VirtualMachine::addc(){
	if(immed == 0) {
		r[rd] = r[rd] + r[rs];
	} else if (immed == 1) {
		r[rd] = r[rd] + constant;
	}
	//check carry flag
	if(r[rd] & 0x00010000) {
		sr = sr | 0x00000001;
	} else {
		sr = sr & 0x0000001E;
	}
	//check carry flag
	if(r[rd] & 0x00010000) {
		sr = sr | 0x00000001;
	}
	//check for overflow
	if(r[rd] >= 32767 || r[rd] <= -32768) {
		sr = sr | 0x00000010; //set overflow bit to 1
	} 
	//sign extend
	if(r[rd] & 0x00008000) {//leading bit is 1
		r[rd] = r[rd] | 0xFFFF0000; //sign extend negative 
	} else {				//leading bit is 0
		r[rd] = r[rd] & 0x0000FFFF; //sign extend positive
	}
}

void VirtualMachine::sub(){
	if(immed == 0) {
		r[rd] = r[rd] - r[rs];
	} else if (immed == 1) {
		r[rd] = r[rd] - constant;
	}
	//check carry flag
	if(r[rd] & 0x00010000) {
		sr = sr | 0x00000001;
	} else {
		sr = sr & 0x0000001E;
	}
	//check for overflow
	if(r[rd] >= 32767 || r[rd] <= -32768) {
		sr = sr | 0x00000010; //set overflow bit to 1
	} 
	//sign extend, only care about first 16 bits
	if(r[rd] & 0x00008000) {//leading bit is 1
		r[rd] = r[rd] | 0xFFFF0000; //sign extend negative 
	} else {				//leading bit is 0
		r[rd] = r[rd] & 0x0000FFFF; //sign extend positive
	}
}

void VirtualMachine::subc(){
	if(immed == 0) {
		r[rd] = r[rd] - r[rs];
	} else if (immed == 1) {
		r[rd] = r[rd] - constant;
	}
	//add carry
	if(sr & 0x00000001) {
		r[rd] = r[rd] - 32768;
	}
	//check carry flag
	if(r[rd] & 0x00010000) {
		sr = sr | 0x00000001;
	} else {
		sr = sr & 0x0000001E;
	}
	//check for overflow
	if(r[rd] >= 32767 || r[rd] <= -32768) {
		sr = sr | 0x00000010; //set overflow bit to 1
	} 
	//sign extend
	if(r[rd] & 0x00008000) {//leading bit is 1
		r[rd] = r[rd] | 0xFFFF0000; //sign extend negative 
	} else {				//leading bit is 0
		r[rd] = r[rd] & 0x0000FFFF; //sign extend positive
	}
}

void VirtualMachine::and_op(){
	clock+=1;
	if( immed == 0 ) {
		r[rd] = r[rd] & r[rs];
	} else {
		r[rd] = r[rd] & constant;
	}
}

void VirtualMachine::xor_op(){
	clock+=1;
	if( immed == 0 ) {
		r[rd] = r[rd] ^ r[rs];
	} else {
		r[rd] = r[rd] ^ constant;
	}
}

void VirtualMachine::compl_op(){
	clock+=1;
	r[rd] = ~r[rd];
}

void VirtualMachine::shl(){
	clock+=1;

	/* Set the carry bit */	
	if( /*1000000000000000*/ (0x00008000 & r[rd]) ) {
		sr = sr | 0x00000001; //0000000000011111
	} else {
		sr = sr & 0x0000001E; //0000000000011110
	}
	r[rd] = r[rd] << 1;
	//anything beyond the 16th should only be sign extend
	if( /*1000000000000000*/ (0x00008000 & r[rd]) ) {
		r[rd] = r[rd] | 0xFFFF0000; //0000000000011111
	} else {
		r[rd] = r[rd] & 0x0000FFFF; //0000000000011110
	}
}

void VirtualMachine::shla(){
	clock+=1;

	/* Set the carry bit */
	if( /*1000000000000000*/ 0x00008000 & r[rd]) {
		sr = sr | 0x00000001; //0000000000011111
	} else {
		sr = sr & 0x0000001E; //0000000000011110
	}
	r[rd] = r[rd] << 1;
	//anything beyond the 16th should only be sign extend
	if(0x00008000 & r[rd]) {
		r[rd] = r[rd] | 0xFFFF0000;
	} else {
		r[rd] = r[rd] & 0x0000FFFF;
	}
}

void VirtualMachine::shr(){
	clock+=1;
	
	/* Set the carry bit */
	if( /*0000000000000001*/ 0x00000001 & r[rd]) {
		sr = sr | 0x00000001; //0000000000011111
	} else {
		sr = sr & 0x0000001E; //0000000000011110
	}

	/*shr pushes a 0 into the 16th bit which makes this 
	 *operation awkward as we are using 32bit hex literals */
	r[rd] = r[rd] & 0x0000FFFF;
	r[rd] = r[rd] >> 1;
}

void VirtualMachine::shra(){
	clock+=1;

	/* Set the carry bit */
	if( /*0000000000000001*/ 0x00000001 & r[rd]) {
		sr = sr | 0x00000001; //0000000000011111
	} else {
		sr = sr & 0x0000001E; //0000000000011110
	}
	/* C++ default int type is signed so sign extension happens automatically with a right shift. */
	r[rd] = r[rd] >> 1;
}

void VirtualMachine::compr(){
	clock+=1;
	if( immed == 0 ) {
		if( r[rd] < r[rs] ) {
			sr = sr | 0x00000008; //01000
			sr = sr & 0x00000019; //11001
		} else if( r[rd] == r[rs] ) {
			sr = sr | 0x00000004; //00100
			sr = sr & 0x00000015; //10101
		} else if( r[rd] > r[rs] ) {
			sr = sr | 0x00000002; //00010
			sr = sr & 0x00000013; //10011
		}
	} else { 
		if( r[rd] < constant ) {
			sr = sr | 0x00000008; //01000
			sr = sr & 0x00000019; //11001
		} else if( r[rd] == constant ) {
			sr = sr | 0x00000004; //00100
			sr = sr & 0x00000015; //10101
		} else if( r[rd] > constant  ) {
			sr = sr | 0x00000002; //00010
			sr = sr & 0x00000013; //10011
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
	if( (sr & 0x00000008) >= 1 ) { //0000000000001000
		pc = addr;
	}
}

void VirtualMachine::jumpe(){
	clock+=1;
	if( (sr & 0x00000004) >= 1 ) { //0000000000000100
		pc = addr;
	}
}

void VirtualMachine::jumpg(){
	clock+=1;
	if( (sr & 0x00000002) >= 1 ) { //0000000000000010
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
		cerr << "Segmentation Fault[call]\n";
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
		cerr << "Segmentation Fault[return]\n";
		exit(EXIT_FAILURE);
	}
}

void VirtualMachine::read(){
	clock += 28;
	//Writing this with the assumption that the .in file has only one value in it to read in per program, removing the necessity for a line pointer
	
	std::ifstream input;
	//std::cout << filename+".in";
	input.open(filename+".in", std::ifstream::in);
	if( input.good() ) {
		r[rd] = input.get() - '0';
	}
}

void VirtualMachine::write(){
	clock += 28;

	std::ofstream output;
	output.open(filename+".out", std::ofstream::out | std::ofstream::app);
	if( output.good() )
		output << "Output: " << r[rd] << std::endl;
}

void VirtualMachine::halt(){
	clock+=1;
	std::ofstream output;
	output.open(filename+".out", std::ofstream::out | std::ofstream::app);
	if( output.good() )
		output << "Clock: " << clock << std::endl;
	halt_flag = true;
}

void VirtualMachine::noop(){
	clock+=1;
}

/* Helper functions for call and return instructions */
bool VirtualMachine::stackEmpty() {
	return (sp > 250);
}

bool VirtualMachine::stackFull() {
	return (sp <= limit);
}

#ifdef TESTING
void VirtualMachine::set_mem(int address, int value){
	mem[address] = value;
}
void VirtualMachine::set_reg(int reg, int value){
	r[reg] = value;
}
void VirtualMachine::set_pc(int value){
	pc = value;
}
void VirtualMachine::set_sr(int value){
	sr = value;
}
void VirtualMachine::set_sp(int value){
	sp = value;
}
void VirtualMachine::set_clock(int value){
	clock = value;
}
void VirtualMachine::set_rd(int value){
	rd = value;
}
void VirtualMachine::set_immed(int value){
	immed = value;
}
void VirtualMachine::set_rs(int value){
	rs = value;
}
void VirtualMachine::set_addr(int value){
	addr = value;
}
void VirtualMachine::set_constant(int value){
	constant = value;
}
void VirtualMachine::set_halt_flag(bool value){
	halt_flag = value;
}
int VirtualMachine::get_mem(int address){
	return mem[address];
}
int VirtualMachine::get_reg(int reg){
	return r[reg];
}
int VirtualMachine::get_pc(){
	return pc;
}
int VirtualMachine::get_sr(){
	return sr;
}
int VirtualMachine::get_sp(){
	return sp;
}
int VirtualMachine::get_clock(){
	return clock;
}
int VirtualMachine::get_rd(){
	return rd;
}
int VirtualMachine::get_immed(){
	return immed;
}
int VirtualMachine::get_rs(){
	return rs;
}
int VirtualMachine::get_addr(){
	return addr;
}
int VirtualMachine::get_constant(){
	return constant;
}
bool VirtualMachine::get_halt_flag(){
	return halt_flag;
}
#endif
