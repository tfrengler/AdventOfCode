#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <complex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limits.h"
#include "LibThomas.h"
#include "LibNumeric.h"

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

static bool i32Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int32_t *)number1Pointer > *(int32_t *)number2Pointer;
}

int32_t i32Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i32Data, input->Size, sizeof(input->i32Data[0]), &i32Max);
    return *(int32_t *)ReturnData;
}

static bool i32Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int32_t *)number1Pointer < *(int32_t *)number2Pointer;
}

int32_t i32Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i32Data, input->Size, sizeof(input->i32Data[0]), &i32Min);
    return *(int32_t *)ReturnData;
}

/* ********************** Unsigned 32-bit ********************/

static bool u32Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint32_t *)number1Pointer > *(uint32_t *)number2Pointer;
}

uint32_t u32Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u32Data, input->Size, sizeof(input->u32Data[0]), &u32Max);
    return *(uint32_t *)ReturnData;
}

static bool u32Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint32_t *)number1Pointer < *(uint32_t *)number2Pointer;
}

uint32_t u32Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u32Data, input->Size, sizeof(input->u32Data[0]), &u32Min);
    return *(uint32_t *)ReturnData;
}

/* ********************** Signed 64-bit ********************/

static bool i64Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int64_t *)number1Pointer > *(int64_t *)number2Pointer;
}

int64_t i64Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i64Data, input->Size, sizeof(input->i64Data[0]), &i64Max);
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

int64_t i64Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i64Data, input->Size, sizeof(input->i64Data[0]), &int64_t_Min);
    return *(int64_t *)ReturnData;
}

/* ********************** Unsigned 64-bit ********************/

static bool u64Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint64_t *)number1Pointer > *(uint64_t *)number2Pointer;
}

uint64_t u64Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u64Data, input->Size, sizeof(input->u64Data[0]), &u64Max);
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

uint64_t u64Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u64Data, input->Size, sizeof(input->u64Data[0]), &uint64_t_Min);
    return *(uint64_t *)ReturnData;
}

/* ********************** Signed 16-bit ********************/

static bool i16Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int16_t *)number1Pointer > *(int16_t *)number2Pointer;
}

int16_t i16Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u16Data, input->Size, sizeof(input->u16Data[0]), &i16Max);
    return *(int16_t *)ReturnData;
}

static bool i16Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int16_t *)number1Pointer < *(int16_t *)number2Pointer;
}

int16_t i16Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u16Data, input->Size, sizeof(input->u16Data[0]), &i16Min);
    return *(int16_t *)ReturnData;
}

/* ********************** Unsigned 16-bit ********************/

static bool u16Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint16_t *)number1Pointer > *(uint16_t *)number2Pointer;
}

uint16_t u16Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u16Data, input->Size, sizeof(input->u16Data[0]), &u16Max);
    return *(uint16_t *)ReturnData;
}

static bool u16Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int16_t *)number1Pointer < *(int16_t *)number2Pointer;
}

uint16_t u16Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u16Data, input->Size, sizeof(input->u16Data[0]), &u16Min);
    return *(uint16_t *)ReturnData;
}

/* ********************** Signed 8-bit ********************/

static bool i8Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int8_t *)number1Pointer > *(int8_t *)number2Pointer;
}

int8_t i8Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i8Data, input->Size, sizeof(input->i8Data[0]), &i8Max);
    return *(int8_t *)ReturnData;
}

static bool i8Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(int8_t *)number1Pointer < *(int8_t *)number2Pointer;
}

int8_t i8Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->i8Data, input->Size, sizeof(input->i8Data[0]), &i8Min);
    return *(int8_t *)ReturnData;
}

/* ********************** Unsigned 8-bit ********************/

static bool ui8Max(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint8_t *)number1Pointer > *(uint8_t *)number2Pointer;
}

uint8_t u8Array_Max(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u8Data, input->Size, sizeof(input->u8Data[0]), &ui8Max);
    return *(uint8_t *)ReturnData;
}

static bool ui8Min(const void *number1Pointer, const void *number2Pointer)
{
#if DEBUG()
    assert(number1Pointer != NULL);
    assert(number2Pointer != NULL);
#endif
    return *(uint8_t *)number1Pointer > *(uint8_t *)number2Pointer;
}

uint8_t u8Array_Min(const IntegerArray *input)
{
    const void *ReturnData = ArrayNumberCompare(input->u8Data, input->Size, sizeof(input->u8Data[0]), &ui8Min);
    return *(uint8_t *)ReturnData;
}

/* ********************** Numeric array functions ********************/

