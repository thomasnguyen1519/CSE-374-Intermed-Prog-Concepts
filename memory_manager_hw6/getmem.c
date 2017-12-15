/*
    John Diego & Thomas Nguyen
    November 15, 2017
    CSE 374
    Homework 6: Memory Management

    getmem.c - Function that return a pointer to a new block of storage with at
               least size bytes of memory.

 */

#include <stdio.h>
#include "mem_impl.h"

// The default size when calling for raw memory
#define  DEFAULT_CHUNK_SIZE 8000

static freenode* past;

// our free memory list
struct freenode *freelist = NULL;

// total size from our underlying system
uintptr_t total_size_from_malloc = 0;

// Returns the max value between the two parameters
static size_t max_of(size_t size1, size_t size2);

// assigns the given values to the freenode
static void assign_node(freenode *node, uintptr_t size, freenode *next);

// create new node from malloc
static freenode *new_node(uintptr_t size, freenode *next);

// delete node from freelist
static void remove_node(freenode *node);

// inserts node into free list in ascending memory address order
static void sorted_insert_node(freenode *new_node);

// split the node into two nodes
static void split_node(freenode *node, uintptr_t req_size, uintptr_t leftover_size);


/*
    gets memory from either the underlying system or from the free list

    Params
        size: the amount the client is requesting the payload to be
*/
void* getmem(uintptr_t size) {
    if (size <= 0) {
        return NULL;
    }
    if (!freelist) {
        past = freelist;
    }

    check_heap();

    // sizes must be at least THRESHOLD size
    if (size < THRESHOLD) {
        size = THRESHOLD;
    }

    // make given size 16 byte aligned
    uintptr_t call_size = size;
    if (call_size % 16 != 0) {
        int difference = 16 - (int) call_size % 16;
        call_size = difference + size;
    }
    uintptr_t total_req_size = call_size + sizeof(freenode);

    // traverse and search the free list for a node with
    // at least the total req size.
    freenode *current = past;
    freenode *prev = past;
    while (current != NULL && current->size < total_req_size) {
        prev = current;
        current = current->next;
    }
    freenode *req_node;
    freenode *ptr;
    if (current == NULL) {
        // executed when we reached the end of free list and no node could
        // fulfill the total req size
        uintptr_t malloc_size = max_of(DEFAULT_CHUNK_SIZE, total_req_size);
        req_node = new_node(malloc_size, NULL);
        uintptr_t total_leftover_size = malloc_size - total_req_size;
        if (malloc_size > DEFAULT_CHUNK_SIZE) {
            // call size is way over 8000 so just return it
            move_ptr(sizeof(freenode), &req_node);
            check_heap();
            return (void*) req_node;
        } else if ((int) total_leftover_size < MIN_NODE_SIZE) {
            // call size is here is <= 8000 but make sure the
            // leftover node is atleast > MIN_NODE_SIZE
            move_ptr(sizeof(freenode), &req_node);
            check_heap();
            return (void*) req_node;
        } else {
            // call size is 8000
            // calculate the size for a leaving behind a
            // leftover node in the free list
            split_node(req_node, total_req_size,
                       DEFAULT_CHUNK_SIZE - total_req_size);
             freenode *leftover_node = req_node->next;
            req_node->next = NULL;
            sorted_insert_node(leftover_node);
            sorted_insert_node(req_node);
            remove_node(req_node);
            ptr = req_node;
            move_ptr(sizeof(freenode), &ptr);
        }
    } else {
        // were are at a node which fulfills the req size
        if ((int)(current->size - total_req_size) >=  MIN_NODE_SIZE) {
            // split it
            uintptr_t total_leftover_size = current->size - total_req_size;
            split_node(current, total_req_size, total_leftover_size);
        }
        if (prev != current) {
            // current node is somewhere in the middle so
            // so update prev pointer
            prev->next = current;
        }
        ptr = current;
        move_ptr(sizeof(freenode), &ptr);
        remove_node(current);
    }
    past = prev;
    check_heap();
    return ptr;
}


static size_t max_of(size_t size1, size_t size2) {
    if (size1 > size2) {
        return  size1;
    } else {
        return size2;
    }
}

static void assign_node(freenode *node, uintptr_t size, freenode *next) {
    node->size = size;
    node->next = next;
}

static freenode* new_node(uintptr_t size, freenode *next) {
    freenode *node = (freenode*) malloc(size);
    if (node == NULL) {
        fprintf(stderr, "something went wrong with malloc");
        exit(EXIT_FAILURE);
    }
    // increment our total call size to malloc
    total_size_from_malloc += size;
    if (next == NULL) {
        assign_node(node, size, NULL);
    } else {
        assign_node(node, size, next);
    }
    return node;
}

void remove_node(freenode *node) {
    // when node to be deleted is head node
    if (freelist == node) {
        freelist = freelist->next;
        return;
    }

    // find prev node
    freenode *prev = freelist;
    while (prev->next != NULL && prev->next != node) {
        prev = prev->next;
    }

    // Check if node really exists in free List
    if (prev->next == NULL) {
        fprintf(stderr, "tried to delete a node not in free list");
        exit(EXIT_FAILURE);
    }

    // remove node from list
    prev->next = prev->next->next;
}

static void split_node(freenode *node, uintptr_t req_size, uintptr_t leftover_size) {
    freenode *moving_ptr = node;
    int distance = (int) req_size;
    // assign second half node
    move_ptr(distance, &moving_ptr);
    assign_node(moving_ptr, leftover_size, node->next);
    freenode *second_node = moving_ptr;
    // assign first half node
    move_ptr(-1 * distance, &moving_ptr);
    assign_node(moving_ptr, req_size, second_node);
}

static void sorted_insert_node(freenode *new_node) {
    /* Special case for the head end */
    if (freelist == NULL || (uintptr_t)freelist >= (uintptr_t)new_node) {
        new_node->next = freelist;
        freelist = new_node;
    } else {
        /* Locate the node before the point of insertion */
        freenode *current = freelist;
        while (current->next != NULL &&
               (uintptr_t) current->next < (uintptr_t)new_node) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
