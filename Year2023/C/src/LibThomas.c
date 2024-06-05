#include "LibThomas.h"
#include <assert.h>
#include <complex.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief  Panics and terminates the program with EXIT_FAILURE, caused by an unrecoverable error.
 * @param  message: The message to print to perror.
 * @retval None
 */
void Fatal(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

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

    StringArray *ReturnData = malloc(sizeof *ReturnData + sizeof(String *[LineCount]));
#if DEBUG()
    assert(ReturnData != NULL);
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

        String *CurrentContentData = String_Make(LocalString, StringLength);
        ReturnData->Contents[IndexOuter] = CurrentContentData;

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
        input->Content = 0;
    }
    free(input);
    input = 0;
}

/**
 * @brief   De-allocates (frees) a StringArray-instance.
 * @param   input: The instance to free. Cannot be NULL.
 * @retval  None.
 */
void StringArray_Free(StringArray *input)
{
#if DEBUG()
    assert(input != NULL);
#endif

    for (int32_t Index = 0; Index < input->Count; Index++) {
        String *Current = input->Contents[Index];
#if DEBUG()
        assert(Current != NULL);
#endif
        String_Free(Current);
    }

    free(input);
    input = 0;
}

/* ***********************************************************
 * ********************** NUMBER FUNCTIONS ********************
 * ***********************************************************/

/**
 * @brief   Compares an array of numbers against one another.
 * @param   array       : Pointer to the start of the array.
 * @param   arraySize   : The amount of elements in the array.
 * @param   objectSize  : The size of the objects in the array.
 * @param   compare     : Pointer to a function that can compare two numbers, returning true when comparing p1 against p2.
 * @retval  A void pointer that can be cast to an integer type (uint8_t,int8_t,int16_t,uint16_t,int32_t,uint32_t,int64_t,uint64_t).
 */
static const void *ArrayNumberCompare(const void *array, int32_t arraySize, int32_t objectSize, bool (*compare)(const void *p1, const void *p2))
{
#if DEBUG()
    assert(array != NULL);
    assert(arraySize > 0);
    assert(objectSize > 0);
    assert(compare != NULL);
#endif

    const uint8_t *ByteArray = array;
    const void *ReturnData;

    if (compare(&ByteArray[0], &ByteArray[objectSize])) {
        ReturnData = &ByteArray[0];
    } else {
        ReturnData = &ByteArray[objectSize];
    }

    for (int32_t Index = 2; Index < arraySize; Index++) {
        if (compare(&ByteArray[Index * objectSize], ReturnData)) {
            ReturnData = &ByteArray[Index * objectSize];
        }
    }

    return ReturnData;
}

/* ********************** Signed 32-bit ********************/

static bool int32_t_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int32_t *)number1Pointer > *(int32_t *)number2Pointer;
}

int32_t int32_tArray_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->int32_tData, input->Size, sizeof(input->int32_tData[0]), &int32_t_Max);
    return *(int32_t *)ReturnData;
}

static bool int32_t_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int32_t *)number1Pointer < *(int32_t *)number2Pointer;
}

int32_t int32_tArray_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->int32_tData, input->Size, sizeof(input->int32_tData[0]), &int32_t_Min);
    return *(int32_t *)ReturnData;
}

/* ********************** Unsigned 32-bit ********************/

static bool uint32_t_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint32_t *)number1Pointer > *(uint32_t *)number2Pointer;
}

uint32_t uint32_tArray_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->uint32_tData, input->Size, sizeof(input->uint32_tData[0]), &uint32_t_Max);
    return *(uint32_t *)ReturnData;
}

static bool uint32_t_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint32_t *)number1Pointer < *(uint32_t *)number2Pointer;
}

uint32_t uint32_tArray_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->uint32_tData, input->Size, sizeof(input->uint32_tData[0]), &uint32_t_Min);
    return *(uint32_t *)ReturnData;
}

/* ********************** Signed 64-bit ********************/

static bool int64_t_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int64_t *)number1Pointer > *(int64_t *)number2Pointer;
}

int64_t int64_tArray_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->int64_tData, input->Size, sizeof(input->int64_tData[0]), &int64_t_Max);
    return *(int64_t *)ReturnData;
}

