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
        uint8_t *uint8_tData;
        int8_t *int8_tData;
        uint16_t *uint16_tData;
        int16_t *int16_tData;
        uint32_t *uint32_tData;
        int32_t *int32_tData;
        uint64_t *uint64_tData;
        int64_t *int64_tData;
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

IntegerArray* uint8_tArray_Make(int32_t size, const uint8_t *values);
IntegerArray* int8_tArray_Make(int32_t size, const int8_t *values);
IntegerArray* uint16_tArray_Make(int32_t size, const uint16_t *values);
IntegerArray* int16_tArray_Make(int32_t size, const int16_t *values);
IntegerArray* uint32_tArray_Make(int32_t size, const uint32_t *values);
IntegerArray* int32_tArray_Make(int32_t size, const int32_t *values);
IntegerArray* uint64_tArray_Make(int32_t size, const uint64_t *values);
IntegerArray *int64_tArray_Make(int32_t size, const int64_t *values);

void IntegerArray_Free(IntegerArray *input);

uint64_t uint64_tArray_Max(const IntegerArray *input);
int64_t int64_tArray_Max(const IntegerArray *input);
uint32_t uint32_tArray_Max(const IntegerArray *input);
int32_t int32_tArray_Max(const IntegerArray *input);
uint16_t uint16_tArray_Max(const IntegerArray *input);
int16_t int16_tArray_Max(const IntegerArray *input);
int8_t int8_tArray_Max(const IntegerArray *input);
uint8_t uint8_tArray_Max(const IntegerArray *input);

uint64_t uint64_tArray_Min(const IntegerArray *input);
int64_t int64_tArray_Min(const IntegerArray *input);
uint32_t uint32_tArray_Min(const IntegerArray *input);
int32_t int32_tArray_Min(const IntegerArray *input);
uint16_t uint16_tArray_Min(const IntegerArray *input);
int16_t int16_tArray_Min(const IntegerArray *input);
int8_t int8_tArray_Min(const IntegerArray *input);
uint8_t uint8_tArray_Min(const IntegerArray *input);

#endif
