
#ifndef AGNETAOS_KHEAP_H
#define AGNETAOS_KHEAP_H

#include <stdint.h>
#include <stddef.h>
void* kmalloc(size_t size);
void kheap_init();
void* kfree(void* ptr);
#endif //AGNETAOS_KHEAP_H
