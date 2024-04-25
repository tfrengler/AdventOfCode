#include "LibThomas.h"
#include "errno.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
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
    if (errno == 0) errno = EBADMSG;
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

    i32 PatternIndex = 0;
    i32 PatternIndexMax = pattern->Size - 1;
    i32 IndexMax = input->Size;

    for (i32 Index = 0; Index < IndexMax; Index++) {
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

    i32 InputIndex = input->Size - 1;
    for (i32 PatternIndex = (pattern->Size - 1); PatternIndex != 0; PatternIndex--, InputIndex--) {
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

    for (i32 Index = 0; Index < pattern->Size; Index++) {
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

    i32 IndexLimit = original->Size;
    for (i32 Index = 0; Index < IndexLimit; Index++) {
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
String *String_Make(const char *content, u16 size)
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

    u16 SubStringStart = 0;
    u16 SubStringEnd = input->Size - 1;

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

    u16 StringSize = (SubStringEnd - SubStringStart) + 1;
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

    i32 LineCount = 1;
    i32 SearchEndIndex = inputString->Size - 1;

    for (i32 Index = 1; Index < SearchEndIndex; Index++) {
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

    i32 StringStartIndex = 0;
    u16 StringLength = 0;

    if (inputString->Content[0] == delimiter) {
        StringStartIndex++;
    }

    for (i32 IndexOuter = 0; IndexOuter < LineCount; IndexOuter++) {
        for (i32 IndexInner = StringStartIndex; IndexInner <= inputString->Size; IndexInner++) {
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
    i64 FileSize = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    char *FileContents = malloc(FileSize + 1);
    i32 Index = 0;

#if DEBUG()
    assert(FileContents != NULL);
#endif

    while (1) {
        i32 NextChar = fgetc(fileHandle);
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
    u16 FinalSizeWithTerminator = (u16)Index + 1;

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

    for (i32 Index = 0; Index < input->Count; Index++) {
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
 * @retval  A void pointer that can be cast to an integer type (u8,i8,i16,u16,i32,u32,i64,u64).
 */
static const void *ArrayNumberCompare(const void *array, size_t arraySize, size_t objectSize, bool (*compare)(const void *p1, const void *p2))
{
#if DEBUG()
    assert(array != NULL);
    assert(arraySize > 0);
    assert(objectSize > 0);
    assert(compare != NULL);
#endif

    const u8 *ByteArray = array;
    const void *ReturnData;

    if (compare(&ByteArray[0], &ByteArray[objectSize])) {
        ReturnData = &ByteArray[0];
    } else {
        ReturnData = &ByteArray[objectSize];
    }

    for (size_t Index = 2; Index < arraySize; Index++) {
        if (compare(&ByteArray[Index * objectSize], ReturnData)) {
            ReturnData = &ByteArray[Index * objectSize];
        }
    }

    return ReturnData;
}

/* ********************** Signed 32-bit ********************/

static bool i32_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(i32 *)number1Pointer > *(i32 *)number2Pointer;
}

i32 i32Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i32Data, input->Size, sizeof(input->i32Data[0]), &i32_Max);
    return *(i32 *)ReturnData;
}

static bool i32_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(i32 *)number1Pointer < *(i32 *)number2Pointer;
}

i32 i32Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i32Data, input->Size, sizeof(input->i32Data[0]), &i32_Min);
    return *(i32 *)ReturnData;
}

/* ********************** Unsigned 32-bit ********************/

static bool u32_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(u32 *)number1Pointer > *(u32 *)number2Pointer;
}

u32 u32Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u32Data, input->Size, sizeof(input->u32Data[0]), &u32_Max);
    return *(u32 *)ReturnData;
}

static bool u32_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(u32 *)number1Pointer < *(u32 *)number2Pointer;
}

u32 u32Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u32Data, input->Size, sizeof(input->u32Data[0]), &u32_Min);
    return *(u32 *)ReturnData;
}

/* ********************** Signed 64-bit ********************/

static bool i64_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(i64 *)number1Pointer > *(i64 *)number2Pointer;
}

i64 i64Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i64Data, input->Size, sizeof(input->i64Data[0]), &i64_Max);
    return *(i64 *)ReturnData;
}

static bool i64_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(i64 *)number1Pointer < *(i64 *)number2Pointer;
}

i64 i64Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i64Data, input->Size, sizeof(input->i64Data[0]), &i64_Min);
    return *(i64 *)ReturnData;
}

/* ********************** Unsigned 64-bit ********************/

static bool u64_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(u64 *)number1Pointer > *(u64 *)number2Pointer;
}

u64 u64Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u64Data, input->Size, sizeof(input->u64Data[0]), &u64_Max);
    return *(u64 *)ReturnData;
}

static bool u64_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(u64 *)number1Pointer < *(u64 *)number2Pointer;
}

u64 u64Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u64Data, input->Size, sizeof(input->u64Data[0]), &u64_Min);
    return *(u64 *)ReturnData;
}

/* ********************** Signed 16-bit ********************/

static bool i16_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(i16 *)number1Pointer > *(i16 *)number2Pointer;
}

i16 i16Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i16Data, input->Size, sizeof(input->i16Data[0]), &i16_Max);
    return *(i16 *)ReturnData;
}

static bool i16_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(i16 *)number1Pointer < *(i16 *)number2Pointer;
}

i16 i16Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i16Data, input->Size, sizeof(input->i16Data[0]), &i16_Min);
    return *(i16 *)ReturnData;
}

