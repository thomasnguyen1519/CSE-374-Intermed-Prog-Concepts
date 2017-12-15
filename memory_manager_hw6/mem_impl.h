/*
 * mem_impl.h - interface to the underlying data structure
 *
 * John Diego & Thomas Nguyen
 * UW CSE 374
 * HW6 - part I
 */

#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

// The required size left when dividing a block
// of memory.
#define THRESHOLD 80

#define MIN_NODE_SIZE (THRESHOLD + sizeof(freenode))

// freenode represents the data structure of our underlying
// memory management package. It represents a free memory block
// that is available to satisfy memory allocation requests.
//
// The size of the memory block within a freenode does not
// include the size of the other two fields - size and next.
// It only counts the space intended for use of memory allocations.
typedef struct freenode {
    uintptr_t size;
    struct freenode *next;
} freenode;

// global variable to keep count amount of memory
// we call from the underlying system
extern uintptr_t total_size_from_malloc;

// pointer to the head of our free list
extern freenode *freelist;

// move an pointer 'steps' times to point to another
// address space
void move_ptr(int steps, freenode **node);

// Check for possible problems with the free list data structure.
void check_heap();

#endif
