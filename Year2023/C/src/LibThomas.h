#ifndef _TYPES_H_
#define _TYPES_H_

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "errno.h"
#include "string.h"

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

typedef struct _i32Array {
    i32 Size;
    i32* Value;
} i32Array;

typedef struct _i64Array {
    i32 Size;
    i64* Value;
} i64Array;

typedef struct _i16Array {
    i32 Size;
    i16* Value;
} i16Array;

typedef struct _i8Array {
    i32 Size;
    i8* Value;
} i8Array;

#define DEBUG() 1

#if DEBUG()
# define DEBUG_PRINT(f_, ...) printf((f_), __VA_ARGS__)
#else
# define DEBUG_PRINT(f, ...) do {} while (0)
#endif

/**
 * @brief  Panics and terminates the program
 * @param  message: The message to print to stdout before terminating
 * @param  code: The code to pass to exit()
 * @retval None
 */
void Fatal(char* message, int code)
{
    perror(message);
    exit(code);
}

/**
 * Opens a file, and reads out its text content
 * @param fileNameAndPath: the name and location of the file, including extension
 * @retval A string with the contents of the file or NULL if an error happened (file cannot be opened or malloc failed)
 */
string File_Read(char* fileNameAndPath)
{
    FILE *fileHandle = fopen(fileNameAndPath, "r");

    if (fileHandle == NULL) {
        Fatal("Error reading file contents. File or directory not found", errno);
        return NULL;
    }

    fseek(fileHandle, 0, SEEK_END);
    i64 FileSize = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    string FileContents = malloc(FileSize+1);
    i64 Index = 0;

    if (FileContents == NULL) {
        Fatal("Error reading file contents. Cannot allocate memory", 1000);
        return NULL;
    }

    while (1) {
        i32 NextChar = fgetc(fileHandle);
        if (NextChar == EOF) break;
        FileContents[Index] = (char)NextChar;
        Index++;
    }

    FileContents[Index+1] = '\0';
    DEBUG_PRINT("Filesize (index): %d\n", Index+1);

    string ReturnData = malloc(FileSize + 2);

    if (ReturnData == NULL) {
        Fatal("Error reading file contents. Cannot allocate memory", 1001);
        return NULL;
    }

    strcpy(ReturnData, FileContents);
    free(FileContents);
    fclose(fileHandle);

    return ReturnData;
}

#endif
