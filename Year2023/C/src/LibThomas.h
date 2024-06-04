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

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

/* The maximum size of a string as used by String-instances. */
static const int32_t STRING_MAX_SIZE = 65535;

/* Represents a wrapper around a C-string (char*) with a max size of 64kb. Content is the string and Size is the length without the null-terminator.*/
typedef struct _String {
	i32 Size; // Size is until but not including the line terminator
	char *Content;
} String;

/* Represents a wrapper around an fixed length array of String*-instances. Count is the amount of structs in Contents, and Contents is the array (ptr to the start)*/
typedef struct _StringArray {
	i32 Count;
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
    i32 Size;
    IntegerType Type;
    union {
        u8 *u8Data;
        i8 *i8Data;
        u16 *u16Data;
        i16 *i16Data;
        u32 *u32Data;
        i32 *i32Data;
        u64 *u64Data;
        i64 *i64Data;
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
String *String_Make(const char *content, i32 size);
String *String_Empty(void);
bool String_StartsWith(const String *input, const String *pattern, bool caseInsensitive);
bool String_EndsWith(const String *input, const String *pattern, bool caseInsensitive);
bool String_Contains(const String *input, const String *pattern, bool caseInsensitive);
bool String_Equals(const String *original, const String *compare, bool caseInsensitive);
String *String_Trim(const String *input);
bool StringToInt(const char *input, int32_t length, int* output);

IntegerArray* u8Array_Make(i32 size, const u8 *values);
IntegerArray* i8Array_Make(i32 size, const i8 *values);
IntegerArray* u16Array_Make(i32 size, const u16 *values);
IntegerArray* i16Array_Make(i32 size, const i16 *values);
IntegerArray* u32Array_Make(i32 size, const u32 *values);
IntegerArray* i32Array_Make(i32 size, const i32 *values);
IntegerArray* u64Array_Make(i32 size, const u64 *values);
IntegerArray *i64Array_Make(i32 size, const i64 *values);

void IntegerArray_Free(IntegerArray *input);

u64 u64Array_Max(const IntegerArray *input);
i64 i64Array_Max(const IntegerArray *input);
u32 u32Array_Max(const IntegerArray *input);
i32 i32Array_Max(const IntegerArray *input);
u16 u16Array_Max(const IntegerArray *input);
i16 i16Array_Max(const IntegerArray *input);
i8 i8Array_Max(const IntegerArray *input);
u8 u8Array_Max(const IntegerArray *input);

u64 u64Array_Min(const IntegerArray *input);
i64 i64Array_Min(const IntegerArray *input);
u32 u32Array_Min(const IntegerArray *input);
i32 i32Array_Min(const IntegerArray *input);
u16 u16Array_Min(const IntegerArray *input);
i16 i16Array_Min(const IntegerArray *input);
i8 i8Array_Min(const IntegerArray *input);
u8 u8Array_Min(const IntegerArray *input);

#endif
