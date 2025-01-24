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
    size_t Capacity;
    size_t Size;
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

int32_t i32Array_Max(const i32Array *input);
uint32_t u32Array_Max(const u32Array *input);
int32_t i32Array_Min(const i32Array *input);
uint32_t u32Array_Min(const u32Array *input);
bool i32Array_Equal(const i32Array *first, const i32Array *second);
bool u32Array_Equal(const u32Array *first, const u32Array *second);
int32_t i32Array_Sum(const i32Array *input);
uint32_t u32Array_Sum(const u32Array *input);
uint32_t u32Array_Average(const u32Array *input);
int32_t i32Array_Average(const i32Array *input);
int32_t i32Array_Median(const i32Array *input);
uint32_t u32Array_Median(const u32Array *input);

int64_t i64Array_Max(const i64Array *input);
uint64_t u64Array_Max(const u64Array *input);
int64_t i64Array_Min(const i64Array *input);
uint64_t u64Array_Min(const u64Array *input);
bool i64Array_Equal(const i64Array *first, const i64Array *second);
bool u64Array_Equal(const u64Array *first, const u64Array *second);
int64_t i64Array_Sum(const i64Array *input);
uint64_t u64Array_Sum(const u64Array *input);
uint64_t u64Array_Average(const u64Array *input);
int64_t i64Array_Average(const i64Array *input);
int64_t i64Array_Median(const i64Array *input);
uint64_t u64Array_Median(const u64Array *input);

bool StringToInt(const char *input, int32_t length, int32_t* output);
bool StringToLong(const char *input, int32_t length, int64_t* output);
bool LongToInt(int64_t input, int32_t *output);


// IntegerArray *i32Array_RemoveAt(const IntegerArray* input, int32_t index);

bool OverflowIntOnAdd(int32_t first, int32_t second);
bool OverflowIntOnSub(int32_t first, int32_t second);
bool OverflowIntOnMul(int32_t x, int32_t a);
bool OverflowLongOnAdd(int64_t first, int64_t second);
bool OverflowLongOnSub(int64_t first, int64_t second);
bool OverflowLongOnMul(int64_t x, int64_t a);

#endif
