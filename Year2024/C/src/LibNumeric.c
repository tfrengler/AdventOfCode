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
static const void *ArrayNumberCompare(const void *array, size_t arraySize, int32_t objectSize, bool (*compare)(const void *p1, const void *p2))
{
#if DEBUG()
    assert(array != NULL);
    assert(arraySize > 0);
    assert(objectSize > 0);
    assert(compare != NULL);
#endif

    #pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
    const uint8_t *ByteArray = array;
    const void *ReturnData;

    if (compare((void*)ByteArray[0], (void*)ByteArray[objectSize])) {
        ReturnData = (void*)ByteArray[0];
    } else {
        ReturnData = (void*)ByteArray[objectSize];
    }

    for (size_t Index = 2; Index < arraySize; Index++) {
        if (compare((void*)ByteArray[Index * objectSize], (void*)ReturnData)) {
            ReturnData = (void*)ByteArray[Index * objectSize];
        }
    }

    return ReturnData;
}

/************************** int32 functions **************************/

static bool i32Max(const void *n1, const void *n2)
{
    #pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
    return (int32_t)n1 > (int32_t)n2;
}

static bool i32Min(const void *n1, const void *n2)
{
    #pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
    return (int32_t)n1 < (int32_t)n2;
}

static bool u32Max(const void *n1, const void *n2)
{
    #pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
    return (uint32_t)n1 > (uint32_t)n2;
}

static bool u32Min(const void *n1, const void *n2)
{
    #pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
    return (uint32_t)n1 < (uint32_t)n2;
}

int32_t i32Array_Max(const i32Array *input)
{
    const void *ReturnData = ArrayNumberCompare(input->Data, input->Size, sizeof(int32_t), &i32Max);
    return (int32_t)ReturnData;
}

int32_t i32Array_Min(const i32Array *input)
{
    const void *ReturnData = ArrayNumberCompare(input->Data, input->Size, sizeof(int32_t), &i32Min);
    return (int32_t)ReturnData;
}

uint32_t u32Array_Max(const u32Array *input)
{
    const void *ReturnData = ArrayNumberCompare(input->Data, input->Size, sizeof(uint32_t), &u32Max);
    return (uint32_t)ReturnData;
}

uint32_t u32Array_Min(const u32Array *input)
{
    const void *ReturnData = ArrayNumberCompare(input->Data, input->Size, sizeof(uint32_t), &u32Min);
    return (uint32_t)ReturnData;
}

bool i32Array_Equal(const i32Array *first, const i32Array *second) {
    if (first->Size != second->Size) {
        return false;
    }

    for(size_t index = 0; index < first->Size; index++) {
        if (first->Data[index] != second->Data[index]) {
            return false;
        }
    }

    return true;
}

bool u32Array_Equal(const u32Array *first, const u32Array *second) {
    if (first->Size != second->Size) {
        return false;
    }

    for(size_t index = 0; index < first->Size; index++) {
        if (first->Data[index] != second->Data[index]) {
            return false;
        }
    }

    return true;
}

int32_t i32Array_Sum(const i32Array *input) {
#if DEBUG()
    assert(input != NULL);
#endif

    if (input->Size == 0) {
        return 0;
    }

    int32_t ReturnData = 0;
    for(size_t index = 0; index < input->Size; index++) {
        int32_t NextNumber = input->Data[index];

        if (NextNumber > INT32_MAX - ReturnData) {
            return INT32_MAX;
        }

        ReturnData += NextNumber;
    }

    return ReturnData;
}

uint32_t u32Array_Sum(const u32Array *input) {
#if DEBUG()
    assert(input != NULL);
#endif

    if (input->Size == 0) {
        return 0;
    }

    uint32_t ReturnData = 0;
    for(size_t index = 0; index < input->Size; index++) {
        uint32_t NextNumber = input->Data[index];

        if (NextNumber > UINT32_MAX - ReturnData) {
            return UINT32_MAX;
        }

        ReturnData += NextNumber;
    }

    return ReturnData;
}

uint32_t u32Array_Average(const u32Array *input) {
#if DEBUG()
    assert(input != NULL);
#endif

    if (input->Size == 0) {
        return 0;
    }

    uint32_t Sum = 0;
    for(size_t index = 0; index < input->Size; index++) {
        uint32_t NextNumber = input->Data[index];

        if (NextNumber > UINT32_MAX - Sum) {
            return 0;
        }

        Sum += NextNumber;
    }

    return Sum / input->Size;
}