static IntegerArray *IntegerArray_Make(int32_t size, IntegerType type, const void *values)
{
    IntegerArray *ReturnData = Malloc(sizeof(*ReturnData));
#if DEBUG()
    assert(ReturnData != NULL);
#endif

    ReturnData->Size = size;
    ReturnData->Type = type;
    ReturnData->u8Data = 0;

    int32_t ElementSize = 0;
    void *DataDestination = 0;

    if (size == 0) {
        return ReturnData;
    }

    switch (type) {
        case U8:
            ReturnData->u8Data = Malloc(sizeof(uint8_t) * size);
            ElementSize = sizeof(uint8_t);
            DataDestination = ReturnData->u8Data;
            break;
        case I8:
            ReturnData->i8Data = Malloc(sizeof(int8_t) * size);
            ElementSize = sizeof(int8_t);
            DataDestination = ReturnData->i8Data;
            break;
        case U16:
            ReturnData->u16Data = Malloc(sizeof(uint16_t) * size);
            ElementSize = sizeof(uint16_t);
            DataDestination = ReturnData->u16Data;
            break;
        case I16:
            ReturnData->u16Data = Malloc(sizeof(int16_t) * size);
            ElementSize = sizeof(int16_t);
            DataDestination = ReturnData->u16Data;
            break;
        case U32:
            ReturnData->u32Data = Malloc(sizeof(uint32_t) * size);
            ElementSize = sizeof(uint32_t);
            DataDestination = ReturnData->u32Data;
            break;
        case I32:
            ReturnData->i32Data = Malloc(sizeof(int32_t) * size);
            ElementSize = sizeof(int32_t);
            DataDestination = ReturnData->i32Data;
            break;
        case U64:
            ReturnData->u64Data = Malloc(sizeof(uint64_t) * size);
            ElementSize = sizeof(uint64_t);
            DataDestination = ReturnData->u64Data;
            break;
        case I64:
            ReturnData->i64Data = Malloc(sizeof(int64_t) * size);
            ElementSize = sizeof(int64_t);
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
        if (input->u8Data != NULL) Free(input->u8Data);
        break;
    case I8:
        if (input->i8Data != NULL) Free(input->i8Data);
        break;
    case U16:
        if (input->u16Data != NULL) Free(input->u16Data);
        break;
    case I16:
        if (input->u16Data != NULL) Free(input->u16Data);
        break;
    case U32:
        if (input->u32Data != NULL) Free(input->u32Data);
        break;
    case I32:
        if (input->i32Data != NULL) Free(input->i32Data);
        break;
    case U64:
        if (input->u64Data != NULL) Free(input->u64Data);
        break;
    case I64:
        if (input->i64Data != NULL) Free(input->i64Data);
        break;
    }

    input->u8Data = 0;
    Free(input);
    input = 0;
}

IntegerArray *u8Array_Make(int32_t size, const uint8_t *values)
{
    return IntegerArray_Make(size, U8, values);
}

IntegerArray *i8Array_Make(int32_t size, const int8_t *values)
{
    return IntegerArray_Make(size, I8, values);
}

IntegerArray *u16Array_Make(int32_t size, const uint16_t *values)
{
    return IntegerArray_Make(size, U16, values);
}

IntegerArray *i16Array_Make(int32_t size, const int16_t *values)
{
    return IntegerArray_Make(size, I16, values);
}

IntegerArray *u32Array_Make(int32_t size, const uint32_t *values)
{
    return IntegerArray_Make(size, U32, values);
}

IntegerArray *i32Array_Make(int32_t size, const int32_t *values)
{
    return IntegerArray_Make(size, I32, values);
}

IntegerArray *u64Array_Make(int32_t size, const uint64_t *values)
{
    return IntegerArray_Make(size, U64, values);
}

IntegerArray *i64Array_Make(int32_t size, const int64_t *values)
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
 *
 * In all cases output will be 0 upon return EXCEPT if output is NULL (since that would be dereferencing a null pointer)
 */
bool StringToInt(const char *input, int32_t length, int32_t* output)
{
    if (output == NULL) {
        DEBUG_PRINT("StringToInt: output is null", NULL);
        return false;
    }

    *output = 0;

    if (input == NULL || length < 1) {
        DEBUG_PRINT("StringToInt: input is null and/or length is less than 1\n", NULL);
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

bool LongToInt(int64_t input, int32_t *output)
{
    *output = 0;
    
    if (input > INT_MAX || input < INT_MIN) {
        DEBUG_PRINT("Input over/under-flows int32: %zu", input);
        return false;
    }

    *output = (int32_t)input;
    return true;
}
