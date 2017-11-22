#Thomas Nguyen
#November 8, 2017
#CSE 374
#Homework 5: t9
# Makefile to simplify the compiling commands for this project.

Header file for node.c

t9: node.o main.o
	gcc -Wall -std=c11 -g -o t9 node.o main.o

trie.o: node.h node.c
	gcc -Wall -std=c11 -g -c node.c node.h

main.o: main.c node.h
	gcc -Wall -std=c11 -g -c main.c node.h

.PHONY: clean

clean:
	rm -f main.o node.o t9
