CXX=g++
OBJECTS=main.o drop_system.o drop.o
CXXFLAGS=-O2 -g -std=c++14

all: show

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


main.x: $(OBJECTS) drop.hpp drop_system.hpp
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@


data2.txt: main.x
	./$< > $@


pdfs: data2.txt plots2.gp
	gnuplot plots2.gp

show:  pdfs
	evince two_drops.pdf

clean:
	rm -f *.txt *.o *.x *~ a.out
