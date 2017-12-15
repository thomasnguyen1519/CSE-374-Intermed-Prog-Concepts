/*
    John Diego & Thomas Nguyen
    November 15, 2017
    CSE 374
    Homework 6: Memory Management

    get_mem_stats.c - Store statistics about the current state of the memory manager.
                      The information stored should be as follows:

    Parameters:
        total_size: total amount of storage in bytes acquired by the memory manager
                    so far to use in satisfying allocation requests.

        total_free: the total amount of storage in bytes that is currently stored
                    on the free list, including any space occupied by header
                    information or links in the free blocks.

        n_free_blocks: the total number of individual blocks currently stored
                       on the free list.
 */

#include "mem_impl.h"

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
                   uintptr_t* n_free_blocks) {
    uintptr_t i_free_blocks = 0;
    uintptr_t i_total_free = 0;
    freenode *current = freelist;
    while (current != NULL) {
        i_free_blocks++;
        i_total_free += current->size;
        current = current->next;
    }
    *total_free = i_total_free;
    *n_free_blocks = i_free_blocks;
    *total_size = total_size_from_malloc;
}
