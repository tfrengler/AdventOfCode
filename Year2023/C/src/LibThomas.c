#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"

#define DEBUG_ALLOCATION() 0

static size_t Allocations = 0;
static size_t DeAllocations = 0;
static size_t Heap = 0;

/*
void (*__free)(void *ptr) = free;
#define free(size) Free(size)

void* (*__malloc)(size_t size) = malloc;
#define malloc(size) Malloc(size)
*/

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

void *Malloc(size_t size)
{
    void *ReturnData = malloc(size);

    if (ReturnData == 0x0) {
        printf("Fatal, malloc failed (%zu bytes requested)\n", size);
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
    printf("%p freed by %s:%i (%zu allocations) \n", ptr, __FILE__, __LINE__, DeAllocations);
#endif
}

size_t GetAllocations(void) {
    return Allocations;
}

size_t GetDeAllocations(void) {
    return DeAllocations;
}

char* GetReadableBytes(size_t bytes) {
    const int32_t i = (int32_t)floor(log((double_t)bytes) / log(1024));
    char* sizes[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
    double_t FinalSize = ((double_t)bytes / pow(1024, i));

    double_t StringSize = (floor(log10(FinalSize)) + 1) + 3;
    printf("DEBUG: StringSize %f", StringSize);
    char* ReturnData = Malloc( (size_t)StringSize );
    ReturnData[(size_t)StringSize-2] = 0;
    ReturnData[(size_t)StringSize-1] = 0;

    sprintf(ReturnData, "%f %s", FinalSize, sizes[i]);
    return ReturnData;
}

void PrintAllocations(void) {
    printf("%zu allocations made | %zu de-allocations made (heap: %s)\n", Allocations, DeAllocations, GetReadableBytes(Heap));
}