int32_t i32Array_Average(const i32Array *input) {
#if DEBUG()
    assert(input != NULL);
#endif

    if (input->Size == 0) {
        return 0;
    }

    int32_t Sum = 0;
    for(size_t index = 0; index < input->Size; index++) {
        int32_t NextNumber = input->Data[index];

        if (NextNumber > INT32_MAX - Sum) {
            return 0;
        }

        Sum += input->Data[index];
    }

    return Sum / input->Size;
}

int32_t i32Array_Median(const i32Array *input) {
#if DEBUG()
    assert(input != NULL);
#endif

    if (input->Size == 0) {
        return 0;
    }

    if (input->Size == 1) {
        return input->Data[0];
    }

    if (input->Size % 2 != 0) {
        return input->Data[input->Size / 2];
    }

    int32_t Num1 = input->Data[input->Size / 2];
    int32_t Num2 = input->Data[(input->Size / 2) - 1];

    return (Num1 + Num2) / 2;
}

uint32_t u32Array_Median(const u32Array *input) {
#if DEBUG()
    assert(input != NULL);
#endif

    if (input->Size == 0) {
        return 0;
    }

    if (input->Size == 1) {
        return input->Data[0];
    }

    if (input->Size % 2 != 0) {
        return input->Data[input->Size / 2];
    }

    uint32_t Num1 = input->Data[input->Size / 2];
    uint32_t Num2 = input->Data[(input->Size / 2) - 1];

    return (Num1 + Num2) / 2;
}

/**
 * @brief  Returns a copy of an array with a number removed from a specific index.
 * @param  input: The array to removed a number from. Must not be null.
 * @param  index: The index of the number to omit from the returned array. Must be greater than 0 and less than input->Size.
 * @retval An IntegerArray that is a copy of input with the number removed from the index that was given.
 */
/*IntegerArray *i32Array_RemoveAt(const IntegerArray* input, int32_t index)
{
#if DEBUG()
    assert(input != NULL);
    assert(input->Type == I32);
#endif

    if (index > (input->Size-1) || index < 0) {
        Fatal("Index is greater than the size of the input array or less than 0");
        return NULL;
    }

    if (input->Size == 1) {
        return i32Array_Make(0, NULL);
    }

    int32_t NewArraySize = input->Size - 1;
    int32_t NewArray[NewArraySize];
    int32_t NewArrayIndex = 0;

    for(int32_t arrayIndex = 0; arrayIndex < input->Size; arrayIndex++) {
        if (arrayIndex == index) continue;
        NewArray[NewArrayIndex] = input->i32Data[arrayIndex];
        NewArrayIndex++;
    }

    IntegerArray* ReturnData = i32Array_Make(NewArraySize, NewArray);

#if DEBUG()
    assert(ReturnData != NULL);
#endif

    return ReturnData;
}*/

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

bool StringToInt(const char *input, int32_t length, int32_t* output)
{
    int64_t Output = 0;
    if (!StringToLong(input, length, &Output))
    {
        *output = 0;
        return false;
    }

    return LongToInt(Output, output);
}

/**
 * @brief   Converts numbers founds in strings to 64-bit integers. Ignores leading whitespace, and will convert a sequence of contigous digits to an int until a non-digit character is found or until length is reached.
            Leading zeroes before the first number sequence - or between the negative sign and the first digit - are counted as non-digits.
            Examples:
            - "0123", "a123", "-0123", "0-123" returns true with output = 0
            - "123x4", "123 4". "123" or "  123" returns true with output = 123
            - "-456x7", "-456 7". "-456" or "  -456" returns true with output = -456
            - "9223372036854775807" and "-9223372036854775808" returns false with output = 0 (int under/overflow by calculation)
            - "92233720368547758070" and "-92233720368547758080" returns false with output = 0 (max int overflow by too many contigous digits)
 * @param  *input: The string with potential numbers in them you want to parse. Not allowed to be NULL or false is returned.
 * @param  length: The max amount of characters to process in the input. Typically the length of input (minus null terminator) but can be less. Must be at least 1 or false is returned.
 * @param  output: A pointer to a long where the parsed number will be stored in. Will be initialized to 0. Must not be NULL or false is returned.
 * @retval True if parsing succeeded, or false if parsing failed due to an error. True does not mean a number was found, just that no errors happened. False can mean multiple things:
 * - input or output was NULL
 * - length was was less than 1
 * - a number was found but it under- or overflowed the max value of a 32-bit int
 * - a null terminator character was found in input before length was reached
 *
 * In all cases output will be 0 upon return EXCEPT if output is NULL (since that would be dereferencing a null pointer)
 */
