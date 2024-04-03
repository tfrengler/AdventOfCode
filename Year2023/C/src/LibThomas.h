#ifndef LIB_THOMAS_H
#define LIB_THOMAS_H

#include <stdint.h>
#include <stdbool.h>

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
static const u16 STRING_MAX_SIZE = 65535;

/* Represents a wrapper around a C-string (char*) with a max size of 64kb. Content is the string and Size is the length without the null-terminator.*/
typedef struct _String {
    u16 Size; // Size is until but not including the line terminator
    char* Content;
} String;

/* Represents a wrapper around an fixed length array of String*-instances. Count is the amount of structs in Contents, and Contents is the array (ptr to the start)*/
typedef struct _StringArray {
    i64 Count;
    String* Contents[];
} StringArray;

typedef struct _i32Array {
    i64 Size;
    i32* Value;
} i32Array;

typedef struct _i64Array {
    i64 Size;
    i64* Value;
} i64Array;

typedef struct _i16Array {
    i64 Size;
    i16* Value;
} i16Array;

typedef struct _i8Array {
    i64 Size;
    i8* Value;
} i8Array;

typedef struct _u32Array {
    i64 Size;
    u32* Value;
} u32Array;

typedef struct _u64Array {
    i64 Size;
    u64* Value;
} u64Array;

typedef struct _u16Array {
    i64 Size;
    u16* Value;
} u16Array;

typedef struct _u8Array {
    i64 Size;
    u8* Value;
} u8Array;

#if DEBUG()
# define DEBUG_PRINT(f_, ...) printf((f_), __VA_ARGS__)
#else
# define DEBUG_PRINT(f, ...) do {} while (0)
#endif

void Fatal(const char* message);

StringArray* File_ReadAllLines(const char* fileNameAndPath);
StringArray* String_Split(const String* inputString, char delimiter);
void StringArray_Free(StringArray* input);


void String_Free(String* input);
String* File_ReadAllText(const char* fileNameAndPath);
String* String_Make(const char* content, u16 size);
String* String_Empty(void);
bool String_StartsWith(const String* input, const String* pattern, bool caseInsensitive);
bool String_EndsWith(const String* input, const String* pattern, bool caseInsensitive);
bool String_Contains(const String* input, const String* pattern, bool caseInsensitive);
bool String_Equals(const String* original, const String* compare, bool caseInsensitive);
String* String_Trim(String* input);

i32 i32Array_Max(const i32Array* input);
i64 i64Array_Max(const i64Array* input);
i16 i16Array_Max(const i16Array* input);
i8 i8Array_Max(const i8Array* input);
u64 u64Array_Max(const u64Array* input);
u32 u32Array_Max(const u32Array* input);
u16 u16Array_Max(const u16Array* input);
u8 u8Array_Max(const u8Array* input);

i32Array* i32Array_Make(i64 size, const i32* values);
void i32Array_Free(i32Array* input);

#endif
