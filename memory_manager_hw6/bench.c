
/*
    John Diego & Thomas Nguyen
    November 15, 2017
    CSE 374
    Homework 6: Memory Management

    bench.c - automates random test cases on getmem and freemem; if no
              arguments are passed then the default values will be used

    Syntax: bench [ntrials [pctget [pctlarge [small_limit [large_limit
            [random_seed]]]]]]

    Options
        N/A
 */

#include "mem.h"
#include <string.h>
#include <time.h>

#define NTRI_DEFAULT 10000
#define PCTGET_DEFAULT 50
#define PCTLRG_DEFAULT 10
#define SML_LIM_DEFAULT 200
#define LRG_LIM_DEFAULT 20000
#define RAND_SEED_DEFAULT time(NULL)


static void performtrials(int *args);

int main(int argc, char **argv) {
    int args[6] = {NTRI_DEFAULT, PCTGET_DEFAULT, PCTLRG_DEFAULT,
                   SML_LIM_DEFAULT, LRG_LIM_DEFAULT, RAND_SEED_DEFAULT};
    for (int i = 1; argv[i] && i < 7; i++) {
        args[i - 1] = atoi(argv[i]);
    }
    performtrials(args);
    return EXIT_SUCCESS;
}

/*
    Performs the trials on the memory manager and outputs statistics of the
    memory at every 10% intervals until completion.

    Params
        *args: pointer to the args provided by the client or the
               assumed default values
*/
static void performtrials(int *args) {
    double time_elapsed;
    int range = args[4] - args[3];
    uintptr_t *mem_ptrs = (uintptr_t*) malloc(args[0]*sizeof(uintptr_t));
    clock_t start = clock();
    uintptr_t n_free_blocks = 0;
    uintptr_t n_req_blocks = 0;
    uintptr_t total_free = 0;
    char initial_data[16] = {0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
                             0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE};
    srand(args[5]);
    for (int i = 1; i <= args[0]; i++) {
        int rand_num = rand() % 100 + 1;
        if (rand_num <= args[1]) {
            rand_num = rand() % 100 + 1;
            uintptr_t byte_size = (rand_num > args[2]) ? rand() % args[3] + 1 :
                                  rand() % range + args[3];
            void *preprossed_mem = getmem(byte_size);
            size_t bytes_init = (byte_size < 16) ? byte_size : 16;
            void *prossed_mem = memcpy(preprossed_mem, initial_data,
                                       bytes_init);
            mem_ptrs[n_req_blocks++] = (uintptr_t) prossed_mem;
        } else {
            if (n_req_blocks > 0) {
                int index = 0;
                if (n_req_blocks != 1) {
                    index = rand() % (n_req_blocks - 1);
                }
                freemem((void*) mem_ptrs[index]);
                mem_ptrs[index] = mem_ptrs[--n_req_blocks];
            }
        }
        int tenth = ((args[0] / 10) != 0 ) ? args[0] / 10 : i;
        if (i % tenth == 0) {
            uintptr_t total_size;
            get_mem_stats(&total_size, &total_free, &n_free_blocks);
            double avg = (n_free_blocks > 0) ?
                         (double) total_free / n_free_blocks : 0.0;
            time_elapsed = ((double) (clock() - start)) / CLOCKS_PER_SEC;
            printf("Total CPU time elapsed: %lf\n", time_elapsed);
            printf("Total storage acquired: %lu\n", total_size);
            printf("Number of free blocks: %lu\n", n_free_blocks);
            printf("Average number of bytes per block: %f\n\n", avg);
        }
    }
}
