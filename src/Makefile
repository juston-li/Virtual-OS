CXX = g++
CXXFLAGS = -g -std=c++0x -Wall -march=native -Wno-sign-compare
OBJECTS = Assembler.o VirtualMachine.o

all: os

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

os: $(OBJECTS) os.cpp
	$(CXX)  $(CXXFLAGS) -o $@ os.cpp $(OBJECTS)

clean: 
	$(RM) os *.o
