
#include <raspiccolo/memory/qmalloc.h>

#include <stdint.h>
#include <stdbool.h>

#ifndef NULL
    #define NULL (void*)0
#endif

#define CEIL_DIV(X, Y) ( ( X + ( Y - 1 ) ) / (Y) ) // Can be optimized by compiler for Y = 2^n

typedef struct qalloc_header {
    struct qalloc_header *next_free_block;
    unsigned int size;
} QHEADER; // Stuct (always seems to be) size power 2

extern QHEADER __qheap_start;
extern QHEADER __qheap_end;
extern QHEADER __qheap_size;

static QHEADER *free_header_ptr;
static unsigned int qalloc_memory_remaining;

//Could replace with static check but that's an extra if statement
void init_quick_alloc(void)
{
    free_header_ptr = &__qheap_start;
    free_header_ptr->next_free_block = NULL;

    qalloc_memory_remaining = (int)(((uintptr_t)&__qheap_size) / sizeof(QHEADER));
    free_header_ptr->size = qalloc_memory_remaining;
}

void* qmalloc(unsigned int nbytes) 
{
    unsigned int num_units = CEIL_DIV(nbytes, sizeof(QHEADER));
    
    /**************************************************************************
    * Two cases: 
    ** 1) Enough space (2 subcases) 
    *** 1a) Exactly enough space -> allocate the whole block.
    *** 1b) Too much space -> split blocks
    *
    ** 2) Not enough space -> return NULL
    **************************************************************************/

    bool first_loop = true;
    for (QHEADER *curr = free_header_ptr; curr; curr = curr->next_free_block)
    {
        if (curr->size >= num_units)
        {
            if (curr->size > num_units)
            {
                curr->size -= num_units;
                curr += curr->size;
                curr->size = num_units;
            }
            else // curr->size == num_units
            {
                if (first_loop)
                {
                    free_header_ptr = curr->next_free_block;
                }
            }
            qalloc_memory_remaining -= num_units;
            return (void *)(curr + 1);
        }

        first_loop = false;
    }
    // Not enough space
    return(NULL);
}

void qfree(void *ptr)
{
    /**************************************************************************
    * Three cases: 
    ** 1) Block before free_header_ptr
    *** 1a) Check contiguous with free_header_ptr
    *
    ** 2) Block inbetween free blocks.
    *** 2a) 
    *
    ** 3) Block at end of space
    **************************************************************************/

    QHEADER *freeing_block = (QHEADER*)ptr - 1;

    if (freeing_block < free_header_ptr)
    {
        //Check if contigous with free_header_ptr
        if (freeing_block + freeing_block->size == free_header_ptr)
        {
            freeing_block->next_free_block = free_header_ptr->next_free_block;
            freeing_block->size += free_header_ptr->size;
        }
        else
        {
            freeing_block->next_free_block = free_header_ptr;
        }

        free_header_ptr = freeing_block;
        return;
    }

    QHEADER *prev = NULL;
    QHEADER *curr;

    // Two cases, inbetween or at end.
    for(curr = free_header_ptr; curr && curr < freeing_block;
         prev = curr, curr = curr->next_free_block)
    {
        //if ()

    }




}