#include <iostream>
#include <fstream>
#include <string>
#include "Assembler.hpp"
#include "VirtualMachine.h"
using namespace std;

/*
 *	TODO
 *		Write file to test out each individual function for expected input
 *
 *		Write file to test for each assembler parsing case
 */

int main(int argc,char *argv[]) {
	int str_size;
	string program = argv[1];
	Assembler as;
	VirtualMachine vm;
	if( argc != 2 ) {
		cerr << "Error: no input program" << std::endl;
		cerr << "Usage: " << argv[0] << " prog.s" << std::endl;
		return 1;
	}
	
	as.Assemble(program);
	str_size = program.size();
	program.replace(str_size-1,1,"o"); //change to .o
	if(vm.load_mem(program)) { //Returns 0 if prog not found or not enough mem
		vm.execute();
	}
}