static bool int64_t_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int64_t *)number1Pointer < *(int64_t *)number2Pointer;
}

int64_t int64_tArray_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->int64_tData, input->Size, sizeof(input->int64_tData[0]), &int64_t_Min);
    return *(int64_t *)ReturnData;
}

/* ********************** Unsigned 64-bit ********************/

static bool uint64_t_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint64_t *)number1Pointer > *(uint64_t *)number2Pointer;
}

uint64_t uint64_tArray_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->uint64_tData, input->Size, sizeof(input->uint64_tData[0]), &uint64_t_Max);
    return *(uint64_t *)ReturnData;
}

static bool uint64_t_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint64_t *)number1Pointer < *(uint64_t *)number2Pointer;
}

uint64_t uint64_tArray_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->uint64_tData, input->Size, sizeof(input->uint64_tData[0]), &uint64_t_Min);
    return *(uint64_t *)ReturnData;
}

/* ********************** Signed 16-bit ********************/

static bool int16_t_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int16_t *)number1Pointer > *(int16_t *)number2Pointer;
}

int16_t int16_tArray_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->int16_tData, input->Size, sizeof(input->int16_tData[0]), &int16_t_Max);
    return *(int16_t *)ReturnData;
}

static bool int16_t_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int16_t *)number1Pointer < *(int16_t *)number2Pointer;
}

int16_t int16_tArray_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->int16_tData, input->Size, sizeof(input->int16_tData[0]), &int16_t_Min);
    return *(int16_t *)ReturnData;
}

/* ********************** Unsigned 16-bit ********************/

static bool uint16_t_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint16_t *)number1Pointer > *(uint16_t *)number2Pointer;
}

uint16_t uint16_tArray_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->uint16_tData, input->Size, sizeof(input->uint16_tData[0]), &uint16_t_Max);
    return *(uint16_t *)ReturnData;
}

static bool uint16_t_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int16_t *)number1Pointer < *(int16_t *)number2Pointer;
}

uint16_t uint16_tArray_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->uint16_tData, input->Size, sizeof(input->uint16_tData[0]), &uint16_t_Min);
    return *(uint16_t *)ReturnData;
}

/* ********************** Signed 8-bit ********************/

static bool int8_t_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int8_t *)number1Pointer > *(int8_t *)number2Pointer;
}

int8_t int8_tArray_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->int8_tData, input->Size, sizeof(input->int8_tData[0]), &int8_t_Max);
    return *(int8_t *)ReturnData;
}

static bool int8_t_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int8_t *)number1Pointer < *(int8_t *)number2Pointer;
}

int8_t int8_tArray_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->int8_tData, input->Size, sizeof(input->int8_tData[0]), &int8_t_Min);
    return *(int8_t *)ReturnData;
}

/* ********************** Unsigned 8-bit ********************/

static bool uint8_t_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint8_t *)number1Pointer > *(uint8_t *)number2Pointer;
}

uint8_t uint8_tArray_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->uint8_tData, input->Size, sizeof(input->uint8_tData[0]), &uint8_t_Max);
    return *(uint8_t *)ReturnData;
}

static bool uint8_t_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint8_t *)number1Pointer > *(uint8_t *)number2Pointer;
}

uint8_t uint8_tArray_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->uint8_tData, input->Size, sizeof(input->uint8_tData[0]), &uint8_t_Min);
    return *(uint8_t *)ReturnData;
}

/* ********************** Numeric array functions ********************/

