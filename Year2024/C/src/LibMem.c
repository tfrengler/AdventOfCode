#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibMem.h"
#include "LibThomas.h"

static void* MemStart = nullptr;
static void* MemCurrent = nullptr;
static size_t ArenaSize = 0;
static size_t ArenaRemaining = 0;

static size_t Allocations = 0;
static size_t DeAllocations = 0;
static size_t Heap = 0;

void* MemArena_Request(size_t bytes) {
    if (bytes > ArenaRemaining) {
        printf("FATAL: Requested %s but %s remains in the arena", GetReadableBytes(bytes), GetReadableBytes(ArenaRemaining));
        exit(EXIT_FAILURE);
    }
#if DEBUG_ALLOCATION()
    printf("Requested memory from arena: %s\n", GetReadableBytes(bytes));
#endif

    MemCurrent = ((char*)MemCurrent + bytes + 1);
    ArenaRemaining -= bytes;
    Heap += bytes;

#if DEBUG_ALLOCATION()
    printf("Advancing pointer to %p (%s remaining)\n", MemCurrent, GetReadableBytes(ArenaRemaining));
#endif
    return MemCurrent;
}

void MemArena_Teardown(void) {
#if DEBUG_ALLOCATION()
    puts("Tearing down memory arena");
#endif
    free(MemStart);
}

void *memAlloc(size_t size)
{
    void *ReturnData = malloc(size);

    if (ReturnData == nullptr) {
        printf("Fatal, malloc failed (%zu bytes requested)\n", size);
        exit(EXIT_FAILURE);
    }

#if DEBUG()
    memset(ReturnData, 0, size);
#endif
    Allocations++;
    Heap += size;

#if DEBUG_ALLOCATION()
    printf("%zu bytes of memory requested (%zu allocations)\n", size, Allocations);
#endif

    return ReturnData;
}

void memFree(void *ptr)
{
#if DEBUG()
    if (ptr == nullptr) {
        Fatal("Freeing a null-pointer");
    }
#endif

    free(ptr);

#if DEBUG_ALLOCATION()
    printf("%p freed (%zu de-allocations) \n", ptr, DeAllocations);
#endif

    ptr = nullptr;
    DeAllocations++;
}

// #pragma clang diagnostic ignored "-Wunused-parameter"
void memFreeNoop(void* ptr) {
    #if DEBUG_ALLOCATION()
        printf("Freeing %p is a no-op\n", ptr);
    #endif
}

void* (*_Malloc)(size_t bytes) = &memAlloc;
void (*_Free)(void* ptr) = &memFree;

void *MemRequest(size_t bytes) {
    return _Malloc(bytes);
}

void MemFree(void *ptr) {
    _Free(ptr);
}

size_t GetAllocations(void) {
    return Allocations;
}

size_t GetDeAllocations(void) {
    return DeAllocations;
}

void PrintAllocations(void)
{
    char* ReadableBytes = GetReadableBytes(Heap);
    if (ReadableBytes == NULL)
    {
        puts("No allocations made");
        return;
    }

    if (ArenaSize == 0) {
        printf("%zu allocations made | %zu de-allocations made (heap size: %s)\n", Allocations, DeAllocations, ReadableBytes);
    }
    else {
        printf("%s used of memory arena (%s remaining) of %s\n", ReadableBytes, GetReadableBytes(ArenaRemaining), GetReadableBytes(ArenaSize));
    }

    free(ReadableBytes);
}

void MemArena_Init(size_t size) {
#if DEBUG_ALLOCATION()
    printf("Initializing memory arena with size of %s\n", GetReadableBytes(size));
#endif

    MemStart = malloc(size);
    MemCurrent = MemStart;
    assert(MemStart != nullptr);

    ArenaSize = size;
    ArenaRemaining = size;
    _Malloc = &MemArena_Request;
    _Free = &memFreeNoop;

#if DEBUG_ALLOCATION()
    printf("Done, start address is at: %p\n", MemStart);
#endif
}