/* ********************** Unsigned 16-bit ********************/

static bool u16_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(u16 *)number1Pointer > *(u16 *)number2Pointer;
}

u16 u16Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u16Data, input->Size, sizeof(input->u16Data[0]), &u16_Max);
    return *(u16 *)ReturnData;
}

static bool u16_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(i16 *)number1Pointer < *(i16 *)number2Pointer;
}

u16 u16Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u16Data, input->Size, sizeof(input->u16Data[0]), &u16_Min);
    return *(u16 *)ReturnData;
}

/* ********************** Signed 8-bit ********************/

static bool i8_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(i8 *)number1Pointer > *(i8 *)number2Pointer;
}

i8 i8Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i8Data, input->Size, sizeof(input->i8Data[0]), &i8_Max);
    return *(i8 *)ReturnData;
}

static bool i8_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(i8 *)number1Pointer < *(i8 *)number2Pointer;
}

i8 i8Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i8Data, input->Size, sizeof(input->i8Data[0]), &i8_Min);
    return *(i8 *)ReturnData;
}

/* ********************** Unsigned 8-bit ********************/

static bool u8_Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(u8 *)number1Pointer > *(u8 *)number2Pointer;
}

u8 u8Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u8Data, input->Size, sizeof(input->u8Data[0]), &u8_Max);
    return *(u8 *)ReturnData;
}

static bool u8_Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(u8 *)number1Pointer > *(u8 *)number2Pointer;
}

u8 u8Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u8Data, input->Size, sizeof(input->u8Data[0]), &u8_Min);
    return *(u8 *)ReturnData;
}

/* ********************** Numeric array functions ********************/

static IntegerArray *IntegerArray_Make(size_t size, IntegerType type, const void *values)
{
    IntegerArray *ReturnData = malloc(sizeof(*ReturnData));
#if DEBUG()
    assert(ReturnData != NULL);
#endif

    ReturnData->Size = size;
    ReturnData->Type = type;
    ReturnData->u8Data = 0;

    size_t ElementSize = 0;
    void *DataDestination = 0;

    if (size == 0) {
        return ReturnData;
    }

    switch (type) {
    case U8:
        ReturnData->u8Data = malloc(sizeof(u8) * size);
        ElementSize = sizeof(u8);
        DataDestination = ReturnData->u8Data;
        break;
    case I8:
        ReturnData->i8Data = malloc(sizeof(i8) * size);
        ElementSize = sizeof(i8);
        DataDestination = ReturnData->i8Data;
        break;
    case U16:
        ReturnData->u16Data = malloc(sizeof(u16) * size);
        ElementSize = sizeof(u16);
        DataDestination = ReturnData->u16Data;
        break;
    case I16:
        ReturnData->i16Data = malloc(sizeof(i16) * size);
        ElementSize = sizeof(i16);
        DataDestination = ReturnData->i16Data;
        break;
    case U32:
        ReturnData->u32Data = malloc(sizeof(u32) * size);
        ElementSize = sizeof(u32);
        DataDestination = ReturnData->u32Data;
        break;
    case I32:
        ReturnData->i32Data = malloc(sizeof(i32) * size);
        ElementSize = sizeof(i32);
        DataDestination = ReturnData->i32Data;
        break;
    case U64:
        ReturnData->u64Data = malloc(sizeof(u64) * size);
        ElementSize = sizeof(u64);
        DataDestination = ReturnData->u64Data;
        break;
    case I64:
        ReturnData->i64Data = malloc(sizeof(i64) * size);
        ElementSize = sizeof(i64);
        DataDestination = ReturnData->i64Data;
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
        if (input->u8Data != NULL) free(input->u8Data);
        break;
    case I8:
        if (input->i8Data != NULL) free(input->i8Data);
        break;
    case U16:
        if (input->u16Data != NULL) free(input->u16Data);
        break;
    case I16:
        if (input->i16Data != NULL) free(input->i16Data);
        break;
    case U32:
        if (input->u32Data != NULL) free(input->u32Data);
        break;
    case I32:
        if (input->i32Data != NULL) free(input->i32Data);
        break;
    case U64:
        if (input->u64Data != NULL) free(input->u64Data);
        break;
    case I64:
        if (input->i64Data != NULL) free(input->i64Data);
        break;
    }

    input->u8Data = 0;
    free(input);
    input = 0;
}

IntegerArray *u8Array_Make(size_t size, const u8 *values)
{
    return IntegerArray_Make(size, U8, values);
}

IntegerArray *i8Array_Make(size_t size, const i8 *values)
{
    return IntegerArray_Make(size, I8, values);
}

IntegerArray *u16Array_Make(size_t size, const u16 *values)
{
    return IntegerArray_Make(size, U16, values);
}

IntegerArray *i16Array_Make(size_t size, const i16 *values)
{
    return IntegerArray_Make(size, I16, values);
}

IntegerArray *u32Array_Make(size_t size, const u32 *values)
{
    return IntegerArray_Make(size, U32, values);
}

IntegerArray *i32Array_Make(size_t size, const i32 *values)
{
    return IntegerArray_Make(size, I32, values);
}

IntegerArray *u64Array_Make(size_t size, const u64 *values)
{
    return IntegerArray_Make(size, U64, values);
}

IntegerArray *i64Array_Make(size_t size, const i64 *values)
{
    return IntegerArray_Make(size, I64, values);
}
