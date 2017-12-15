John Diego & Thomas Nguyen, Group AT.

We decided to divide the work by assigning the following:
John:
- get_mem_stats.c
- getmem.c
- mem.h
- mem_impl.h

Thomas:
- freemem.c
- print_heap.c
- mem_utils.c
- bench.c


### Free list structure ###
The free list data structure is implemented using a linked list data structure,
with each node (called _free node_) having a size and pointer field. The `size`
field contains an 8 byte unsigned number which describes the size of the whole 
free node. **This means that the `size` is the size of a free node + the size 
of the payload**. The `next` field contains a 8 byte pointer to the next free 
node in the list. 8 bytes further down the memory address, is the _payload_ of 
the free node. The free list data structure is sorted in ascending order based 
on the memory address of the node.

### Improvements ###
For improvements in our memory manager, we enforced that any size requested
for memory should be **16 byte alligned**. We also enforced 
**minimum size of 80** for the payload data, meaning the least size node 
possible in the freelist is 96.

For extra credit we also finished the first extra credit, where we for each
subsequent search, it starts from where the previous search left off. Doing so 
marginally _increased_ the runtime of the program because it skips the the many 
little fragments of free space at the beginning of the list.

### Results ###
When running bench with default arguments, it runs 10000 trials of either
calling getmem() or freemem(). Running default arguments usually took about
_~3 seconds_. The runtime drastically decreases when we don't have to run 
assertions on our free list.