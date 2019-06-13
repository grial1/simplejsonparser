PROG=example
INCLUDE= -Iinclude/utils
CXXFLAGS= $(INCLUDE) -std=c++11

.PHONY:$(PROG).cc

all:$(PROG).o $(PROG).bin

$(PROG).o:$(PROG).cc
	g++ -c -o obj/$@ src/$< $(CXXFLAGS)

$(PROG).bin:$(PROG).o
	g++ -o $@ obj/$< $(CXXFLAGS)

clean:
	rm -rf obj/*.o

run:
	./$(PROG).bin

debug:$(PROG).cc
	g++ -g -o debug.bin src/$< $(CXXFLAGS)
	gdb ./debug.bin

clean_debug:
	rm -rf debug.bin