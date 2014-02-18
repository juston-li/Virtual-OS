CXX = g++
CFLAGS = -g -std=c++0x -Wall -march=native -O2
DIRS = src tests
all: os test

os:
	$(MAKE) -C src
	cp src/os ./ 

test:
	$(MAKE) -C test
	cp src/test ./ 

clean: 
	$(RM) os test
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done
