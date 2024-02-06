#ifndef _TYPES_H_
#define _TYPES_H_

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "errno.h"
#include "string.h"

#define arrayCount(x) (sizeof(x) / sizeof(*x))

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef unsigned char byte;

typedef char** arrayOfStrings;
typedef char *string;

typedef int64_t* arrayOfInt64;
typedef int32_t* arrayOfInt32;
typedef int16_t* arrayOfInt16;
typedef int8_t *arrayOfInt8;

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
    int64 FileSize = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    string FileContents = malloc(FileSize+1);
    int64 Index = 0;

    if (FileContents == NULL) {
        Fatal("Error reading file contents. Cannot allocate memory", 1000);
        return NULL;
    }

    while (1) {
        int32 NextChar = fgetc(fileHandle);
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
