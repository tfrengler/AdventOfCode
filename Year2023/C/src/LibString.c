#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <complex.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibThomas.h"
#include "LibString.h"

/* ***********************************************************
 * ********************** STRING FUNCTIONS ********************
 * ***********************************************************/

/**
 * @brief  Checks whether a given input string contains a given string pattern. Case-sensitive.
 * @param  input: The input string to check
 * @param  pattern: The pattern you want to check if input contains.
 * @param  caseInsensitive: When 1 (true) then each charater for each string will be lower-cased before comparison, otherwise not.
 * @retval True if input contains pattern, false otherwise.
 */
bool String_Contains(const String *input, const String *pattern, bool caseInsensitive)
{
#if DEBUG()
    if (input == NULL || pattern == NULL) Fatal("String_Contains: argument 'input' or 'pattern' is NULL");
    assert(caseInsensitive == false || caseInsensitive == true);
#endif

    if (pattern->Size > input->Size) return false;

    int64_t PatternIndex = 0;
    int64_t PatternIndexMax = pattern->Size - 1;
    int32_t IndexMax = input->Size;

    for (int32_t Index = 0; Index < IndexMax; Index++) {
        if (PatternIndex == 0 && pattern->Size > (input->Size - Index)) return false;

        char InputChar = input->Content[Index];
        char PatternChar = pattern->Content[PatternIndex];

        if (caseInsensitive) {
            InputChar = (char)tolower(InputChar);
            PatternChar = (char)tolower(PatternChar);
        }

        if (InputChar == PatternChar) {
            PatternIndex++;
        } else {
            PatternIndex = false;
        }

        if (PatternIndex > PatternIndexMax) {
            return true;
        }
    }

    return false;
}

/**
 * @brief  Checks whether a given input string ends with a given string pattern. Case-sensitive.
 * @param  input: The input string to check
 * @param  pattern: The pattern you want to check if input ends with.
 * @param  caseInsensitive: When 1 (true) then each charater for each string will be lower-cased before comparison, otherwise not.
 * @retval True if input ends with pattern, false otherwise.
 */
bool String_EndsWith(const String *input, const String *pattern, bool caseInsensitive)
{
#if DEBUG()
    if (input == NULL || pattern == NULL) Fatal("String_EndsWith: argument 'input' or 'pattern' is NULL");
    assert(caseInsensitive == false || caseInsensitive == true);
#endif

    if (pattern->Size > input->Size) return false;

    int64_t InputIndex = input->Size - 1;
    for (int32_t PatternIndex = (pattern->Size - 1); PatternIndex != 0; PatternIndex--, InputIndex--) {
        char CurrentInputChar = input->Content[InputIndex];
        char CurrentPatternChar = pattern->Content[PatternIndex];

        if (caseInsensitive) {
            CurrentInputChar = (char)tolower(CurrentInputChar);
            CurrentPatternChar = (char)tolower(CurrentPatternChar);
        }

        if (CurrentInputChar != CurrentPatternChar) {
            return false;
        }
    }

    return true;
}

/**
 * @brief  Checks whether a given input string starts with a given string pattern. Case-sensitive.
 * @param  input: The input string to check
 * @param  pattern: The pattern you want to check if input starts with.
 * @param  caseInsensitive: When 1 (true) then each charater for each string will be lower-cased before comparison, otherwise not.
 * @retval True if input starts with pattern, false otherwise.
 */
bool String_StartsWith(const String *input, const String *pattern, bool caseInsensitive)
{
#if DEBUG()
    assert(input != NULL);
    assert(pattern != NULL);
    assert(caseInsensitive == false || caseInsensitive == true);
#endif

    if (pattern->Size > input->Size) return false;

    for (int32_t Index = 0; Index < pattern->Size; Index++) {
        char CurrentInputChar = input->Content[Index];
        char CurrentPatternChar = pattern->Content[Index];

        if (caseInsensitive) {
            CurrentInputChar = (char)tolower(CurrentInputChar);
            CurrentPatternChar = (char)tolower(CurrentPatternChar);
        }

        if (CurrentInputChar != CurrentPatternChar) {
            return false;
        }
    }

    return true;
}

/**
 * @brief    Compares two instances of string structures to see if their contents are equal to each other.
 * @param    original: The first string in the comparison.
 * @param    compare: The second string that will be compared to the original.
 * @param    caseInsensitive: When 1 (true) then each charater for each string will be lower-cased before comparison, otherwise not.
 * @retval   Returns 1 if both strings are equal, 0 otherwise.
 */
bool String_Equals(const String *original, const String *compare, bool caseInsensitive)
{
#if DEBUG()
    assert(original != NULL);
    assert(compare != NULL);
    assert(caseInsensitive == false || caseInsensitive == true);
#endif

    if (original->Size == 0 || compare->Size == 0) return false;
    if (compare->Size != original->Size) return false;

    int32_t IndexLimit = original->Size;
    for (int32_t Index = 0; Index < IndexLimit; Index++) {
        char CurrentOriginalChar = original->Content[Index];
        char CurrentCompareChar = compare->Content[Index];

        if (caseInsensitive) {
            CurrentOriginalChar = (char)tolower(CurrentOriginalChar);
            CurrentCompareChar = (char)tolower(CurrentCompareChar);
        }

        if (CurrentOriginalChar != CurrentCompareChar) {
            return false;
        }
    }

    return true;
}

