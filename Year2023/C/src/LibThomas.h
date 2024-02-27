#ifndef LIB_THOMAS_H
#define LIB_THOMAS_H

#include <stdint.h>

// NOTE: Only useful for stack allocated arrays. Note that strings will be one extra due to the null terminator!
#define arrayCount(x) (sizeof(x) / sizeof(*x))

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef unsigned char u8;

typedef char** arrayOfStrings;
typedef char* string;

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

#define DEBUG() 1

#if DEBUG()
# define DEBUG_PRINT(f_, ...) printf((f_), __VA_ARGS__)
#else
# define DEBUG_PRINT(f, ...) do {} while (0)
#endif

void Fatal(char* message);

String* File_ReadAllText(const char* fileNameAndPath);
StringArray* File_ReadAllLines(const char* fileNameAndPath);

String* String_Make(const char* content, u16 size);
String* String_Empty(void);
u8 String_StartsWith(const String* input, const String* pattern);

#endif
