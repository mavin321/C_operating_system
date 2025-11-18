/* kernel/memory.h */
#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

void  kheap_init(void);
void* kmalloc(size_t size);
void  kfree(void* ptr);  // stub for now

#endif /* MEMORY_H */
