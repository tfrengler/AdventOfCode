#ifndef LIB_NUMERIC_H
#define LIB_NUMERIC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum _IntegerType {
    U8,
    I8,
    U16,
    I16,
    U32,
    I32,
    U64,
    I64
} IntegerType;

typedef struct _IntegerArray {
    int32_t Size;
    IntegerType Type;
    union {
        uint8_t *u8Data;
        int8_t *i8Data;
        uint16_t *u16Data;
        int16_t *i16Data;
        uint32_t *u32Data;
        int32_t *i32Data;
        uint64_t *u64Data;
        int64_t *i64Data;
    };
} IntegerArray;

bool StringToInt(const char *input, int32_t length, int32_t* output);
bool StringToLong(const char *input, int32_t length, int64_t* output);
bool LongToInt(int64_t input, int32_t *output);

IntegerArray* u8Array_Make(int32_t size, const uint8_t *values);
IntegerArray* i8Array_Make(int32_t size, const int8_t *values);
IntegerArray* u16Array_Make(int32_t size, const uint16_t *values);
IntegerArray* i16Array_Make(int32_t size, const int16_t *values);
IntegerArray* u32Array_Make(int32_t size, const uint32_t *values);
IntegerArray* i32Array_Make(int32_t size, const int32_t *values);
IntegerArray* u64Array_Make(int32_t size, const uint64_t *values);
IntegerArray* i64Array_Make(int32_t size, const int64_t *values);

void IntegerArray_Free(IntegerArray *input, bool freeContent);

uint8_t u8Array_Max(const IntegerArray *input);
int8_t i8Array_Max(const IntegerArray *input);
uint16_t u16Array_Max(const IntegerArray *input);
int16_t i16Array_Max(const IntegerArray *input);
uint32_t u32Array_Max(const IntegerArray *input);
int32_t i32Array_Max(const IntegerArray *input);
uint64_t u64Array_Max(const IntegerArray *input);
int64_t i64Array_Max(const IntegerArray *input);

uint8_t u8Array_Min(const IntegerArray *input);
int8_t i8Array_Min(const IntegerArray *input);
uint16_t u16Array_Min(const IntegerArray *input);
int16_t i16Array_Min(const IntegerArray *input);
uint32_t u32Array_Min(const IntegerArray *input);
int32_t i32Array_Min(const IntegerArray *input);
uint64_t u64Array_Min(const IntegerArray *input);
int64_t i64Array_Min(const IntegerArray *input);

IntegerArray *i32Array_RemoveAt(const IntegerArray* input, int32_t index);

bool OverflowIntOnAdd(int32_t first, int32_t second);
bool OverflowIntOnSub(int32_t first, int32_t second);
bool OverflowIntOnMul(int32_t x, int32_t a);
bool OverflowLongOnAdd(int64_t first, int64_t second);
bool OverflowLongOnSub(int64_t first, int64_t second);
bool OverflowLongOnMul(int64_t x, int64_t a);

#endif
