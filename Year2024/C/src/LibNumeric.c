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
#include "LibMem.h"

/************************** int32 functions **************************/

int64_t i64Array_Max(const i64Array *input)
{
#if DEBUG()
    assert(input != nullptr);
    assert(input->Data != nullptr);
#endif

    if (input-> Size < 2) {
        return 0;
    }

    int64_t ReturnData = 0;

    for(size_t index = 0; index < input->Size; index++) {
        if (input->Data[index] > ReturnData) {
            ReturnData = input->Data[index];
        }
    }

    return ReturnData;
}

int64_t i64Array_Min(const i64Array *input)
{
#if DEBUG()
    assert(input != nullptr);
    assert(input->Data != nullptr);
#endif

    if (input-> Size < 2) {
        return 0;
    }

    int64_t ReturnData = INT64_MAX;

    for(size_t index = 0; index < input->Size; index++) {
        if (input->Data[index] < ReturnData) {
            ReturnData = input->Data[index];
        }
    }

    return ReturnData;
}

bool i64Array_Equal(const i64Array *first, const i64Array *second)
{
#if DEBUG()
    assert(first != nullptr);
    assert(first->Data != nullptr);
    assert(second != nullptr);
    assert(second->Data != nullptr);
#endif

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

int64_t i64Array_Sum(const i64Array *input) {
#if DEBUG()
    assert(input != nullptr);
    assert(input->Data != nullptr);
#endif

    if (input->Size == 0) {
        return 0;
    }

    if (input->Size == 1) {
        return input->Data[0];
    }

    int64_t ReturnData = 0;
    for(size_t index = 0; index < input->Size; index++) {
        int64_t NextNumber = input->Data[index];
        // Guard against overflow which is undefined behaviour
        if (NextNumber > (INT64_MAX - ReturnData)) {
            return INT64_MAX;
        }

        ReturnData += NextNumber;
    }

    return ReturnData;
}

int64_t i64Array_Average(const i64Array *input) {
    int64_t Sum = i64Array_Sum(input);
    return Sum / input->Size;
}

int64_t i64Array_Median(const i64Array *input) {
#if DEBUG()
    assert(input != nullptr);
    assert(input->Data != nullptr);
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

    int64_t Num1 = input->Data[input->Size / 2];
    int64_t Num2 = input->Data[(input->Size / 2) - 1];

    return (Num1 + Num2) / 2;
}

i64Array* i64Array_Copy(const i64Array *input, i64Array *output) {
#if DEBUG()
    assert(input != nullptr);
    assert(input->Data != nullptr);
    assert(output != nullptr);
    assert(output->Data != nullptr);
    assert(output->Capacity >= input->Size);
#endif

    for(size_t index = 0; index < input->Size; index++) {
        output->Data[index] = input->Data[index];
    }

    output->Size = input->Size;
    return output;
}

i64Array* i64Array_CopyM(const i64Array *input) {
#if DEBUG()
    assert(input != nullptr);
    assert(input->Data != nullptr);
#endif

    i64Array* ReturnData = MemRequest(sizeof(i64Array));
    int64_t* Data = MemRequest(input->Size * sizeof(int64_t));

    ReturnData->Capacity = input->Size;
    ReturnData->Data = Data;

    return i64Array_Copy(input, ReturnData);
}

static int32_t i64SortAsc(const void *n1, const void *n2) {
    if (*(int64_t*)n1 > *(int64_t*)n2) return 1;
    if (*(int64_t*)n1 < *(int64_t*)n2) return -1;
    return 0;
}

static int32_t i64SortDesc(const void *n1, const void *n2) {
    if (*(int64_t*)n1 < *(int64_t*)n2) return 1;
    if (*(int64_t*)n1 > *(int64_t*)n2) return -1;
    return 0;
}

void i64Array_SortAsc(i64Array *input) {
#if DEBUG()
    assert(input != nullptr);
    assert(input->Data != nullptr);
#endif

    qsort(input->Data, input->Size, sizeof(int64_t), &i64SortAsc);
}

void i64Array_SortDesc(i64Array *input) {
#if DEBUG()
    assert(input != nullptr);
    assert(input->Data != nullptr);
#endif

    qsort(input->Data, input->Size, sizeof(int64_t), &i64SortDesc);
}

/**
 * @brief  Returns a copy of an array with a number removed from a specific index.
 * @param  input: The array to removed a number from. Must not be nullptr.
 * @param  index: The index of the number to omit from the returned array. Must be greater than 0 and less than input->Size.
 * @retval An IntegerArray that is a copy of input with the number removed from the index that was given.
 */
i64Array *i64Array_RemoveAt(const i64Array* input, size_t index)
{
#if DEBUG()
    assert(input != nullptr);
    assert(input->Data != nullptr);
#endif

    if (index > (input->Size-1)) {
        Fatal("Index is greater than the size of the input array");
        return nullptr;
    }

    if (input->Size == 1) {
        i64Array *ReturnData = MemRequest(sizeof(i64Array));
        ReturnData->Size = 0;
        ReturnData->Capacity = 0;
        ReturnData->Data = nullptr;
        return ReturnData;
    }

    size_t NewArraySize = input->Size - 1;
    int64_t *NewArray = MemRequest(NewArraySize * sizeof(int64_t));
    int64_t NewArrayIndex = 0;

    for(size_t arrayIndex = 0; arrayIndex < input->Size; arrayIndex++) {
        if (arrayIndex == index) continue;
        NewArray[NewArrayIndex] = input->Data[arrayIndex];
        NewArrayIndex++;
    }

    i64Array *ReturnData = MemRequest(sizeof(i64Array));
    ReturnData->Size = NewArraySize;
    ReturnData->Capacity = NewArraySize;
    ReturnData->Data = NewArray;

    return ReturnData;
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
 * @param  *input: The string with potential numbers in them you want to parse. Not allowed to be nullptr or false is returned.
 * @param  length: The max amount of characters to process in the input. Typically the length of input (minus nullptr terminator) but can be less. Must be at least 1 or false is returned.
 * @param  output: A pointer to a long where the parsed number will be stored in. Will be initialized to 0. Must not be nullptr or false is returned.
 * @retval True if parsing succeeded, or false if parsing failed due to an error. True does not mean a number was found, just that no errors happened. False can mean multiple things:
 * - input or output was nullptr
 * - length was was less than 1
 * - a number was found but it under- or overflowed the max value of a 32-bit int
 * - a nullptr terminator character was found in input before length was reached
 *
 * In all cases output will be 0 upon return EXCEPT if output is nullptr (since that would be dereferencing a nullptr pointer)
 */
bool StringToLong(const char *input, int32_t length, int64_t* output)
{
    if (output == nullptr) {
        DEBUG_PRINT("StringToLong: output is nullptr", nullptr);
        return false;
    }

    *output = 0;

    if (input == nullptr || length < 1) {
        DEBUG_PRINT("StringToLong: input is nullptr and/or length is less than 1\n", nullptr);
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
            DEBUG_PRINT("StringToLong: premature nullptr terminator found in input (1)\n", nullptr);
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
            // ...unless it's a nullptr terminator in which cases length is longer than input which is bad
            if (NextCharacter == '\0') {
                DEBUG_PRINT("StringToLong: premature nullptr terminator found in input (2)\n", nullptr);
                *output = 0;
                return false;
            }
            break;
        }
        // 9223372036854775807
        Digits++;
        // Overflow, we now have 11 digits and there's 10 in the max or min int value OR we have a nullptr terminator
        if (Digits > 19) {
            DEBUG_PRINT("StringToLong: max/min int over flow (max 19 digits)\n", nullptr);
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
                DEBUG_PRINT("StringToLong: max/min int overflow (calculation)\n", nullptr);
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
