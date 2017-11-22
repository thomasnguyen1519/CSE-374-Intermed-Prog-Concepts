/*
    Thomas Nguyen
    November 8, 2017
    CSE 374
    Homework 5: t9

    Source file for the trie nodes that will store the word data.
 */

#include <ctype.h>
#include "node.h"


/*
    Converts a char into a t9 numeric value.

    Params
        letter: char value to convert

    Return
        int: representing a t9 numeric value or -1 if the char was not
        alphabetic
*/
int char_to_t9(char letter) {
    int lower = tolower(letter);
    if (lower >= (int)'a' && lower <= (int)'c') {
        return 2;
    } else if (lower >= (int)'d' && lower <= (int)'f') {
        return 3;
    } else if (lower >= (int)'g' && lower <= (int)'i') {
        return 4;
    } else if (lower >= (int)'j' && lower <= (int)'l') {
        return 5;
    } else if (lower >= (int)'m' && lower <= (int)'o') {
        return 6;
    } else if (lower >= (int)'p' && lower <= (int)'s') {
        return 7;
    } else if (lower >= (int)'t' && lower <= (int)'v') {
        return 8;
    } else if (lower >= (int)'w' && lower <= (int)'z') {
        return 9;
    } else {
        return -1;
    }
}

/*
    Adds the word to the trie structure.

    Params
        node: root of the trie structure
        str: word to add to the trie
*/
void add_word(Tnode *node, char *str) {
    Tnode *curr = node;
    char *new_line_char = strchr(str, '\n');
    if (new_line_char) {
        *new_line_char = '\0';              // converts \n to null byte
    }
    for (int i = 0; str[i]; i++) {
        int curr_char = char_to_t9(str[i]);
        if (curr_char == -1) {
            fprintf(stderr, "could not insert: %s %c\n", str, str[i]);
            exit(EXIT_FAILURE);
        }
        if (!curr->children[curr_char-2]) {
            curr->children[curr_char-2] = create_node();
        }
        curr = curr->children[curr_char-2];
    }
    while (curr->word) {
        if (!curr->children[MAX_CHILDREN]) {
            curr->children[MAX_CHILDREN] = create_node();
        }
        curr = curr->children[MAX_CHILDREN];
    }
    curr->word = malloc(strlen(str) + 1);
    strncpy(curr->word, str, strlen(str) + 1);
}

/*
    Traverses the trie and searches for the word.

    Params
        node: Tnode to start searching from
        str: string to be searched for

    Return
        Tnode: node containing the provided word
*/
Tnode *search_word(Tnode *node, char *str) {
    Tnode *curr = node;
    for (int i = 0; str[i]; i++) {
        int currNum = (str[i] == '#') ? 10 : str[i] - '0';
        if (currNum > 10 || currNum < 2 || !curr->children[currNum-2]) {
            return NULL;
        }
        curr = curr->children[currNum-2];
    }
    return curr;
}

/*
    Creates an empty trie node.

    Return
        Tnode: created Tnode that is empty
*/
Tnode *create_node() {
    Tnode *node = malloc(sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "Node malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    node->word = NULL;
    for (int i = 0; i <= MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}

/*
    Recursively frees the dynamically allocated memory from a trie node.

    Params
        node: Tnode to begin freeing memory from
*/
void destroy(Tnode *node) {
    if (node) {
        for (int i = 0; i <= MAX_CHILDREN; i++) {
            destroy(node->children[i]);
        }
        free(node->word);
        free(node);
    }
}
