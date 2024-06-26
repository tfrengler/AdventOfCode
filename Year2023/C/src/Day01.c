#include "LibThomas.h"
#include "LibNumeric.h"
#include "LibString.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>
#include <strings.h>

typedef struct _PatternTestResult {
    int32_t PatternSize;
    char Value;
} PatternTestResult;

PatternTestResult *TestPattern(const String *input, const String *pattern, char returnOnSuccess)
{
    bool Result = String_StartsWith(input, pattern, 0);
    if (!Result) return NULL;

    PatternTestResult *ReturnData = malloc(sizeof(*ReturnData));
#if DEBUG()
    if (ReturnData == NULL) Fatal("Failed to malloc memory for PatternTestResult*");
#endif

    ReturnData->PatternSize = pattern->Size;
    ReturnData->Value = returnOnSuccess;

    return ReturnData;
}

PatternTestResult *Test1(const String *input)
{
    String *Pattern = String_Make("one", 3);
    PatternTestResult *ReturnData = TestPattern(input, Pattern, '1');
    String_Free(Pattern);
    return ReturnData;
}

PatternTestResult *Test2(const String *input)
{
    String *Pattern = String_Make("two", 3);
    PatternTestResult *ReturnData = TestPattern(input, Pattern, '2');
    String_Free(Pattern);
    return ReturnData;
}

PatternTestResult *Test3(const String *input)
{
    String *Pattern = String_Make("three", 5);
    PatternTestResult *ReturnData = TestPattern(input, Pattern, '3');
    String_Free(Pattern);
    return ReturnData;
}

PatternTestResult *Test4(const String *input)
{
    String *Pattern = String_Make("four", 4);
    PatternTestResult *ReturnData = TestPattern(input, Pattern, '4');
    String_Free(Pattern);
    return ReturnData;
}

PatternTestResult *Test5(const String *input)
{
    String *Pattern = String_Make("five", 4);
    PatternTestResult *ReturnData = TestPattern(input, Pattern, '5');
    String_Free(Pattern);
    return ReturnData;
}

PatternTestResult *Test6(const String *input)
{
    String *Pattern = String_Make("six", 3);
    PatternTestResult *ReturnData = TestPattern(input, Pattern, '6');
    String_Free(Pattern);
    return ReturnData;
}

PatternTestResult *Test7(const String *input)
{
    String *Pattern = String_Make("seven", 5);
    PatternTestResult *ReturnData = TestPattern(input, Pattern, '7');
    String_Free(Pattern);
    return ReturnData;
}

PatternTestResult *Test8(const String *input)
{
    String *Pattern = String_Make("eight", 5);
    PatternTestResult *ReturnData = TestPattern(input, Pattern, '8');
    String_Free(Pattern);
    return ReturnData;
}

PatternTestResult *Test9(const String *input)
{
    String *Pattern = String_Make("nine", 4);
    PatternTestResult *ReturnData = TestPattern(input, Pattern, '9');
    String_Free(Pattern);
    return ReturnData;
}

int Part1(void)
{
    StringArray *Input = File_ReadAllLines("Input/01.txt");
    if (Input == NULL) return EXIT_FAILURE;
    int32_t PartAnswer = 0;

    char Buffer[3] = {0};
    int BufferIndex = 0;

    for (int32_t LineIndex = 0; LineIndex < Input->Count; LineIndex++) {
        String* CurrentString = Input->Contents[LineIndex];

        for (int32_t StringIndex = 0; StringIndex < CurrentString->Size; StringIndex++) {
            char CurrentChar = CurrentString->Content[StringIndex];
            if ((int)CurrentChar < 58 && (int)CurrentChar > 48) {
                Buffer[BufferIndex] = CurrentChar;
                if (BufferIndex == 0) BufferIndex = 1;
            }
        }

        if (Buffer[1] == 0) Buffer[1] = Buffer[0];
        int32_t CalibrationNumber;
        if (!StringToInt(Buffer, sizeof(Buffer) - 1, &CalibrationNumber)) {
            Fatal("Failed to parse string buffer to int32\n");
        }

        memset(&Buffer, 0, sizeof(Buffer));
        BufferIndex = 0;

        PartAnswer += CalibrationNumber;
        // if (LineIndex == 10) break;
    }

    printf("Part 1 answer: %i\n", PartAnswer);
    assert(PartAnswer == 55621);

    return EXIT_SUCCESS;
}

int Part2(void)
{
    StringArray *Input = File_ReadAllLines("Input/01.txt");
    if (Input == NULL) return EXIT_FAILURE;
    int32_t PartAnswer = 0;

    PatternTestResult *(*PatternTesters[9])(const String *input);
    PatternTesters[0] = Test1;
    PatternTesters[1] = Test2;
    PatternTesters[2] = Test3;
    PatternTesters[3] = Test4;
    PatternTesters[4] = Test5;
    PatternTesters[5] = Test6;
    PatternTesters[6] = Test7;
    PatternTesters[7] = Test8;
    PatternTesters[8] = Test9;

    char NumberAsStringBuffer[3];
    memset(&NumberAsStringBuffer, 0, sizeof(NumberAsStringBuffer));

    int32_t BufferIndex = 0;

    for (int32_t LineIndex = 0; LineIndex < Input->Count; LineIndex++) {
        String* CurrentString = Input->Contents[LineIndex];

        for (int32_t StringIndex = 0; StringIndex < CurrentString->Size; StringIndex++) {
            char CurrentChar = CurrentString->Content[StringIndex];
            if ((int)CurrentChar < 58 && (int)CurrentChar > 48) {
                NumberAsStringBuffer[BufferIndex] = CurrentChar;
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }

            int32_t CharsToTake = CurrentString->Size - StringIndex;
#if DEBUG()
            assert(CharsToTake > 0);
#endif
            if (CharsToTake > 5) CharsToTake = 5;

            char NumberAsWordBuffer[CharsToTake + 1];
            memset(&NumberAsWordBuffer, 0, CharsToTake + 1);
            memcpy(&NumberAsWordBuffer, &CurrentString->Content[StringIndex], CharsToTake);
            String *StringToTest = String_Make(NumberAsWordBuffer, CharsToTake);

            for (int32_t Index = 0; Index < 9; Index++) {
                PatternTestResult *TestResult = PatternTesters[Index](StringToTest);

                if (TestResult != NULL) {
                    NumberAsStringBuffer[BufferIndex] = TestResult->Value;
                    StringIndex += (TestResult->PatternSize - 2); // Min 2 because the last letter could be the start of a new number, tricksy...
                    if (BufferIndex == 0) BufferIndex = 1;
                    free(TestResult);
                    break;
                }

                free(TestResult);
            }
        }

        if (NumberAsStringBuffer[1] == 0) NumberAsStringBuffer[1] = NumberAsStringBuffer[0];
        int32_t CalibrationNumber;
        if (!StringToInt(NumberAsStringBuffer, sizeof(NumberAsStringBuffer) - 1, &CalibrationNumber)) {
            Fatal("Failed to parse NumberAsStringBuffer to int");
        }

        memset(&NumberAsStringBuffer, 0, sizeof NumberAsStringBuffer);
        BufferIndex = 0;

        PartAnswer += CalibrationNumber;
    }

    StringArray_Free(Input, true);

    printf("Part 1 answer: %i\n", PartAnswer);
    assert(PartAnswer == 53592);

    return EXIT_SUCCESS;
}

int main(void)
{
    int ExitCode;

    ExitCode = Part1();
    ExitCode = Part2();

    return ExitCode;
}
