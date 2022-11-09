
#ifndef AGNETAOS_MEMORY_H
#define AGNETAOS_MEMORY_H


#include <stddef.h>

void* memset(void* ptr, int c, size_t size);
int memcmp(void* s1, void* s2, int count);

void* memcpy(void* dst, const void* src, unsigned int cnt);

#endif //AGNETAOS_MEMORY_H
