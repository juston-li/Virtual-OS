#include <vector>
using namespace std;

class VirtualMachine{
	public:
		VirtualMachine();
		
		void load_mem(string executable);
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
		void shra();
		void compr();
		void compri();
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
		int pc,ir,sr,sp,clock,base,limit;
		//int opcode, rd, immed, rs, addr ,const
};
