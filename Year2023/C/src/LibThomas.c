#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"

/**
 * @brief  Panics and terminates the program with EXIT_FAILURE, caused by an unrecoverable error.
 * @param  message: The message to print to perror.
 * @retval None
 */
void Fatal(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

static size_t Allocations = 0;
static size_t DeAllocations = 0;
static size_t Heap = 0;

#define DEBUG_ALLOCATION() 0

void *Malloc(size_t size)
{
    void *ReturnData = malloc(size);

    if (ReturnData == 0x0) {
        puts("Fatal, malloc failed");
        exit(EXIT_FAILURE);
    }

    Allocations++;
    Heap += size;

#if DEBUG_ALLOCATION()
    printf("%zu bytes of memory requested by %s:%i (%zu allocations)\n", size, __FILE__, __LINE__, Allocations);
#endif

    return ReturnData;
}

void Free(void *ptr) {
    free(ptr);
    DeAllocations++;

#if DEBUG_ALLOCATION()
    printf("%p freed by %s:%i (%zu allocations) \n", ptr, __FILE__, __LINE__, Allocations);
#endif
}

size_t GetAllocations(void) {
    return Allocations;
}

size_t GetDeAllocations(void) {
    return DeAllocations;
}

void PrintAllocations(void) {
    printf("%zu allocations made | %zu de-allocations made\n", Allocations, DeAllocations);
}
