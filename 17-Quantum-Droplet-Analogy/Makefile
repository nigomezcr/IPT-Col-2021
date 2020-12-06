CXX=g++
OBJECTS=main.o system.o
CXXFLAGS=-O2 -g -std=c++17
SANITFLAGS=  -fsanitize=address -fsanitize=leak
VALGRINDFLAGS=--tool=memcheck  --track-origins=yes --leak-check=full

##################################################################

all: data.txt

%.o:  %.cpp %.hpp erase 
	$(CXX)  -c  $< -o  $@

sanitize: $(OBJECTS)
	$(CXX)  $(CXXFLAGS) $(SANITFLAGS)  $^  -o main.x
	./main.x 

data.txt: main.x
	./$< > $@
	@echo "END RUN WITH SANITIZERS"

##################################################################

main.x: $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@


memcheck: main.x
	valgrind $(VALGRINDFLAGS) ./$<
	@echo "END RUN WITH VALGRIND"

##################################################################

gprof: main.x
	./$<
	gprof ./$< > gprof-report.txt
	@echo "END RUN WITH PROFILING"

cachegrind: main.x main.cpp system.cpp
	./$<
	valgrind --tool=cachegrind ./$<
	cg_annotate $$(ls -t cachegrind.out.* | head -n 1) > cachegrind-report.txt



##################################################################


test.x: test.o functions.o
	g++ $^ -o $@


test: test.x
	./$<

##################################################################

plot: data.txt plots.gp
	gnuplot plots.gp

show: plot
	evince  z-x.pdf # y-x.pdf  y-z.pdf #y-t.pdf x-t.pdf &

##################################################################

erase:
	rm -f *.x *.txt *.pdf *~

clean:	
	rm -f *.o *.x *.txt *.pdf *~

