#include "LibThomas.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errno.h"

/**
 * @brief  Panics and terminates the program with EXIT_FAILURE, caused by an unrecoverable error.
 * @param  message: The message to print to perror.
 * @retval None
 */
void Fatal(char* message)
{
    if (errno == 0) errno = EBADMSG;
    perror(message);
    exit(EXIT_FAILURE);
}

/**
 * @brief  Checks whether a given input string starts with a given string pattern. Case-sensitive.
 * @param  input: The input string to check
 * @param  pattern: The pattern to check for.
 * @retval 1 if input starts with pattern, 0 otherwise.
 */
u8 String_StartsWith(const String* input, const String* pattern)
{
#if DEBUG()
    if (input == NULL || pattern == NULL) Fatal("String_StartsWith: argument 'input' or 'pattern' is NULL");
#endif

    if (pattern->Size > input->Size) return 0;

    for(i32 Index = 0; Index < pattern->Size; Index++)
    {
        if (input->Content[Index] != pattern->Content[Index])
        {
            return 0;
        }
    }

    return 1;
}

u8 String_Compare(const String* original, const String* compare, u8 caseInsensitive)
{
#if DEBUG()
    if (original == NULL || compare == NULL) Fatal("String_Compare: argument 'original' or 'compare' is NULL");
#endif

    if (original->Size == 0 || compare->Size == 0) return 0;
    if (compare->Size != original->Size) return 0;

    for(i32 Index = 0; Index < original->Size; Index++)
    {
        char CurrentOriginalChar = original->Content[Index];
        char CurrentCompareChar = compare->Content[Index];
        
        if (caseInsensitive)
        {
            CurrentOriginalChar = (char)tolower(CurrentOriginalChar);
            CurrentCompareChar = (char)tolower(CurrentCompareChar);
        }

        if (CurrentOriginalChar != CurrentCompareChar)
        {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief  Creates a heap-allocated instance of String around a char*. The original string is copied so it is safe to free it afterwards.
 * @param  content: A reference to the string (char-array) that represents the string (including the null-terminator).
 * @param  size: The size of the string MINUS the null-terminator. Must be greater than 0.
 * @retval A pointer to the newly created String wrapped around the C-string.
 */
String* String_Make(const char* content, u16 size)
{
#if DEBUG()
    assert(content != NULL);
    assert(size > 0);
    assert(content[size] == '\0');
#endif

    String* ReturnData = malloc(sizeof(struct _String));

#if DEBUG()
    if (ReturnData == NULL) Fatal("Failed to malloc memory for String*");
#endif

    ReturnData->Content = malloc(size+1);

#if DEBUG()
    if (ReturnData->Content == NULL) Fatal("Failed to malloc memory for String->Content");
#endif

    memcpy(ReturnData->Content, content, size+1);

    ReturnData->Size = size;
    return ReturnData;
}

/**
 * @brief  Creates an empty string.
 * @retval An instance of String where Size = 0 and Content = nullptr.
 */
String* String_Empty(void)
{
    String* ReturnData = malloc(sizeof(struct _String));
#if DEBUG()
    if (ReturnData == NULL) Fatal("Failed to malloc memory for String*");
#endif
    ReturnData->Size = 0;
    return ReturnData;
}

/**
 * @brief  Opens a text file, reads all the content, closes the file and returns the content. Terminates program if text file contains non-ASCI characters.
 * @param  fileNameAndPath: The full name and path of the file to open. NULL is returned if the file could not be opened.
 * @retval A String-instance representing the contents of the file.
 */
String* File_ReadAllText(const char* fileNameAndPath)
{
    FILE *fileHandle = fopen(fileNameAndPath, "r");

    if (fileHandle == NULL) {
        puts("Unable to read all text from file");
        return NULL;
    }

    fseek(fileHandle, 0, SEEK_END);
    i64 FileSize = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    string FileContents = malloc(FileSize+1);
    i32 Index = 0;

#if DEBUG()
    if (FileContents == NULL) {
        Fatal("Error reading file contents. Cannot allocate memory");
    }
#endif

    while (1) {
        i32 NextChar = fgetc(fileHandle);
        if (NextChar == EOF) break;

        if ((NextChar & ~127) > 0)
        {
            char ErrorMessage[100];
            sprintf(ErrorMessage, "Index, %n, Char: %n", Index, NextChar);
            Fatal(strcat("Error reading all text from file as character was not a valid ASCI char: ", ErrorMessage));
        }

        FileContents[Index] = (char)NextChar;
        Index++;

        if (Index > STRING_MAX_SIZE)
        {
            Fatal("Text file content larger than max size string");
        }
    }

#if DEBUG()
    int CloseStatus = fclose(fileHandle);
    if (CloseStatus == -1) Fatal("Error closing file after reading");
#else
    fclose(fileHandle)
#endif

    if (Index == 0)
    {
        return String_Empty();
    }

    FileContents[Index] = '\0';
    u16 FinalSizeWithTerminator = (u16)Index + 1;

    if (FinalSizeWithTerminator > FileSize)
    {
        FileContents = realloc(FileContents, FinalSizeWithTerminator);
#if DEBUG()
        if (FileContents == NULL) {
            Fatal("Error reading text file contents. Cannot allocate memory");
            return NULL;
        }
#endif
    }

    String* ReturnData = String_Make(FileContents, FinalSizeWithTerminator-1);
    free(FileContents);

    return ReturnData;
}

StringArray* File_ReadAllLines(const char* fileNameAndPath)
{
    String* StringData = File_ReadAllText(fileNameAndPath);
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
        if (StringData->Content[Index] == '\n' || StringData->Content[Index] == EOF)
        {
            LineCount++;
        }
    }

    StringArray* ReturnData = malloc(sizeof(String) + sizeof(String*[LineCount]));
#if DEBUG()
    if (ReturnData == NULL) Fatal("Failed to allocate memory for StringArray return data in File_ReadAllLines");
#endif

    ReturnData->Count = LineCount;

    i32 StringStartIndex = 0;
    i32 StringLength = 0;

    // StringStartIndex = 0
    // Index   = 01234567
    // Content = ABCDEFG\n
    // ~~~~~~^6
    // From index 0 read 6 bytes
    for(i32 IndexOuter = 0; IndexOuter < LineCount; IndexOuter++)
    {
        for(i32 IndexInner = StringStartIndex; IndexInner <= StringData->Size; IndexInner++)
        {
            if (StringLength > STRING_MAX_SIZE)
            {
                Fatal("Text file content larger than max size string");
            }

            char CurrentChar = StringData->Content[IndexInner];
            if (CurrentChar == '\n' || CurrentChar == '\0')
            {
                break;
            }

            StringLength++;
        }

        if (StringLength == 0)
        {
            StringStartIndex++;
            StringLength = 0;
            continue;
        }

        char LocalString[StringLength+1];
        memcpy(LocalString, &StringData->Content[StringStartIndex], StringLength);
        LocalString[StringLength] = '\0';

        String* CurrentContentData = String_Make(LocalString, (u16)StringLength);
        ReturnData->Contents[IndexOuter] = CurrentContentData;

        StringStartIndex = StringStartIndex + StringLength + 1;
        StringLength = 0;
    }

    return ReturnData;
}
