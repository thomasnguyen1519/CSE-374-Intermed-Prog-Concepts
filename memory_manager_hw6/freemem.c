/*
   John Diego & Thomas Nguyen
   November 15, 2017
   CSE 374
   Homework 6: Memory Management

   freemem.c - implementation of the freemem function

*/

#include "mem_impl.h"

static int checkcombine(freenode *prev, freenode *neighbor);
static void combine(freenode *first, freenode *next);

/*
    Frees dynamically allocated memory and places the freed block on the
    freelist.

    Params
        *p: pointer to the p_block of memory to return to the free list
*/
void freemem(void *p) {
    check_heap();
    if (p) {
        freenode *curr = freelist;
        freenode *prev = freelist;
        uintptr_t p_addy = (uintptr_t) p - 16;
        freenode *p_block = (freenode*) p_addy;
        if (freelist) {
            if (p_addy < (uintptr_t) freelist) {
                p_block->next = freelist;
                freelist = p_block;
                prev = freelist;
            } else {
                while (curr) {
                    curr = curr->next;
                    if (!curr || ((uintptr_t) prev < p_addy &&
                        (uintptr_t) curr > p_addy)) {
                        p_block->next = curr;
                        prev->next = p_block;
                        break;
                    }
                    prev = curr;
                }
            }
            if (checkcombine(prev, p_block)) {
                combine(prev, p_block);
                if (checkcombine(prev, curr)) {
                    combine(prev, curr);
                }
            } else if (checkcombine(p_block, curr)) {
                combine(p_block, curr);
            }
        } else {
            freelist = p_block;
            p_block->next = NULL;
        }
    } else {
        printf("Error: cannot freemem a NULL argument.\n");
        exit(EXIT_FAILURE);
    }
    check_heap();
}

 /*
    Checks if two blocks are adjacent.

    Params
        prev: freenode pointer to the block preceding neighbor
        neighbor: freenode pointer to the block after prev
    Returns
        int: 0 if not adjacent, otherwise 1
 */
static int checkcombine(freenode *prev, freenode *neighbor) {
     if (prev && neighbor) {
         if ((uintptr_t) prev + prev->size == (uintptr_t) neighbor ||
             (uintptr_t) prev == (uintptr_t) neighbor + neighbor->size) {
             return 1;
         }
     }
     return 0;
}

 /*
    Combines two blocks of memory into one.

    Params
        first: freenode pointer to the block to be merged with
        next: freenode pointer to the block that will be combined and
              appended to first
 */
static void combine(freenode *first, freenode *next) {
     first->size += next->size;
     next->size = 0;
     first->next = next->next;
     next->next = NULL;
}