static IntegerArray *IntegerArray_Make(int32_t size, IntegerType type, const void *values)
{
    IntegerArray *ReturnData = malloc(sizeof(*ReturnData));
#if DEBUG()
    assert(ReturnData != NULL);
#endif

    ReturnData->Size = size;
    ReturnData->Type = type;
    ReturnData->uint8_tData = 0;

    int32_t ElementSize = 0;
    void *DataDestination = 0;

    if (size == 0) {
        return ReturnData;
    }

    switch (type) {
        case U8:
            ReturnData->uint8_tData = malloc(sizeof(uint8_t) * size);
            ElementSize = sizeof(uint8_t);
            DataDestination = ReturnData->uint8_tData;
            break;
        case I8:
            ReturnData->int8_tData = malloc(sizeof(int8_t) * size);
            ElementSize = sizeof(int8_t);
            DataDestination = ReturnData->int8_tData;
            break;
        case U16:
            ReturnData->uint16_tData = malloc(sizeof(uint16_t) * size);
            ElementSize = sizeof(uint16_t);
            DataDestination = ReturnData->uint16_tData;
            break;
        case I16:
            ReturnData->int16_tData = malloc(sizeof(int16_t) * size);
            ElementSize = sizeof(int16_t);
            DataDestination = ReturnData->int16_tData;
            break;
        case U32:
            ReturnData->uint32_tData = malloc(sizeof(uint32_t) * size);
            ElementSize = sizeof(uint32_t);
            DataDestination = ReturnData->uint32_tData;
            break;
        case I32:
            ReturnData->int32_tData = malloc(sizeof(int32_t) * size);
            ElementSize = sizeof(int32_t);
            DataDestination = ReturnData->int32_tData;
            break;
        case U64:
            ReturnData->uint64_tData = malloc(sizeof(uint64_t) * size);
            ElementSize = sizeof(uint64_t);
            DataDestination = ReturnData->uint64_tData;
            break;
        case I64:
            ReturnData->int64_tData = malloc(sizeof(int64_t) * size);
            ElementSize = sizeof(int64_t);
            DataDestination = ReturnData->int64_tData;
            break;
    }

#if DEBUG()
    assert(DataDestination != NULL);
#endif

    if (values != NULL) {
        memcpy(DataDestination, values, size * ElementSize);
    }

    return ReturnData;
}

void IntegerArray_Free(IntegerArray *input)
{
#if DEBUG()
    assert(input != NULL);
#endif

    switch (input->Type) {
    case U8:
        if (input->uint8_tData != NULL) free(input->uint8_tData);
        break;
    case I8:
        if (input->int8_tData != NULL) free(input->int8_tData);
        break;
    case U16:
        if (input->uint16_tData != NULL) free(input->uint16_tData);
        break;
    case I16:
        if (input->int16_tData != NULL) free(input->int16_tData);
        break;
    case U32:
        if (input->uint32_tData != NULL) free(input->uint32_tData);
        break;
    case I32:
        if (input->int32_tData != NULL) free(input->int32_tData);
        break;
    case U64:
        if (input->uint64_tData != NULL) free(input->uint64_tData);
        break;
    case I64:
        if (input->int64_tData != NULL) free(input->int64_tData);
        break;
    }

    input->uint8_tData = 0;
    free(input);
    input = 0;
}

IntegerArray *uint8_tArray_Make(int32_t size, const uint8_t *values)
{
    return IntegerArray_Make(size, U8, values);
}

IntegerArray *int8_tArray_Make(int32_t size, const int8_t *values)
{
    return IntegerArray_Make(size, I8, values);
}

IntegerArray *uint16_tArray_Make(int32_t size, const uint16_t *values)
{
    return IntegerArray_Make(size, U16, values);
}

IntegerArray *int16_tArray_Make(int32_t size, const int16_t *values)
{
    return IntegerArray_Make(size, I16, values);
}

IntegerArray *uint32_tArray_Make(int32_t size, const uint32_t *values)
{
    return IntegerArray_Make(size, U32, values);
}

IntegerArray *int32_tArray_Make(int32_t size, const int32_t *values)
{
    return IntegerArray_Make(size, I32, values);
}

IntegerArray *uint64_tArray_Make(int32_t size, const uint64_t *values)
{
    return IntegerArray_Make(size, U64, values);
}

IntegerArray *int64_tArray_Make(int32_t size, const int64_t *values)
{
    return IntegerArray_Make(size, I64, values);
}

