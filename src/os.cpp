#include <iostream>
#include <fstream>
#include <string>
#include "VirtualMachine.h"
using namespace std;

int main(int argc,char *argv[]) {
	int str_size;
	string program = argv[1];
	//Assembler as;
	VirtualMachine vm;
	if( argc != 2 ) {
		cerr << "Error: no input program" << std::endl;
		cerr << "Usage: " << argv[0] << " prog.s" << std::endl;
		return 1;
	}
	//Assemble program creates .o file
	//as.run();
	str_size = program.size();
	program.replace(str_size-1,1,"o"); //change to .o
	vm.load_mem(program);
	//vm.execute();
}


