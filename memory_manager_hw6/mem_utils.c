/*
    John Diego & Thomas Nguyen
    November 15, 2017
    CSE 374
    Homework 6: Memory Management

    mem_utils.c - implementation of function check_heap

 */

#include <assert.h>
#include <stdio.h>
#include "mem_impl.h"

// Checks if blocks are ordered with strictly
// increasing memory addresses
static int is_sorted(freenode *curr) {
    return (uintptr_t)curr < (uintptr_t)curr->next;
}

// Checks if block sizes are positive numbers and no smaller than
// whatever minimum size you are using in your implementation
static int is_valid_size(freenode *curr) {
    return (int) curr->size > 0 && curr->size >= MIN_NODE_SIZE;
}

// Checks that blocks do not overlap (the start + length of a block
// is not an address in the middle of a later block on the list)
static int is_not_overlapping(freenode *curr) {
    freenode *first_node_end = curr;
    move_ptr((int) curr->size , &first_node_end);
    return (uintptr_t) first_node_end < (uintptr_t) curr->next;
}

// Checks if blocks are not touching (the start + length of a block should
// not be the same address as the next block on the list since in
// that case the two blocks should have been combined into a
// single, larger block.)
static int is_not_adjacent(freenode *curr) {
    return (uintptr_t) curr != (uintptr_t) curr->next;
}


/*
    Checks for possible errors in the memory heap.
*/
void check_heap() {
    freenode *current = freelist;
    while (current != NULL && current->next != NULL) {
        assert(is_sorted(current));
        assert(is_valid_size(current));
        assert(is_not_adjacent(current));
        assert(is_not_overlapping(current));
        current = current->next;
    }
}


/*
    Checks for possible errors in the memory heap.
*/
void move_ptr(int steps, freenode **node) {
    if (node == NULL || *node == NULL) {
        fprintf(stderr, "moving pointer error, amount of steps:%d\n",
                steps);
        exit(EXIT_FAILURE);
    }
    uintptr_t ptr_loc = (uintptr_t) *node;
    ptr_loc = ptr_loc + steps;
    *node = (freenode*) ptr_loc;
}
