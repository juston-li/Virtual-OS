#include <vector>
using namespace std;

class VirtualMachine{
	public:
		VirtualMachine();
		
		void load_mem(string executable);
		void execute();
	private:
		vector<int> mem;
		vector<int> r;
		int pc,ir,sr,sp,clock,base,limit;
		//int opcode, rd, immed, rs, addr ,const
};
