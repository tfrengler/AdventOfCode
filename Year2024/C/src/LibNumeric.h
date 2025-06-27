#ifndef LIB_NUMERIC_H
#define LIB_NUMERIC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct _u8Array {
    size_t Capacity;
    size_t Size;
    uint8_t *Data;
} u8Array;

typedef struct _i8Array {
    size_t Capacity;
    size_t Size;
    int8_t *Data;
} i8Array;

typedef struct _u16Array {
    size_t Capacity;
    size_t Size;
    uint16_t *Data;
} u16Array;

typedef struct _i16Array {
    size_t Capacity;
    size_t Size;
    int16_t *Data;
} i16Array;

typedef struct _u32Array {
    size_t Capacity;
    size_t Size;
    uint32_t *Data;
} u32Array;

typedef struct _i32Array {
    // Max amount of values the array can contain.
    size_t Capacity;
    // The current size of the array (ie. how many values does it contain)
    size_t Size;
    // Pointer to the first value in the array
    int32_t *Data;
} i32Array;

typedef struct _u64Array {
    size_t Capacity;
    size_t Size;
    uint64_t *Data;
} u64Array;

typedef struct _i64Array {
    size_t Capacity;
    size_t Size;
    int64_t *Data;
} i64Array;

int64_t i64Array_Max(const i64Array *input);
int64_t i64Array_Min(const i64Array *input);
bool i64Array_Equal(const i64Array *first, const i64Array *second);
int64_t i64Array_Sum(const i64Array *input);
int64_t i64Array_Average(const i64Array *input);
int64_t i64Array_Median(const i64Array *input);
i64Array* i64Array_Copy(const i64Array *input, i64Array *output);
i64Array* i64Array_CopyM(const i64Array *input);
void i64Array_SortAsc(i64Array *input);
void i64Array_SortDesc(i64Array *input);
i64Array *i64Array_RemoveAt(const i64Array* input, size_t index);

bool StringToInt(const char *input, int32_t length, int32_t* output);
bool StringToLong(const char *input, int32_t length, int64_t* output);
bool LongToInt(int64_t input, int32_t *output);


bool OverflowIntOnAdd(int32_t first, int32_t second);
bool OverflowIntOnSub(int32_t first, int32_t second);
bool OverflowIntOnMul(int32_t x, int32_t a);
bool OverflowLongOnAdd(int64_t first, int64_t second);
bool OverflowLongOnSub(int64_t first, int64_t second);
bool OverflowLongOnMul(int64_t x, int64_t a);

#endif
