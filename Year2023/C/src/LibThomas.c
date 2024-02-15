#include "LibThomas.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Fatal(char* message, int code)
{
    perror(message);

    exit(code);
}

/**
 * @brief  Creates an instance of String. Content is memcopied so make sure to free() content if heap allocated!
 * @param  content: A reference to the string (char-array) that represents the string (including the nul-terminator)
 * @param  size: The size of the string MINUS the nul-terminator
 * @retval A pointer to the newly created String wrapped around the C-string
 */
String* String_Make(char* content, u16 size)
{
#if DEBUG()
    assert(content != NULL);
    assert(size > 0);
    assert(content[size] == '\0');
#endif

    String* ReturnData = malloc(sizeof(struct _String) + sizeof(char[size+1]));
#if DEBUG()
    if (ReturnData == NULL) Fatal("Failed to malloc memory for String*", 1000);
#endif
    ReturnData->Size = size;
    memcpy(ReturnData->Content, content, size+1);

    return ReturnData;
}

string File_ReadAllText(char* fileNameAndPath)
{
    FILE *fileHandle = fopen(fileNameAndPath, "r");

    if (fileHandle == NULL) {
        puts("Error reading file contents. File or directory not found");
        return NULL;
    }

    fseek(fileHandle, 0, SEEK_END);
    i64 FileSize = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    string FileContents = malloc(FileSize+1);
    i64 Index = 0;

#if DEBUG()
    if (FileContents == NULL) {
        Fatal("Error reading file contents. Cannot allocate memory", 1000);
    }
#endif

    while (1) {
        i32 NextChar = fgetc(fileHandle);
        if (NextChar == EOF) break;
        FileContents[Index] = (char)NextChar;
        Index++;
    }

    FileContents[Index+1] = '\0';

    // +1 for the null terminator, and +2 because index started at 0
    i64 FinalSize = Index + 2;
    string ReturnData = malloc(FinalSize);

#if DEBUG()
    if (ReturnData == NULL) {
        Fatal("Error reading file contents. Cannot allocate memory", 1001);
        return NULL;
    }
#endif

    memcpy(ReturnData, FileContents, FinalSize);
    free(FileContents);
    fclose(fileHandle);

    return ReturnData;
}

String* File_ReadAllText_S(char* fileNameAndPath)
{
    FILE *fileHandle = fopen(fileNameAndPath, "r");

    if (fileHandle == NULL) {
        puts("Error reading file contents. File or directory not found");
        return NULL;
    }

    fseek(fileHandle, 0, SEEK_END);
    i64 FileSize = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    string FileContents = malloc(FileSize+1);
    i32 Index = 0;

#if DEBUG()
    if (FileContents == NULL) {
        Fatal("Error reading file contents. Cannot allocate memory", 1001);
    }
#endif

    while (1) {
        i32 NextChar = fgetc(fileHandle);
        if (NextChar == EOF) break;
        FileContents[Index] = (char)NextChar;
        Index++;

        if ((Index-2) > STRING_MAX_SIZE)
        {
            Fatal("Text file content larger than max size string", 1000);
        }
    }

    FileContents[Index+1] = '\0';

    // +1 for the null terminator, and +2 because index started at 0
    u16 FinalSizeWithTerminator = (u16)Index + 2;
#if DEBUG()
    assert(FinalSizeWithTerminator <= STRING_MAX_SIZE);
#endif

    FileContents = realloc(FileContents, FinalSizeWithTerminator);

#if DEBUG()
    if (FileContents == NULL) {
        Fatal("Error reading file contents. Cannot allocate memory", 1001);
        return NULL;
    }
#endif

    fclose(fileHandle);
    String* ReturnData = String_Make(FileContents, FinalSizeWithTerminator-1);
    free(FileContents);

    return ReturnData;
}

StringArray* File_ReadAllLines(char* fileNameAndPath)
{
    String* StringData = File_ReadAllText_S(fileNameAndPath);
    if (StringData == NULL) return NULL;

    if (StringData->Size == 0)
    {
        StringArray* ReturnData = malloc(sizeof(struct _String));
        ReturnData->Count = 0;
        return ReturnData;
    }

    i32 LineCount = 1;
    for(i32 Index = 0; Index < StringData->Size; Index++)
    {
        if (StringData->Content[Index] == '\n')
        {
            LineCount++;
        }
    }

    StringArray* ReturnData = malloc(sizeof(String) + sizeof(String*[LineCount]));
#if DEBUG()
    if (ReturnData == NULL) Fatal("Failed to allocate memory for StringArray return data in File_ReadAllLines", 666);
#endif

    ReturnData->Count = LineCount;

    i32 StringStartIndex = 0;
    i32 StringLength = 0;

    /*for(i32 IndexOuter = 0; IndexOuter <= LineCount; IndexOuter++)
    {
        for(i32 IndexInner = StringStartIndex; IndexInner <= StringData->Size; IndexInner++)
        {
            if (StringData->Content[IndexInner] == '\n')
            {
                break;
            }
            StringLength++;
        }

        String* Current = malloc(sizeof(struct _String));
        Current->Size = StringLength;
        //Current->Content = test;
        ReturnData->Contents[0] = Current;

        int debug = 42;
        break;
        *String* Current = malloc(sizeof(String));
        CheckMalloc(Current);

        Current->Size = StringEndIndex - StringStartIndex;
        Current->Content = malloc(Current->Size + 1);
        CheckMalloc(Current->Content);

        ReturnData->Contents[IndexOuter] = *Current;
    }*/

    return NULL;
}