/**
 * @brief  Creates a heap-allocated instance of String around a char*. The original string is copied so it is safe to free() afterwards.
 * @param  content: The string (including the null-terminator) to wrap the return struct around. Is mem-copied to retval->Content.
 * @param  size: The size of the string MINUS the null-terminator. Must be greater than 0 and content[size] is expected to be '\0'.
 * @retval A pointer to the newly created String wrapped around the C-string.
 */
String *String_Make(const char *content, int32_t size)
{
#if DEBUG()
    assert(content != NULL);
    assert(size > 0);
    assert(content[size] == '\0');
#endif

    String *ReturnData = malloc(sizeof(struct _String));

#if DEBUG()
    assert(ReturnData != NULL);
#endif

    ReturnData->Content = malloc(size + 1);

#if DEBUG()
    assert(ReturnData->Content != NULL);
#endif

    memcpy(ReturnData->Content, content, size + 1);

    ReturnData->Size = size;
    return ReturnData;
}

/**
 * @brief  Creates a heap-allocated struct representing an empty string.
 * @retval An instance of String where Size = 0 and Content = nullptr.
 */
String *String_Empty(void)
{
    String *ReturnData = malloc(sizeof(struct _String));
#if DEBUG()
    assert(ReturnData != NULL);
#endif
    ReturnData->Size = 0;
    return ReturnData;
}

/**
 * @brief  Trims a string and returns a copy with leading and trailing whitespace removed.
 * @param  input: The string to trim of whitespace.
 * @retval Pointer to a copy of input with whitespace trimmed, or if the string is empty (size == 0) the original instance is returned instead.
 */
String *String_Trim(const String *input)
{
#if DEBUG()
    assert(input != NULL);
#endif

    if (input->Size == 0) {
        return (String*)input;
    }

    int32_t SubStringStart = 0;
    int32_t SubStringEnd = input->Size - 1;

    char NextChar = input->Content[0];
    while (isspace(NextChar)) {
        SubStringStart++;
        if (SubStringStart > SubStringEnd) {
            return String_Empty();
        }
        NextChar = input->Content[SubStringStart];
    }

    NextChar = input->Content[SubStringEnd];
    while (isspace(NextChar)) {
        SubStringEnd--;
        NextChar = input->Content[SubStringEnd];
    }

    int32_t StringSize = (SubStringEnd - SubStringStart) + 1;
    char LocalSubStringCopy[StringSize + 1];

    memcpy(LocalSubStringCopy, &input->Content[SubStringStart], StringSize);
    LocalSubStringCopy[StringSize] = '\0';

    String *ReturnData = String_Make(LocalSubStringCopy, StringSize);
    return ReturnData;
}

/**
 * @brief  Parses a string and splits it into an array of strings based on a delimiter.
 * @param   inputString: The string to split into other strings.
 * @param   delimiter: The character to split the string on which is omitted from the strings after the split. Not allowed to be a null-character.
 * @retval  A StringArray representing all the lines of text split by - but not including - the delimiter. If input->Size is 0 then NULL is returned.
 */
StringArray *String_Split(const String *inputString, char delimiter)
{
#if DEBUG()
    assert(inputString != NULL);
    assert(delimiter != '\0');
#endif

    if (inputString->Size == 0) {
        return NULL;
    }

    int32_t LineCount = 1;
    int32_t SearchEndIndex = inputString->Size - 1;

    for (int32_t Index = 1; Index < SearchEndIndex; Index++) {
        if (inputString->Content[Index] == delimiter) {
            LineCount++;
        }
    }

    StringArray *ReturnData = malloc(sizeof *ReturnData);
#if DEBUG()
    assert(ReturnData != NULL);
#endif
    ReturnData->Contents = malloc(sizeof(**ReturnData->Contents) * LineCount);
#if DEBUG()
    assert(ReturnData->Contents != NULL);
#endif

    ReturnData->Count = LineCount;

    if (LineCount == 1) {
        ReturnData->Contents[0] = String_Make(inputString->Content, inputString->Size);
        return ReturnData;
    }

    int32_t StringStartIndex = 0;
    uint16_t StringLength = 0;

    if (inputString->Content[0] == delimiter) {
        StringStartIndex++;
    }

    for (int32_t IndexOuter = 0; IndexOuter < LineCount; IndexOuter++) {
        for (int32_t IndexInner = StringStartIndex; IndexInner <= inputString->Size; IndexInner++) {
            if (StringLength > STRING_MAX_SIZE) {
                Fatal("Text file content larger than max size string");
            }

            char CurrentChar = inputString->Content[IndexInner];
            if (CurrentChar == delimiter || CurrentChar == '\0') {
                break;
            }

            StringLength++;
        }

        if (StringLength == 0) {
            StringStartIndex++;
            StringLength = 0;
            continue;
        }

        char LocalString[StringLength + 1];
        memcpy(LocalString, &inputString->Content[StringStartIndex], StringLength);
        LocalString[StringLength] = '\0';

        ReturnData->Contents[IndexOuter] = String_Make(LocalString, StringLength);

        StringStartIndex = StringStartIndex + StringLength + 1;
        StringLength = 0;
    }

    return ReturnData;
}

