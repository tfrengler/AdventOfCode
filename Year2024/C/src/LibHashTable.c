#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LibHashTable.h"
#include "LibMem.h"

typedef struct {
    HashItem* Items;
    size_t Size;
} HashTable;

static HashTable TheTable = {0};

uint32_t Fnv1aHash(uint8_t *input, size_t length)
{
    uint32_t ReturnData = 2166136261;

    for(size_t index = 0; index < length; index++) {
        ReturnData = ReturnData ^ input[index];
        ReturnData = ReturnData * 16777619;
    }

    return ReturnData;
}

void HashTable_Init(HashItem backingBuffer[], size_t size) {
    assert(backingBuffer != NULL);
    assert(size > 0);
    memset(backingBuffer, 0, size * sizeof(HashItem));

    TheTable.Size = size;
    TheTable.Items = backingBuffer;
}

void HashTable_InsertString(char* key, char value[]) {
    HashTable_Insert(key, value);
}

void HashTable_InsertI32(char* key, int32_t value) {
    #pragma clang diagnostic ignored "-Wint-to-pointer-cast"
    HashTable_Insert(key, (intptr_t*)value);
}

void HashTable_InsertI64(char* key, int64_t value) {
    HashTable_Insert(key, (intptr_t*)value);
}

void HashTable_Insert(char* key, void* value)
{
    uint32_t HashCode = Fnv1aHash((uint8_t*)key, strlen(key));
    uint32_t Index = HashCode % TheTable.Size;

    if (TheTable.Items[Index].Key == NULL) {

        TheTable.Items[Index].Key = key;
        TheTable.Items[Index].Value = value;
        TheTable.Items[Index].Next = NULL;

        return;
    }

    HashItem *Current = &TheTable.Items[Index];

    while(1) {

        if (Current->Next != NULL) {
            Current = Current->Next;
            continue;
        }

        Current->Next = MemRequest(sizeof(HashItem));
        Current->Next->Key = key;
        Current->Next->Value = value;

        break;
    }
}

int32_t HashTable_FindI32(char* key) {
    #pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
    return (int32_t)HashTable_Find(key);
}

int64_t HashTable_FindI64(char* key) {
    return (int64_t)HashTable_Find(key);
}

void* HashTable_Find(char* key)
{
    uint32_t HashCode = Fnv1aHash((uint8_t*)key, strlen(key));
    uint32_t Index = HashCode % TheTable.Size;

    if (TheTable.Items[Index].Key == NULL) {
        return NULL;
    }

    if (TheTable.Items[Index].Key == key) {
        return TheTable.Items[Index].Value;
    }

    HashItem *Next = TheTable.Items[Index].Next;
    while(1) {

        if (Next == NULL) {
            return NULL;
        }

        if (Next->Key == key) {
            return Next->Value;
        }

        Next = Next->Next;
    }
}

void HashTable_Teardown(void) {

    for(size_t index = 0; index < TheTable.Size; index++) {
        HashItem *Current = &TheTable.Items[index];

        if (Current == NULL) {
            continue;
        }

        Current = Current->Next;

        while(Current != NULL) {
            void* Temp = Current;
            Current = Current->Next;
            MemFree(Temp);
        }
    }

}
