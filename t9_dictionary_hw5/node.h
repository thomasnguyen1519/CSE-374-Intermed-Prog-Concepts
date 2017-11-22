/*
    Thomas Nguyen
    November 8, 2017
    CSE 374
    Homework 5: t9

    Header file for node.c
 */

#ifndef NODE_H
#define NODE_H

#define MAX_CHILDREN 8

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Tnode {
      struct Tnode *children[9];
      char *word;
} Tnode;

int char_to_t9(char letter);
void add_word(Tnode *node, char *str);
Tnode *search_word(Tnode *node, char *str);
Tnode *create_node();
void destroy(Tnode *node);

#endif
