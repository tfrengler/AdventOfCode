#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "LibThomas.h"

#define DEBUG_ALLOCATION() 0

static size_t Allocations = 0;
static size_t DeAllocations = 0;
static size_t Heap = 0;

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

#if DEBUG()
    memset(ReturnData, 0, size);
#endif
    Allocations++;
    Heap += size;

#if DEBUG_ALLOCATION()
    printf("%zu bytes of memory requested by %s:%i (%zu allocations)\n", size, __FILE__, __LINE__, Allocations);
#endif

    return ReturnData;
}

/**
 * @brief   De-allocates memory pointed to by a pointer and changes its value to NULL
 * @param   input: The pointer to free.
 * @retval  None.
 */
void Free(void *ptr)
{
#if DEBUG()
    if (ptr == NULL) {
        Fatal("Freeing a null-pointer");
    }
#endif

    free(ptr);
    ptr = 0x0;
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
    if (bytes == 0) return NULL;
    const int32_t i = (int32_t)floor(log((double_t)bytes) / log(1024));
    char* Sizes[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
    double_t FinalSize = ((double_t)bytes / pow(1024, i));

    size_t StringSize = (size_t)((floor(log10(FinalSize)) + 1) + 3);
    char* ReturnData = malloc(StringSize + 1);
    memset(ReturnData, 0, StringSize + 1);

    sprintf(ReturnData, "%zu %s", (size_t)round(FinalSize), Sizes[i]);
    return ReturnData;
}

void PrintAllocations(void)
{
    char* ReadableBytes = GetReadableBytes(Heap);
    if (ReadableBytes == NULL)
    {
        puts("No allocations made");
        return;
    }
    printf("%zu allocations made | %zu de-allocations made (heap size: %s)\n", Allocations, DeAllocations, ReadableBytes);
    free(ReadableBytes);
}

static struct timespec start;
static struct timespec end;

void TimerStart(void)
{
    clock_gettime(CLOCK_MONOTONIC, &start);
}

void TimerStop(void)
{
    clock_gettime(CLOCK_MONOTONIC, &end);
}

void PrintTimer(void)
{
    printf(
        "Time taken: %.5f seconds\n",
        ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
        ((double)start.tv_sec + 1.0e-9*start.tv_nsec));
}