/**
 * @brief  Opens a text file, reads all the content, closes the file and returns the content. Terminates program if text file contains non-ASCI characters.
 * @param  fileNameAndPath: The full name and path of the file to open. NULL is returned if the file could not be opened.
 * @retval A String-instance representing the contents of the file.
 */
String *File_ReadAllText(const char *fileNameAndPath)
{
    FILE *fileHandle = fopen(fileNameAndPath, "r");

    if (fileHandle == NULL) {
        puts("Unable to read all text from file");
        return NULL;
    }

    fseek(fileHandle, 0, SEEK_END);
    int64_t FileSize = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    char *FileContents = malloc(FileSize + 1);
    int32_t Index = 0;

#if DEBUG()
    assert(FileContents != NULL);
#endif

    while (1) {
        int32_t NextChar = fgetc(fileHandle);
        if (NextChar == EOF) break;

        if ((NextChar & ~127) > 0) {
            char ErrorMessage[100];
            sprintf(ErrorMessage, "Index, %i, Char: %i", Index, NextChar);
            Fatal(strcat("Error reading all text from file as character was not a valid ASCI char: ", ErrorMessage));
        }

        FileContents[Index] = (char)NextChar;
        Index++;

        if (Index > STRING_MAX_SIZE) {
            Fatal("Text file content larger than max size string");
        }
    }

#if DEBUG()
    int CloseStatus = fclose(fileHandle);
    if (CloseStatus == -1) Fatal("Error closing file after reading");
#else
    fclose(fileHandle)
#endif

    if (Index == 0) {
        return String_Empty();
    }

    FileContents[Index] = '\0';
    uint16_t FinalSizeWithTerminator = (uint16_t)Index + 1;

    if (FinalSizeWithTerminator > FileSize) {
        FileContents = realloc(FileContents, FinalSizeWithTerminator);
#if DEBUG()
        if (FileContents == NULL) {
            Fatal("Error reading text file contents. Cannot allocate memory");
            return NULL;
        }
#endif
    }

    String *ReturnData = String_Make(FileContents, FinalSizeWithTerminator - 1);
    free(FileContents);
    FileContents = 0;

    return ReturnData;
}

StringArray *StringArray_Make(String *contents, const int32_t size)
{
    if (contents == 0x0 || size < 1) {
        Fatal("Error making string array. Contents were NULL or size was less than 1");
    }

    StringArray *ReturnData = malloc(sizeof(StringArray));
#if DEBUG()
    assert(ReturnData != 0x0);
#endif
    ReturnData->Contents = malloc(size * sizeof(String));
#if DEBUG()
    assert(ReturnData->Contents != 0x0);
#endif

    ReturnData->Count = size;
    ReturnData->Contents = &contents;

    return ReturnData;
}

/**
 * @brief  Opens a text file, reads all the content, parses it into lines (based on \n), closes the file and returns the content. Terminates program if text file contains non-ASCI characters.
 * @param   fileNameAndPath: The full name and path of the file to open. NULL is returned if the file could not be opened.
 * @retval  A StringArray representing all the lines of text in the text-file.
 */
StringArray *File_ReadAllLines(const char *fileNameAndPath)
{
    String *StringData = File_ReadAllText(fileNameAndPath);
    if (StringData == NULL) return NULL;

    StringArray *ReturnData = String_Split(StringData, '\n');
    String_Free(StringData);

    return ReturnData;
}

/**
 * @brief   De-allocates (frees) a String-instance.
 * @param   input: The instance to free. Cannot be NULL.
 * @retval  None.
 */
void String_Free(String *input)
{
#if DEBUG()
    assert(input != NULL);
#endif

    if (input->Content != NULL) {
        free(input->Content);
        input->Content = 0x0;
    }
    free(input);
    input = 0x0;
}

/**
 * @brief   De-allocates (frees) a StringArray-instance.
 * @param   input: The instance to free. Cannot be NULL.
 * @retval  None.
 */
void StringArray_Free(StringArray *input, bool freeContent)
{
#if DEBUG()
    assert(input != NULL);
    assert(input->Contents != NULL);
#endif
    
    if (freeContent) {
        for (int32_t Index = 2; Index < input->Count; Index++) {
            String *Current = input->Contents[Index];
#if DEBUG()
        assert(Current != NULL);
#endif
            String_Free(Current);
        }
        free(input->Contents);
    }

    free(input);
    input = 0x0;
}
