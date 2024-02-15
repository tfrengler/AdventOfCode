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

typedef struct _String {
    u16 Size; // Size is until but not including the line terminator
    char Content[];
} String;

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

/**
 * @brief  Panics and terminates the program, caused by an unrecoverable error
 * @param  message: The message to print to stdout before terminating
 * @param  code: The code to pass to exit()
 * @retval None
 */
void Fatal(char* message, int code);

/**
 * Opens a file, and reads out its text content
 * @param fileNameAndPath: the name and location of the file, including extension
 * @retval A string with the contents of the file or NULL if an error happened (file cannot be opened or malloc failed)
 */
string File_ReadAllText(char* fileNameAndPath);

String* File_ReadAllText_S(char* fileNameAndPath);

StringArray* File_ReadAllLines(char* fileNameAndPath);

String* String_Make(char* content, u16 size);

#endif
