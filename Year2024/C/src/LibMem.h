#ifndef LIB_MEM_H
#define LIB_MEM_H

#include <stddef.h>

#define DEBUG_ALLOCATION() 0

void MemArena_Init(const size_t size);
void MemArena_Teardown(void);
void MemFree(void* ptr);
void *MemRequest(const size_t size);
size_t GetAllocations(void);
void PrintAllocations(void);
size_t GetDeAllocations(void);

#endif