/**
 * @brief   Converts numbers founds in strings to 32-bit integers. Ignores leading whitespace, and will convert a sequence of contigous digits to an int until a non-digit character is found or until length is reached.
            Leading zeroes before the first number sequence - or between the negative sign and the first digit - are counted as non-digits.
            Examples:
            - "0123", "a123", "-0123", "0-123" returns true with output = 0
            - "123x4", "123 4". "123" or "  123" returns true with output = 123
            - "-456x7", "-456 7". "-456" or "  -456" returns true with output = -456
            - "2147483648" and "-2147483649" returns false with output = 0 (int under/overflow by calculation)
            - "21474836471" and "-21474836481" returns false with output = 0 (max int overflow by too many contigous digits)
 * @param  *input: The string with potential numbers in them you want to parse. Not allowed to be NULL or false is returned.
 * @param  length: The max amount of characters to process in the input. Typically the length of input (minus null terminator) but can be less. Must be at least 1 or false is returned.
 * @param  output: A pointer to an int where the parsed number will be stored in. Will be initialized to 0. Must not be NULL or false is returned.
 * @retval True if parsing succeeded, or false if parsing failed due to an error. True does not mean a number was found, just that no errors happened. False can mean multiple things:
 * - input or output was NULL
 * - length was was less than 1
 * - a number was found but it under- or overflowed the max value of a 32-bit int
 * - a null terminator character was found in input before length was reached
 * In all cases output will be 0 upon return EXCEPT if output is NULL (since that would be dereferencing a null pointer)
 */
bool StringToInt(const char *input, int32_t length, int* output)
{
    if (output == NULL) {
        DEBUG_PRINT("StringToInt: output is null", NULL);
        return false;
    }

    *output = 0;

    if (input == NULL || length < 1) {
        DEBUG_PRINT("StringToInt: input is null and/or length is less than 0\n", NULL);
        return false;
    }

    bool IsNegative = false;
    char NextCharacter;
    int32_t InputIndex = 0;

    // Pre-process until we find the first number or a negative sign
    while (InputIndex < length) {
        NextCharacter = input[InputIndex];

        // Detect end of string regardless of length param
        if (NextCharacter == '\0') {
            DEBUG_PRINT("StringToInt: premature null terminator found in input (1)\n", NULL);
            return false;
        }
        // Ignore leading whitespace
        if ((NextCharacter < 14 && NextCharacter > 9) || NextCharacter == 32) {
            InputIndex++;
            continue;
        }
        // Break, because we have non-whitespace chars
        break;
    }

    // Is the non-whitespace char a sign?
    if (NextCharacter == '-') {
        // If not at end of input as defined by length, peek and determine if we have leading zeroes after negative sign
        if (InputIndex < length && input[InputIndex + 1] == '0') {
            return true;
        }
        // Otherwise flag it and continue
        IsNegative = true;
        InputIndex++;
    }

    if (NextCharacter == '0') {
        return true;
    }

    int32_t Digits = 0;

    while (InputIndex < length) {
        NextCharacter = input[InputIndex];

        // Not a number anymore? Break, and return the number we have parsed so far...
        if (NextCharacter < '0' || NextCharacter > '9') {
            // ...unless it's a null terminator in which cases length is longer than input which is bad
            if (NextCharacter == '\0') {
                DEBUG_PRINT("StringToInt: premature null terminator found in input (2)\n", NULL);
                *output = 0;
                return false;
            }
            break;
        }

        Digits++;
        // Overflow, we now have 11 digits and there's 10 in the max or min int value OR we have a null terminator
        if (Digits > 10) {
            DEBUG_PRINT("StringToInt: max/min int over flow (11 digits)\n", NULL);
            *output = 0;
            return false;
        }

        *output *= 10; // Advance to next decimal
        int32_t NextNumber = NextCharacter - '0'; // Convert char to int

        // Deal with potential over- or underflow of max/min int value
        if (Digits == 10) {
            int32_t ValueSoFar = *output;
            int32_t MaxBeforeOverflow;

            if (IsNegative) {
                MaxBeforeOverflow = (INT_MIN - ValueSoFar) * -1;
            } else {
                MaxBeforeOverflow = INT_MAX - ValueSoFar;
            }

            if (NextNumber > MaxBeforeOverflow) {
                DEBUG_PRINT("StringToInt: max/min int overflow (calculation)\n", NULL);
                *output = 0;
                return false;
            }
        }

        if (IsNegative) {
            *output -= NextNumber;
        } else {
            *output += NextNumber;
        }

        InputIndex++;
    }

    return true;
}
