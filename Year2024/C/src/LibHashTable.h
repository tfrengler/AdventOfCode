#ifndef LIB_HASHTABLE_H
#define LIB_HASHTABLE_H

#include <stdint.h>

typedef struct _HashItem {
    void* Value;
    char* Key;
    struct _HashItem *Next;
} HashItem;

uint32_t Fnv1aHash(uint8_t *input, size_t length);
void HashTable_Init(HashItem backingBuffer[], size_t size);
void HashTable_Insert(char* key, void* value);
void* HashTable_Find(char* key);
void HashTable_Teardown(void);

void HashTable_InsertI32(char* key, int32_t value);
void HashTable_InsertI64(char* key, int64_t value);

int32_t HashTable_FindI32(char* key);
int64_t HashTable_FindI64(char* key);

#endif
