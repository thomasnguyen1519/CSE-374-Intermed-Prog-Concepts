/*
    Thomas Nguyen
    November 8, 2017
    CSE 374
    Homework 5: t9

    This program simulates an old-school t9 numeric to alphabetic translator,
    using a provided dictionary file.

    Syntax: ./t9 FILE

    Options
        N/A
 */


#include "node.h"

#define MAX_WORD_LENGTH 100

int main(int argc, char **argv) {
    if (argc != 2) {                // checks for the correct number of args
        fprintf(stderr, "Usage: t9 [FILE]\n");
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "%s: %s file not found.\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }
    Tnode *root = create_node();
    char line[MAX_WORD_LENGTH];
    while (fgets(line, MAX_WORD_LENGTH, file)) {
        add_word(root, line);
    }
    fclose(file);
    Tnode *curr = root;
    char input[MAX_WORD_LENGTH];
    printf("Enter \"exit\" to quit.\n");
    printf("Enter Key Sequence (or \"#\" for next word):\n");
    printf("> ");
    while (fgets(input, MAX_WORD_LENGTH, stdin)) {
        char *new_line_char = strchr(input, '\n');
        if (new_line_char) {
            *new_line_char = '\0';          // converts \n to null byte
        }
        if (feof(stdin) || strcmp(input, "exit") == 0) {    // checks to exit
            break;
        } else if (strcmp(input, "#") == 0) {       // checks for '#' input
            if (curr && curr != root) {
                printf("    %s\n", curr->word);
                curr = curr->children[MAX_CHILDREN];
            } else {
                printf("    There are no more T9onyms\n");
            }
        } else {
            curr = search_word(root, input);
            if (!curr || !curr->word) {
                printf("    Not found in current dictionary.\n");
            } else {
                printf("    \'%s\'\n", curr->word);
                curr = curr->children[MAX_CHILDREN];
            }
        }
        printf("Enter Key Sequence (or \"#\" for next word):\n");
        printf("> ");
    }
    destroy(root);
    exit(EXIT_SUCCESS);
}
