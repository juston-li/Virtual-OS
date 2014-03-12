CXX = g++
CXXFLAGS = -g -std=c++0x -Wall -march=native -O2
DIRS = src tests
.PHONY : os test
all: os test

os:
	$(MAKE) -C src
	cp src/os ./ 

test:
	$(MAKE) -C tests
	cp tests/vm_unittest ./ 

clean: 
	$(RM) os vm_unittest
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done
