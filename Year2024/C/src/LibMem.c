#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibMem.h"
#include "LibThomas.h"

static uint8_t* MemStart = nullptr;
static size_t Offset = 0;
static size_t ArenaSize = 0;
static size_t ArenaRemaining = 0;

static size_t Allocations = 0;
static size_t DeAllocations = 0;
static size_t Heap = 0;
static size_t Alignment = 8; // Hardcoded 8 byte alignment because we assume we're always on 64-bit systems

void* MemArena_Request(size_t bytes) {
    if (bytes > ArenaRemaining) {
        printf("FATAL: Requested %zu bytes but %s remains in the arena", bytes, GetReadableBytes(ArenaRemaining));
        exit(EXIT_FAILURE);
    }
#if DEBUG_ALLOCATION()
    printf("Requested %zu bytes of memory from arena\n", bytes);
#endif

    uintptr_t ThePointer = (uintptr_t)&MemStart[Offset];
    uintptr_t ModuloResult = ThePointer % Alignment;
    ArenaRemaining -= bytes;
    Heap += bytes;

    if (ModuloResult != 0) {
        size_t Adjustment = Alignment - ModuloResult;
#if DEBUG_ALLOCATION()
    printf("WARNING: Address not aligned, adjusting by %zu bytes\n", Adjustment);
#endif
        ThePointer += Adjustment;
        ArenaRemaining -= Adjustment;
        Heap += Adjustment;
    }

    Offset += (bytes + ModuloResult);
    void *ReturnData = (void*)ThePointer;

    memset(ReturnData, 0, bytes);

#if DEBUG_ALLOCATION()
    printf("Returning pointer to %zu (%s remaining)\n", (uintptr_t)ReturnData, GetReadableBytes(ArenaRemaining));
#endif

    return ReturnData;
}

void MemArena_Teardown(void) {
#if DEBUG_ALLOCATION()
    puts("Tearing down memory arena");
#endif
    if (MemStart == nullptr) return;
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

// https://www.gingerbill.org/article/2019/02/08/memory-allocation-strategies-002/
void MemArena_Init(size_t size) {
#if DEBUG_ALLOCATION()
    printf("Initializing memory arena with size of %s\n", GetReadableBytes(size));
#endif

    MemStart = malloc(size);
    assert(MemStart != nullptr);

    ArenaSize = size;
    ArenaRemaining = size;
    _Malloc = &MemArena_Request;
    _Free = &memFreeNoop;

#if DEBUG_ALLOCATION()
    printf("Done, start address is at: %zu\n", (uintptr_t)MemStart);
#endif
}
