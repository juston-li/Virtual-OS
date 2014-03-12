#include <vector>
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