bool StringToLong(const char *input, int32_t length, int64_t* output)
{
    if (output == NULL) {
        DEBUG_PRINT("StringToLong: output is null", NULL);
        return false;
    }

    *output = 0;

    if (input == NULL || length < 1) {
        DEBUG_PRINT("StringToLong: input is null and/or length is less than 1\n", NULL);
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
            DEBUG_PRINT("StringToLong: premature null terminator found in input (1)\n", NULL);
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
                DEBUG_PRINT("StringToLong: premature null terminator found in input (2)\n", NULL);
                *output = 0;
                return false;
            }
            break;
        }
        // 9223372036854775807
        Digits++;
        // Overflow, we now have 11 digits and there's 10 in the max or min int value OR we have a null terminator
        if (Digits > 19) {
            DEBUG_PRINT("StringToLong: max/min int over flow (max 19 digits)\n", NULL);
            *output = 0;
            return false;
        }

        *output *= 10; // Advance to next decimal
        int32_t NextNumber = NextCharacter - '0'; // Convert char to int

        // Deal with potential over- or underflow of max/min int value
        if (Digits == 10) {
            int64_t ValueSoFar = *output;
            int64_t MaxBeforeOverflow;

            if (IsNegative) {
                MaxBeforeOverflow = (LONG_LONG_MIN - ValueSoFar) * -1;
            } else {
                MaxBeforeOverflow = LONG_LONG_MAX - ValueSoFar;
            }

            if (NextNumber > MaxBeforeOverflow) {
                DEBUG_PRINT("StringToLong: max/min int overflow (calculation)\n", NULL);
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

// INT overflow functions

bool OverflowIntOnAdd(int32_t first, int32_t second)
{
    if (first > 0 && second > INT_MAX - first) return true; // `a + x` would overflow
    if (first < 0 && second < INT_MIN - first) return true; // `a + x` would underflow
    return false;
}

bool OverflowIntOnSub(int32_t first, int32_t second)
{
    if (first < 0 && second > INT_MAX + first) return true; // `a - x` would overflow
    if (first > 0 && second < INT_MIN + first) return true; // `a - x` would underflow
    return false;
}

bool OverflowIntOnMul(int32_t x, int32_t a)
{
    // There may be a need to check for -1 for two's complement machines.
    // If one number is -1 and another is INT_MIN, multiplying them we get abs(INT_MIN) which is 1 higher than INT_MAX
    if (a == -1 && x == INT_MIN) return true; // `a * x` can overflow
    if (x == -1 && a == INT_MIN) return true; // `a * x` (or `a / x`) can overflow
    // general case
    if (x != 0 && a > INT_MAX / x) return true; // `a * x` would overflow
    if (x != 0 && a < INT_MIN / x) return true; // `a * x` would underflow
    return false;
}

// LONG overflow functions

bool OverflowLongOnAdd(int64_t first, int64_t second)
{
    if (first > 0 && second > LONG_LONG_MAX - first) return true; // `a + x` would overflow
    if (first < 0 && second < LONG_LONG_MIN - first) return true; // `a + x` would underflow
    return false;
}

bool OverflowLongOnSub(int64_t first, int64_t second)
{
    if (first < 0 && second > LONG_LONG_MAX + first) return true; // `a - x` would overflow
    if (first > 0 && second < LONG_LONG_MIN + first) return true; // `a - x` would underflow
    return false;
}

bool OverflowLongOnMul(int64_t x, int64_t a)
{
    // There may be a need to check for -1 for two's complement machines.
    // If one number is -1 and another is INT_MIN, multiplying them we get abs(INT_MIN) which is 1 higher than INT_MAX
    if (a == -1 && x == LONG_LONG_MIN) return true; // `a * x` can overflow
    if (x == -1 && a == LONG_LONG_MIN) return true; // `a * x` (or `a / x`) can overflow
    // general case
    if (x != 0 && a > LONG_LONG_MAX / x) return true; // `a * x` would overflow
    if (x != 0 && a < LONG_LONG_MIN / x) return true; // `a * x` would underflow
    return false;
}
