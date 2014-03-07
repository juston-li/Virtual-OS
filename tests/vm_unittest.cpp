#include "../src/VirtualMachine.h"
#include "gtest/gtest.h"

class VirtualMachineTest : public testing::Test {
	protected:
	virtual void SetUp(){	
	}
	VirtualMachine vm;
};
TEST_F(VirtualMachineTest, load){
	// Load 1 into Register 0
	EXPECT_EQ(0,vm.get_reg(0));
	vm.set_rd(0);
	vm.set_addr(100);
	vm.set_mem(100,1);
	vm.load();
	EXPECT_EQ(1,vm.get_reg(0));

	// Load 2 into Register 0 - Make sure overwrites
	EXPECT_EQ(0,vm.get_reg(0));
	vm.set_rd(0);
	vm.set_addr(100);
	vm.set_mem(100,2);
	vm.load();
	EXPECT_EQ(2,vm.get_reg(0));
}
TEST_F(VirtualMachineTest, store){
	// Store 1 into Register 0
	EXPECT_EQ(0,vm.get_mem(100));
	vm.set_rd(0);
	vm.set_reg(0,1);
	vm.set_addr(100);
	vm.store();
	EXPECT_EQ(1,vm.get_mem(100));

	// Store 2 into Register 0 - Make sure overwrites
	EXPECT_EQ(0,vm.get_mem(100));
	vm.set_rd(0);
	vm.set_reg(0,2);
	vm.set_addr(100);
	vm.store();
	EXPECT_EQ(2,vm.get_mem(100));
}
TEST_F(VirtualMachineTest, add){

}
TEST_F(VirtualMachineTest, addc){

}
TEST_F(VirtualMachineTest, sub){

}
TEST_F(VirtualMachineTest, subc){

}
TEST_F(VirtualMachineTest, and_op){

}
TEST_F(VirtualMachineTest, xor_op){

}
TEST_F(VirtualMachineTest, compl_op){

}
TEST_F(VirtualMachineTest, shl){

}
TEST_F(VirtualMachineTest, shla){

}
TEST_F(VirtualMachineTest, shr){

}
TEST_F(VirtualMachineTest, shra){

}
TEST_F(VirtualMachineTest, compr){

}
TEST_F(VirtualMachineTest, getstat){

}
TEST_F(VirtualMachineTest, putstat){

}
TEST_F(VirtualMachineTest, jump){

}
TEST_F(VirtualMachineTest, jumpl) {

}
TEST_F(VirtualMachineTest, jumpe) {

}
TEST_F(VirtualMachineTest, jumpg) {

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
