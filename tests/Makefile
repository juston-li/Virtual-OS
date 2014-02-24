CXX = g++
CXXFLAGS = -g -std=c++0x -Wall -march=native -O2
OBJECTS =

all: test

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

test: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

clean: 
	$(RM) test *.o
