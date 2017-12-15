/*
   John Diego & Thomas Nguyen
   November 15, 2017
   CSE 374
   Homework 6: Memory Management

   Contains the function to print details about the free list.

*/

#include "mem_impl.h"


/*
   Prints a formatted hexadecimal listing of the free list to a specified file.

   Params
       f: pointer to the file being written to
*/
void print_heap(FILE *f) {
    if (f) {
        freenode *curr = freelist;
        while (curr) {
            fprintf(f, "Address: %p, Size: %" PRIxPTR "\n", curr, curr->size);
            curr = curr->next;
        }
    }
}
