#ifndef VIRTUALMACHINE_H_
#define VIRTUALMACHINE_H_
#include <vector>
#include <string>
using namespace std;

class VirtualMachine{
	public:
		VirtualMachine();
		
		int load_mem(string executable);
		void execute();
		void load();
		void store();
		void add();
		void addc();
		void sub();
		void subc();
		void and_op();
		void xor_op();
		void compl_op();
		void shl();
		void shla();
		void shr();
		void shra();
		void compr();
		void getstat();
		void putstat();
		void jump();
		void jumpl();
		void jumpe();
		void jumpg();
		void call();
		void return_op();
		void read();
		void write();
		void halt();
		void noop();
#ifdef TESTING
		void set_mem(int address, int value);
		void set_reg(int reg, int value);
		void set_pc(int value);
		void set_sr(int value);
		void set_sp(int value);
		void set_clock(int value);
		void set_rd(int value);
		void set_immed(int value);
		void set_rs(int value);
		void set_addr(int value);
		void set_constant(int value);
		void set_halt_flag(bool value);
		int get_mem(int address);
		int get_reg(int reg);
		int get_pc();
		int get_sr();
		int get_sp();
		int get_clock();
		int get_rd();
		int get_immed();
		int get_rs();
		int get_addr();
		int get_constant();
		bool get_halt_flag();
#endif
	private:
		vector<int> mem;
		vector<int> r;
		typedef void (VirtualMachine::*instruction)();
		int pc;
		int ir;
		int sr;
		int sp;
		int clock;
		int base;
		int limit;
		int opcode;
		int rd;
		int immed;
		int rs;
		int addr;
		int constant;
		bool halt_flag;
		// The name of the file being executed. Used for read and write instructions
    	std::string filename;
    	bool stackFull();
    	bool stackEmpty();
};
#endif
