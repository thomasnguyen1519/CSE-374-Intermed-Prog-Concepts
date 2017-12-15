/*
 * mem.h - the main public interface for the mem package program.
 *
 * John Diego & Thomas Nguyen
 * UW CSE 374
 * HW6 - part I
 */

#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// getmem returns a pointer  to a new block of storage
// with at least size bytes of memory.
void* getmem(uintptr_t size);

// freemem Return the block of storage at location p to the pool of
// available free storage.
void freemem(void* p);

// get_mem_stats Store statistics about the current state of the
// memory manager in the three integer variables whose addresses
// are given as arguments.
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks);

// Print a formatted listing on file f showing the blocks
// on the free list.
void print_heap(FILE * f);

#endif
