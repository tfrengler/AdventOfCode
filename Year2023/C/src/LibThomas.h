#ifndef LIB_THOMAS_H
#define LIB_THOMAS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Enables extra checks, such as NULL checks after each malloc, asserts on function parameters etc.
#define DEBUG() 1

// To set up use vscode with the following extensions:
// clangd (intellisense) and CodeLLDB (for debugging)
// For toolchain use MSYS2 with the following package(s): pacman -S mingw-w64-clang-x86_64-toolchain
// Use the following compiler flags for debugging. For release-like mode omit -g3, fsanitize-flags and use -O3
/*
    -std=c17
    -Wall
    -Wextra
    -Wconversion
    -Wshadow-all
    -Wundef
    -Wunreachable-code
    -Wuninitialized
    -Wold-style-cast
    -Wno-error=unused-variable
    -Wfloat-equal
    -pedantic-errors
    -Wtype-limits
    -Wno-unused-function
    -Wno-sign-conversion
    -Wdouble-promotion
    -Wformat=2
    -Wformat-pedantic
    -Wfor-loop-analysis
	-pthread
	-fsanitize=undefined
	-fsanitize=address
	-fsanitize-trap
	-fno-omit-frame-pointer
	-fno-common
	-g3
	-O0
*/

// NOTE: Only useful for stack allocated arrays. Note that strings will be one extra due to the null terminator!
#define arrayCount(x) (sizeof(x) / sizeof(*x))

/* The maximum size of a string as used by String-instances. */
static const int32_t STRING_MAX_SIZE = 65535;

/* Represents a wrapper around a C-string (char*) with a max size of 64kb. Content is the string and Size is the length without the null-terminator.*/
typedef struct _String {
	int32_t Size; // Size is until but not including the line terminator
	char *Content;
} String;

/* Represents a wrapper around an fixed length array of String*-instances. Count is the amount of structs in Contents, and Contents is the array (ptr to the start)*/
typedef struct _StringArray {
	int32_t Count;
	String *Contents[];
} StringArray;

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

#if DEBUG()
#define DEBUG_PRINT(f_, ...) printf((f_), __VA_ARGS__)
#else
#define DEBUG_PRINT(f, ...) \
	do {                    \
	} while (0)
#endif

void Fatal(const char *message);

StringArray *File_ReadAllLines(const char *fileNameAndPath);
StringArray *String_Split(const String *inputString, char delimiter);
void StringArray_Free(StringArray *input);

void String_Free(String *input);
String *File_ReadAllText(const char *fileNameAndPath);
String *String_Make(const char *content, int32_t size);
String *String_Empty(void);
bool String_StartsWith(const String *input, const String *pattern, bool caseInsensitive);
bool String_EndsWith(const String *input, const String *pattern, bool caseInsensitive);
bool String_Contains(const String *input, const String *pattern, bool caseInsensitive);
bool String_Equals(const String *original, const String *compare, bool caseInsensitive);
String *String_Trim(const String *input);
bool StringToInt(const char *input, int32_t length, int* output);

IntegerArray* u8Array_Make(int32_t size, const uint8_t *values);
IntegerArray* i8Array_Make(int32_t size, const int8_t *values);
IntegerArray* u16Array_Make(int32_t size, const uint16_t *values);
IntegerArray* i16Array_Make(int32_t size, const int16_t *values);
IntegerArray* u32Array_Make(int32_t size, const uint32_t *values);
IntegerArray* i32Array_Make(int32_t size, const int32_t *values);
IntegerArray* u64Array_Make(int32_t size, const uint64_t *values);
IntegerArray* i64Array_Make(int32_t size, const int64_t *values);

void IntegerArray_Free(IntegerArray *input);

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

#endif
