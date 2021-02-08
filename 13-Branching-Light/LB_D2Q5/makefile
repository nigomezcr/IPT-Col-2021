# Useful flags
DEBUG = -g -Wall -fsanitize=address -fsanitize=leak -fsanitize=undefined
VAL = --track-origins=yes --leak-check=full
CACH = --tool=cachegrind
C_STD = -std=c++11

# Dependecies
DEPS = LB_D2Q5.cpp

all : main.o 

main.o : main.cpp $(DEPS) *.h
	g++ $(C_STD) -O2 $< $(DEPS) -o $@
	time ./$@

.PHONY : assembler
assembler : main.cpp $(DEPS) *.h
	gcc $(C_STD) -g -S main.cpp $(DEPS) -o main.S

.PHONY : parallel
parallel : main.cpp
	g++ $(C_STD) -fopenmp -O2 $< $(DEPS) -o parallel.o
	time ./parallel.o

.PHONY : debug
debug : main.cpp
	g++ $(C_STD) $(DEBUG) $< $(DEPS) -o debug.o
	debug.o

.PHONY : valgrind
valgrind : main.cpp
	g++ $(C_STD) -g $< $(DEPS) -o valgrind.o
	valgrind $(VAL) ./valgrind.o

.PHONY : cachegrind
cachegrind : main.cpp
	g++ $(C_STD) -g $< $(DEPS) -o cachegrind.o
	valgrind $(CACH) ./cachegrind.o

.PHONY : gprof
gprof : main.cpp
	g++ $(C_STD) -Wall -pg $< $(DEPS) -o gprof.o
	./gprof.o
	gprof gprof.o gmon.out > analysis.txt
	most analysis.txt

.PHONY : perf
perf : main.cpp
	g++ $(C_STD) -Wall -pg $< $(DEPS) -o perf.o
	perf record ./perf.o ; perf report

.PHONY : clean
clean :
	rm -f *.o *.txt *.out* debug main *.data


