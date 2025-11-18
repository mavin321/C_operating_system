/* kernel/memory.c */
#include "memory.h"

#define KHEAP_SIZE (1024 * 1024)   /* 1MB heap */

static uint8_t  kheap[KHEAP_SIZE];
static size_t   kheap_offset = 0;

void kheap_init(void)
{
    kheap_offset = 0;
}

void* kmalloc(size_t size)
{
    if (kheap_offset + size > KHEAP_SIZE) {
        return 0; // out of memory
    }

    void* ptr = &kheap[kheap_offset];
    kheap_offset += size;
    return ptr;
}

void kfree(void* ptr)
{
    (void)ptr;
    // No-op: bump allocator can't free; left as an exercise
}
