#include "../src/VirtualMachine.h"
#include "gtest/gtest.h"

class VirtualMachineTest : public testing::Test {
	protected:
	virtual void SetUp(){
		vm.set_rd(0);
		vm.set_rs(0);
		vm.set_immed(0);
		vm.set_constant(0);
		vm.set_addr(0);
	}
	VirtualMachine vm;
};
class VirtualMachineParamTest : public VirtualMachineTest, public ::testing::WithParamInterface<int>  {
	protected:
	virtual void SetUp(){	
	}
	VirtualMachine vm;
};
//INSTANTIATE_TEST_CASE_P(IntName, VirtualMachineParamTest, ::testing::Values(0,1,2,3));
TEST_F(VirtualMachineParamTest, load){
	/* Load from memory cases */
	// Load 1 from Mem 100 into Register 0
	vm.set_rd(0);
	vm.set_addr(100);
	vm.set_mem(100,1);
	vm.load();
	EXPECT_EQ(1,vm.get_reg(0));

	// Load -2 from Mem 100 into Register 0 - Make sure overwrites
	vm.set_mem(100,-2);
	vm.load();
	EXPECT_EQ(-2,vm.get_reg(0));

	// Range check- max register is 3, load 2 from mem 100 into Register 3
	vm.set_rd(3);
	vm.load();
	EXPECT_EQ(-2,vm.get_reg(3));

	/*Load Immediate test cases*/
	//Load 11 from constant into Reg 1
	vm.set_immed(1);
	vm.set_constant(11);
	vm.set_rd(1);
	vm.load();
	EXPECT_EQ(11,vm.get_reg(1));

	//Negative constant, Load -11 from constant into Reg 1
	vm.set_constant(-11);
	vm.set_rd(2);
	vm.load();
	EXPECT_EQ(-11,vm.get_reg(2));
}
TEST_F(VirtualMachineTest, store){
	// Store 1 into Mem 100
	vm.set_rd(0);
	vm.set_reg(0,1);
	vm.set_addr(100);
	vm.store();
	EXPECT_EQ(1,vm.get_mem(100));

	// Store -2 into Mem 100- Make sure overwrites
	vm.set_reg(0,-1);
	vm.store();
	EXPECT_EQ(-1,vm.get_mem(100));
	
	// Range check, Min is 0. Store 1 in Mem 0
	vm.set_reg(0,1);
	vm.set_addr(0);
	vm.store();
	EXPECT_EQ(1,vm.get_mem(0));

	// Range check, Max is 255. Store 1 in Mem 255
	vm.set_addr(255);
	vm.store();
	EXPECT_EQ(1,vm.get_mem(255));
	
}
TEST_F(VirtualMachineTest, add){
	/*Add from Register cases*/
	//Basic add cases
	vm.set_rd(0);
	vm.set_rs(1);
	vm.set_reg(0,100);
	vm.set_reg(1,200);
	vm.add();
	EXPECT_EQ(300,vm.get_reg(0));
	vm.set_reg(1,-400);	
	vm.add();
	EXPECT_EQ(-100,vm.get_reg(0));
	vm.set_reg(1,-100);
	vm.add();
	EXPECT_EQ(-200,vm.get_reg(0));

	/*Add from Immediate cases*/
	//More basic cases
	vm.set_immed(1);
	vm.set_constant(-100);	
	vm.add();
	EXPECT_EQ(-300,vm.get_reg(0));
	vm.set_constant(400);
	vm.add();
	EXPECT_EQ(100,vm.get_reg(0));
	vm.set_constant(200);
	vm.add();
	EXPECT_EQ(300,vm.get_reg(0));

	//Overflow handing
	vm.set_sr(0);
	vm.set_reg(0,32767);
	vm.set_constant(1);
	vm.add();
	int overflow = 0x00000010 & vm.get_sr();
	EXPECT_EQ(16,overflow);
	EXPECT_EQ(-32768,vm.get_reg(0));
	vm.set_constant(-32768);
	vm.add();
	EXPECT_EQ(0,vm.get_reg(0));
	int carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1,carry);

}
TEST_F(VirtualMachineTest, addc){
	/*Add from Register cases*/
	//Basic add cases
	vm.set_rd(0);
	vm.set_rs(1);
	vm.set_reg(0,100);
	vm.set_reg(1,200);
	vm.addc();
	EXPECT_EQ(300,vm.get_reg(0));
	vm.set_reg(1,-400);	
	vm.addc();
	EXPECT_EQ(-100,vm.get_reg(0));
	vm.set_reg(1,-100);
	vm.addc();
	EXPECT_EQ(-200,vm.get_reg(0));

	/*Add from Immediate cases*/
	//More basic cases
	vm.set_immed(1);
	vm.set_constant(-100);	
	vm.addc();
	EXPECT_EQ(-300,vm.get_reg(0));
	vm.set_constant(400);
	vm.addc();
	EXPECT_EQ(100,vm.get_reg(0));
	vm.set_constant(200);
	vm.addc();
	EXPECT_EQ(300,vm.get_reg(0));

	//Overflow handing
	vm.set_sr(0);
	vm.set_reg(0,32767);
	vm.set_constant(1);
	vm.addc();
	int overflow = 0x00000010 & vm.get_sr();
	EXPECT_EQ(16,overflow);
	EXPECT_EQ(-32768,vm.get_reg(0));
	vm.set_constant(-32768);
	vm.addc();
	EXPECT_EQ(0,vm.get_reg(0));
	int carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1,carry);
	vm.set_constant(32768);
	vm.addc();
	EXPECT_EQ(-32768,vm.get_reg(0));
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0,carry);
}
TEST_F(VirtualMachineTest, sub){
	/*Sub from Register cases*/
	//Basic Sub cases
	vm.set_rd(0);
	vm.set_rs(1);
	vm.set_reg(0,100);
	vm.set_reg(1,200);
	vm.sub();
	EXPECT_EQ(-100,vm.get_reg(0));
	vm.set_reg(1,-200);	
	vm.sub();
	EXPECT_EQ(100,vm.get_reg(0));
	vm.set_reg(1,-100);
	vm.sub();
	EXPECT_EQ(200,vm.get_reg(0));

	/*Add from Immediate cases*/
	//More basic cases
	vm.set_immed(1);
	vm.set_constant(250);	
	vm.sub();
	EXPECT_EQ(-50,vm.get_reg(0));
	vm.set_constant(100);
	vm.sub();
	EXPECT_EQ(-150,vm.get_reg(0));
	vm.set_constant(-200);
	vm.sub();
	EXPECT_EQ(50,vm.get_reg(0));
	
	//Overflow handing
	vm.set_sr(0);
	vm.set_reg(0,-32768);
	vm.set_constant(1);
	vm.sub();
	int overflow = 0x00000010 & vm.get_sr();
	EXPECT_EQ(16,overflow);
	EXPECT_EQ(32767,vm.get_reg(0));
	vm.set_constant(-1);
	vm.sub();
	EXPECT_EQ(-32768,vm.get_reg(0));
}
TEST_F(VirtualMachineTest, subc){
	/*Sub from Register cases*/
	//Basic Sub cases
	vm.set_rd(0);
	vm.set_rs(1);
	vm.set_reg(0,100);
	vm.set_reg(1,200);
	vm.set_sr(0);
	vm.subc();
	EXPECT_EQ(-100,vm.get_reg(0));
	vm.set_reg(1,-200);	
	vm.set_sr(0);
	vm.subc();
	EXPECT_EQ(100,vm.get_reg(0));
	vm.set_reg(1,-100);
	vm.set_sr(0);
	vm.subc();
	EXPECT_EQ(200,vm.get_reg(0));

	/*Add from Immediate cases*/
	//More basic cases
	vm.set_immed(1);
	vm.set_constant(250);	
	vm.set_sr(0);
	vm.subc();
	EXPECT_EQ(-50,vm.get_reg(0));
	vm.set_constant(100);
	vm.set_sr(0);
	vm.subc();
	EXPECT_EQ(-150,vm.get_reg(0));
	vm.set_constant(-200);
	vm.set_sr(0);
	vm.subc();
	EXPECT_EQ(50,vm.get_reg(0));
	
	//Overflow handing
	vm.set_sr(0);
	vm.set_reg(0,-32768);
	vm.set_constant(1);
	vm.subc();
	int overflow = 0x00000010 & vm.get_sr();
	EXPECT_EQ(16,overflow);
	EXPECT_EQ(32767,vm.get_reg(0));
	vm.set_constant(-1);
	vm.set_sr(0);
	vm.subc();
	EXPECT_EQ(-32768,vm.get_reg(0));
	vm.set_sr(1);
	vm.set_reg(0,32768);
	vm.set_constant(0);
	vm.subc();
	EXPECT_EQ(0,vm.get_reg(0));
	
}
TEST_F(VirtualMachineTest, and_op){
	/*And with Register cases*/
	vm.set_rd(0);
	vm.set_rs(1);
	vm.set_reg(0,0x000000AA);
	vm.set_reg(1,0x000000F8);
	vm.and_op();
	EXPECT_EQ(0x000000A8,vm.get_reg(0)); //10101010 & 11111000 = 10101000

	/*And with Immediate cases*/
	vm.set_immed(1);
	vm.set_constant(0x00000081); 
	vm.and_op();
	EXPECT_EQ(0x00000080,vm.get_reg(0)); //10101000 & 10000001 = 10000000	
	
	//negative sign extended
	vm.set_constant(-1); //0xFFFFFFFF 
	vm.and_op();
	EXPECT_EQ(0x00000080,vm.get_reg(0));
}
TEST_F(VirtualMachineTest, xor_op){
	/*xor with Register cases*/
	vm.set_rd(0);
	vm.set_rs(1);
	vm.set_reg(0,0x000000AA);
	vm.set_reg(1,0x000000F8);
	vm.xor_op();
	EXPECT_EQ(0x00000052,vm.get_reg(0)); //10101010 ^ 11111000 = 01010010

	/*xor with Immediate cases*/
	vm.set_immed(1);
	vm.set_constant(0x00000081); 	
	vm.xor_op();
	EXPECT_EQ(0x000000D3,vm.get_reg(0)); //01010010 ^ 10000001 = 11010011

	//negative sign extended
	vm.set_constant(-1); //0xFFFFFFFF 
	vm.xor_op();
	EXPECT_EQ(0xFFFFFF2C,vm.get_reg(0));
}
TEST_F(VirtualMachineTest, compl_op){
	//complement twice
	vm.set_rd(0);
	vm.set_reg(0,0x000000AA);
	vm.compl_op();
	EXPECT_EQ(0xFFFFFF55,vm.get_reg(0)); //NOT 10101010 = (sign extend 1)01010101
	vm.compl_op();
	EXPECT_EQ(0x000000AA,vm.get_reg(0));
}
TEST_F(VirtualMachineTest, shl){
	//Shift twice, should double and carry flag off
	vm.set_rd(0);
	vm.set_reg(0,0x000000AA);//10101010
	vm.shl();
	EXPECT_EQ(0x00000154,vm.get_reg(0)); //101010100
	int carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry); //carry flag off
	vm.set_sr(0);
	vm.shl();						 //1010101000
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0x000002A8,vm.get_reg(0));
	EXPECT_EQ(0, carry);//carry flag off

	//Test switch carry flag on, shift 3 times
	vm.set_reg(0,0x0000A000); //leftmost for 16 bit is 101 
	vm.set_sr(0);
	vm.shl();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1, carry);//carry flag off
	vm.set_sr(0);
	vm.shl();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry);//carry flag off
	vm.set_sr(0);
	vm.shl();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1, carry);//carry flag off

	//Test shifting out of 16bits
	vm.set_reg(0,0xFFFFA000); //Right most should be 1010
	vm.set_sr(0);
	vm.shl();
	EXPECT_EQ(0x00004000,vm.get_reg(0));//right most should be 0100
	vm.set_sr(0);
	vm.shl();
	EXPECT_EQ(0xFFFF8000,vm.get_reg(0)); //right most should be 1000	
}
TEST_F(VirtualMachineTest, shla){
	/*Same test as shl, no difference between logical vs arithmetics left shift*/
	//Shift twice, should double and carry flag off
	vm.set_rd(0);
	vm.set_reg(0,0x000000AA);//10101010
	vm.set_sr(0);
	vm.shla();
	EXPECT_EQ(0x00000154,vm.get_reg(0)); //101010100
	int carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry); //carry flag off
	vm.set_sr(0);
	vm.shla();						 //1010101000
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0x000002A8,vm.get_reg(0));
	EXPECT_EQ(0, carry);//carry flag off

	//Test switch carry flag on, shift 3 times
	vm.set_reg(0,0xFFFFA000); //leftmost for 16 bit is 101 
	vm.set_sr(0);
	vm.shla();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1, carry);//carry flag off
	vm.set_sr(0);
	vm.shla();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry);//carry flag off
	vm.set_sr(0);
	vm.shla();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1, carry);//carry flag off

	//Test shifting out of 16bits
	vm.set_reg(0,0xFFFFA000); //Right most should be 1010
	vm.set_sr(0);
	vm.shla();
	EXPECT_EQ(0x00004000,vm.get_reg(0));//right most should be 0100
	vm.set_sr(0);
	vm.shla();
	EXPECT_EQ(0xFFFF8000,vm.get_reg(0)); //right most should be 1000	
}
TEST_F(VirtualMachineTest, shr){
	//Shift twice, should double and carry flag off
	vm.set_rd(0);
	vm.set_reg(0,0x00000080); //10000000
	vm.set_sr(0);
	vm.shr();
	EXPECT_EQ(0x0000040,vm.get_reg(0)); //01000000
	int carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry); //carry flag off
	vm.set_sr(0);
	vm.shr();						 //00100000
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0x00000020,vm.get_reg(0));
	EXPECT_EQ(0, carry);//carry flag off

	//Test switch carry flag on, shift 3 times
	vm.set_reg(0,0x00000005); //rightmost is 101
	vm.set_sr(0);
	vm.shr();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1, carry);//carry flag on
	vm.set_sr(0);
	vm.shr();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry);//carry flag off
	vm.set_sr(0);
	vm.shr();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1, carry);//carry flag on

	/*Make sure shr doesn't sign extend, should only shift in 0's*/
	vm.set_rd(0);
	vm.set_reg(0,0xFFFF8000); //1000
	vm.set_sr(0);
	vm.shr();
	EXPECT_EQ(0x00004000,vm.get_reg(0)); //0100
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry); //carry flag off
	vm.set_sr(0);
	vm.shr();						 
	carry = 0x00000001 & vm.get_sr(); 
	EXPECT_EQ(0x00002000,vm.get_reg(0));//0010
	EXPECT_EQ(0, carry);//carry flag off
}
TEST_F(VirtualMachineTest, shra){
	/*Start off with same test cases as shr. These cases should have
	  the same results as they should sign extend and shift in 0*/
	//Shift twice, should double and carry flag off
	vm.set_rd(0);
	vm.set_reg(0,0x00000080); //10000000
	vm.set_sr(0);
	vm.shra();
	EXPECT_EQ(0x0000040,vm.get_reg(0)); //01000000
	int carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry); //carry flag off
	vm.set_sr(0);
	vm.shra();						 //00100000
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0x00000020,vm.get_reg(0));
	EXPECT_EQ(0, carry);//carry flag off

	//Test switch carry flag on, shift 3 times
	vm.set_reg(0,0x00000005); //rightmost is 101
	vm.set_sr(0);
	vm.shra();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1, carry);//carry flag on
	vm.set_sr(0);
	vm.shra();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry);//carry flag off
	vm.set_sr(0);
	vm.shra();
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(1, carry);//carry flag on

	/*Test sign-extended negatives, shifting in 1*/
	vm.set_rd(0);
	vm.set_reg(0,0xFFFF8000); //1000
	vm.set_sr(0);
	vm.shra();
	EXPECT_EQ(0xFFFFC000,vm.get_reg(0)); //1100
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0, carry); //carry flag off
	vm.set_sr(0);
	vm.shra();						 
	carry = 0x00000001 & vm.get_sr();
	EXPECT_EQ(0xFFFFE000,vm.get_reg(0)); //1110
	EXPECT_EQ(0, carry);//carry flag off
}
TEST_F(VirtualMachineTest, compr){
	/* compare with RS*/
	//Test GREATER
	vm.set_rd(0);
	vm.set_rs(1);
	vm.set_reg(0,2);
	vm.set_reg(1,1);
	vm.compr();
	EXPECT_EQ(0x00000002,vm.get_sr());

	//Test Equal
	vm.set_reg(1,2);
	vm.compr();
	EXPECT_EQ(0x00000004,vm.get_sr());

	//Test Less
	vm.set_reg(1,3);
	vm.compr();
	EXPECT_EQ(0x00000008,vm.get_sr());

	/*compare with immediate*/
	vm.set_immed(1);
	//Test Greater
	vm.set_sr(0);
	vm.set_rd(0);
	vm.set_reg(0,2);
	vm.set_constant(1);
	vm.compr();
	EXPECT_EQ(0x00000002,vm.get_sr());

	//Test Equal
	vm.set_constant(2);
	vm.compr();
	EXPECT_EQ(0x00000004,vm.get_sr());

	//Test Less
	vm.set_constant(3);
	vm.compr();
	EXPECT_EQ(0x00000008,vm.get_sr());
}
TEST_F(VirtualMachineTest, getstat){
	vm.set_rd(0);
	vm.set_sr(0x00000005); //101
	vm.getstat();
	EXPECT_EQ(0x00000005,vm.get_reg(0));
}
TEST_F(VirtualMachineTest, putstat){
	vm.set_rd(0);
	vm.set_reg(0,0x00000005); //101
	vm.putstat();
	EXPECT_EQ(0x00000005,vm.get_sr());
}
TEST_F(VirtualMachineTest, jump){
	vm.set_addr(100);
	vm.jump();
	EXPECT_EQ(100,vm.get_pc());
}
TEST_F(VirtualMachineTest, jumpl) {
	vm.set_addr(100);
	vm.jumpl(); //Less bit is off	
	EXPECT_EQ(0,vm.get_pc());

	//1000 LESS bit is on
	vm.set_sr(0x00000008); 
	vm.jumpl();
	EXPECT_EQ(100,vm.get_pc());
}
TEST_F(VirtualMachineTest, jumpe) {
	vm.set_addr(100);
	vm.jumpe(); //Equal bit is off	
	EXPECT_EQ(0,vm.get_pc());

	//100 Equal bit is on
	vm.set_sr(0x00000004); 
	vm.jumpe();
	EXPECT_EQ(100,vm.get_pc());
}
TEST_F(VirtualMachineTest, jumpg) {
	vm.set_addr(100);
	vm.jumpg(); //Greater bit is off	
	EXPECT_EQ(0,vm.get_pc());

	//10 Greater bit is on
	vm.set_sr(0x00000002); 
	vm.jumpg();
	EXPECT_EQ(100,vm.get_pc());
}
TEST_F(VirtualMachineTest, call) {

}
TEST_F(VirtualMachineTest, return_op) {

}
TEST_F(VirtualMachineTest, read) {

}
TEST_F(VirtualMachineTest, write) {

}
TEST_F(VirtualMachineTest, halt) {
	// Test if halt_flag changes on halt() call
	EXPECT_FALSE(vm.get_halt_flag());
	vm.halt();
	EXPECT_TRUE(vm.get_halt_flag());
}
TEST_F(VirtualMachineTest, noop){
	// Check clock increments on noop
	int clock = vm.get_clock();
	vm.noop();
	EXPECT_EQ(clock+1,vm.get_clock());
}
