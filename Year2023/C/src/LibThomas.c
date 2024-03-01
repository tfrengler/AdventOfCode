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
 * @brief  Checks whether a given input string contains a given string pattern. Case-sensitive.
 * @param  input: The input string to check
 * @param  pattern: The pattern you want to check if input contains.
 * @param  caseInsensitive: When 1 (true) then each charater for each string will be lower-cased before comparison, otherwise not.
 * @retval 1 if input starts with pattern, 0 otherwise.
 */
u8 String_Contains(const String* input, const String* pattern, u8 caseInsensitive)
{
#if DEBUG()
    if (input == NULL || pattern == NULL) Fatal("String_Contains: argument 'input' or 'pattern' is NULL");
    assert(caseInsensitive == 0 || caseInsensitive == 1);
#endif

    if (pattern->Size > input->Size) return 0;

    i32 PatternIndex = 0;
    i32 PatternIndexMax = pattern->Size - 1;
    i32 IndexMax = input->Size;

    for(i32 Index = 0; Index < IndexMax; Index++)
    {
        if (PatternIndex == 0 && pattern->Size > (input->Size - Index)) return 0;

        char InputChar = input->Content[Index];
        char PatternChar = pattern->Content[PatternIndex];

        if (caseInsensitive)
        {
            InputChar = (char)tolower(InputChar);
            PatternChar = (char)tolower(PatternChar);
        }

        if (InputChar == PatternChar)
        {
            PatternIndex++;
        }
        else
        {
            PatternIndex = 0;
        }

        if (PatternIndex > PatternIndexMax)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief  Checks whether a given input string ends with a given string pattern. Case-sensitive.
 * @param  input: The input string to check
 * @param  pattern: The pattern you want to check if input ends with.
 * @param  caseInsensitive: When 1 (true) then each charater for each string will be lower-cased before comparison, otherwise not.
 * @retval 1 if input starts with pattern, 0 otherwise.
 */
u8 String_EndsWith(const String* input, const String* pattern, u8 caseInsensitive)
{
#if DEBUG()
    if (input == NULL || pattern == NULL) Fatal("String_EndsWith: argument 'input' or 'pattern' is NULL");
    assert(caseInsensitive == 0 || caseInsensitive == 1);
#endif

    if (pattern->Size > input->Size) return 0;

    i32 InputIndex = input->Size - 1;
    for(i32 PatternIndex = (pattern->Size - 1); PatternIndex != 0; PatternIndex--, InputIndex--)
    {
        char CurrentInputChar = input->Content[InputIndex];
        char CurrentPatternChar = pattern->Content[PatternIndex];
        
        if (caseInsensitive)
        {
            CurrentInputChar = (char)tolower(CurrentInputChar);
            CurrentPatternChar = (char)tolower(CurrentPatternChar);
        }

        if (CurrentInputChar != CurrentPatternChar)
        {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief  Checks whether a given input string starts with a given string pattern. Case-sensitive.
 * @param  input: The input string to check
 * @param  pattern: The pattern you want to check if input starts with.
 * @param  caseInsensitive: When 1 (true) then each charater for each string will be lower-cased before comparison, otherwise not.
 * @retval 1 if input starts with pattern, 0 otherwise.
 */
u8 String_StartsWith(const String* input, const String* pattern, u8 caseInsensitive)
{
#if DEBUG()
    if (input == NULL || pattern == NULL) Fatal("String_StartsWith: argument 'input' or 'pattern' is NULL");
    assert(caseInsensitive == 0 || caseInsensitive == 1);
#endif

    if (pattern->Size > input->Size) return 0;

    for(i32 Index = 0; Index < pattern->Size; Index++)
    {
        char CurrentInputChar = input->Content[Index];
        char CurrentPatternChar = pattern->Content[Index];
        
        if (caseInsensitive)
        {
            CurrentInputChar = (char)tolower(CurrentInputChar);
            CurrentPatternChar = (char)tolower(CurrentPatternChar);
        }

        if (CurrentInputChar != CurrentPatternChar)
        {
            return 0;
        }
    }

    return 1;
}

/**
* @brief    Compares two instances of string structures to see if their contents are equal to each other.
* @param    original: The first string in the comparison.
* @param    compare: The second string that will be compared to the original.
* @param    caseInsensitive: When 1 (true) then each charater for each string will be lower-cased before comparison, otherwise not.
* @retval   Returns 1 if both strings are equal, 0 otherwise.
*/
u8 String_Equals(const String* original, const String* compare, u8 caseInsensitive)
{
#if DEBUG()
    if (original == NULL || compare == NULL) Fatal("String_Compare: argument 'original' or 'compare' is NULL");
    assert(caseInsensitive == 0 || caseInsensitive == 1);
#endif

    if (original->Size == 0 || compare->Size == 0) return 0;
    if (compare->Size != original->Size) return 0;

    i32 IndexLimit = original->Size;
    for(i32 Index = 0; Index < IndexLimit; Index++)
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
 * @brief  Creates a heap-allocated instance of String around a char*. The original string is copied so it is safe to free() afterwards.
 * @param  content: The string (including the null-terminator) to wrap the return struct around. Is mem-copied to retval->Content.
 * @param  size: The size of the string MINUS the null-terminator. Must be greater than 0 and content[size] is expected to be '\0'.
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
 * @brief  Creates a heao-allocated struct representing an empty string.
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
 * @brief  Opens a text file, reads all the content, parses it into lines (based on \n), closes the file and returns the content. Terminates program if text file contains non-ASCI characters.
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

/**
 * @brief   Opens a text file, reads all the content, closes the file and returns the content. Terminates program if text file contains non-ASCI characters.
 * @param   fileNameAndPath: The full name and path of the file to open. NULL is returned if the file could not be opened.
 * @retval  A StringArray representing all the lines of text in the text-file.
*/
StringArray* File_ReadAllLines(const char* fileNameAndPath)
{
    String* StringData = File_ReadAllText(fileNameAndPath);
    if (StringData == NULL) return NULL;

    if (StringData->Size == 0)
    {
        StringArray* ReturnData = malloc(sizeof *ReturnData);
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

    StringArray* ReturnData = malloc(sizeof *ReturnData + sizeof(String*[LineCount]));
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

    String_Free(StringData);
    return ReturnData;
}

/**
 * @brief   De-allocates (frees) a String-instance.
 * @param   input: The instance to free. Cannot be NULL.
 * @retval  None.
*/
void String_Free(String* input)
{
#if DEBUG()
    if (input == NULL) Fatal("String_Free: argument 'input' is NULL");
#endif

    free(input->Content);
    free(input);
}

/**
 * @brief   De-allocates (frees) a StringArray-instance.
 * @param   input: The instance to free. Cannot be NULL.
 * @retval  None.
*/
void StringArray_Free(StringArray* input)
{
#if DEBUG()
    if (input == NULL) Fatal("StringArray_Free: argument 'input' is NULL");
#endif

    for(i32 Index = 0; Index < input->Count; Index++)
    {
        String* Current = input->Contents[Index];
        String_Free(Current);
    }

    free(input);
}
