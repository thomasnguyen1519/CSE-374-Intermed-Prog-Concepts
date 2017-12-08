# Makefile for rational number calculator
# CSE 374, 17wi, HP

calc: rational.o scan.o parse.o calc.o
	g++ -Wall -g -std=c++11 -o calc calc.o rational.o scan.o parse.o

rational.o: rational.cc rational.h
	g++ -Wall -g -std=c++11 -c rational.cc

scan.o: scan.cc token.h scan.h
	g++ -Wall -g -std=c++11 -c scan.cc

parse.o: parse.cc rational.h token.h scan.h
	g++ -Wall -g -std=c++11 -c parse.cc

calc.o: calc.cc rational.h token.h scan.h parse.h
	g++ -Wall -g -std=c++11 -c calc.cc

clean:
	rm -f *.o *~ calc
