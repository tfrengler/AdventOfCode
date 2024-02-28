#include "LibThomas.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>
#include <strings.h>
#include "stdio.h"

typedef struct _PatternTestResult
{
    i32 PatternSize;
    char Value;
} PatternTestResult;

PatternTestResult* TestPattern(const String* input, const String* pattern, char returnOnSuccess)
{
    u8 Result = String_StartsWith(input, pattern, 0);
    if (!Result) return NULL;

    PatternTestResult* ReturnData = malloc(sizeof(PatternTestResult));
    #if DEBUG()
        if (ReturnData == NULL) Fatal("Failed to malloc memory for PatternTestResult*");
    #endif

    ReturnData->PatternSize = pattern->Size;
    ReturnData->Value = returnOnSuccess;

    return ReturnData;
}

PatternTestResult* Test1(const String* input)
{
    String* Pattern = String_Make("one", 3);
    return TestPattern(input, Pattern, '1');
}

PatternTestResult* Test2(const String* input)
{
    String* Pattern = String_Make("two", 3);
    return TestPattern(input, Pattern, '2');
}

PatternTestResult* Test3(const String* input)
{
    String* Pattern = String_Make("three", 5);
    return TestPattern(input, Pattern, '3');
}

PatternTestResult* Test4(const String* input)
{
    String* Pattern = String_Make("four", 4);
    return TestPattern(input, Pattern, '4');
}

PatternTestResult* Test5(const String* input)
{
    String* Pattern = String_Make("five", 4);
    return TestPattern(input, Pattern, '5');
}

PatternTestResult* Test6(const String* input)
{
    String* Pattern = String_Make("six", 3);
    return TestPattern(input, Pattern, '6');
}

PatternTestResult* Test7(const String* input)
{
    String* Pattern = String_Make("seven", 5);
    return TestPattern(input, Pattern, '7');
}

PatternTestResult* Test8(const String* input)
{
    String* Pattern = String_Make("eight", 5);
    return TestPattern(input, Pattern, '8');
}

PatternTestResult* Test9(const String* input)
{
    String* Pattern = String_Make("nine", 4);
    return TestPattern(input, Pattern, '9');
}

int main(void)
{
    StringArray* Input = File_ReadAllLines("Input/01.txt");
    // StringArray* DebugInput = File_ReadAllLines("C:/Temp/Debug.txt");
    i32 PartAnswer = 0;

    PatternTestResult* (*PatternTesters[9])(const String* input);
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

    i32 BufferIndex = 0;

    for(i32 LineIndex = 0; LineIndex < Input->Count; LineIndex++)
    {
        String* CurrentString = Input->Contents[LineIndex];

        for(i32 StringIndex = 0; StringIndex < CurrentString->Size; StringIndex++)
        {
            char CurrentChar = CurrentString->Content[StringIndex];
            if ((int)CurrentChar < 58 && (int)CurrentChar > 48)
            {
                NumberAsStringBuffer[BufferIndex] = CurrentChar;
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }

            i32 CharsToTake = CurrentString->Size - StringIndex;
            assert(CharsToTake > 0);
            if (CharsToTake > 5) CharsToTake = 5;

            char NumberAsWordBuffer[CharsToTake+1];
            memset(&NumberAsWordBuffer, 0, CharsToTake+1);
            memcpy(&NumberAsWordBuffer, &CurrentString->Content[StringIndex], CharsToTake);
            String* StringToTest = String_Make(NumberAsWordBuffer, (u16)CharsToTake);

            for(i32 Index = 0; Index < 9; Index++)
            {
                PatternTestResult* TestResult = PatternTesters[Index](StringToTest);
                if (TestResult != NULL)
                {
                    NumberAsStringBuffer[BufferIndex] = TestResult->Value;
                    StringIndex += (TestResult->PatternSize - 2); // Min 2 because the last letter could be the start of a new number, tricksy...
                    if (BufferIndex == 0) BufferIndex = 1;
                    break;
                }
            }
        }

        if (NumberAsStringBuffer[1] == 0) NumberAsStringBuffer[1] = NumberAsStringBuffer[0];
        i32 CalibrationNumber = atoi(NumberAsStringBuffer);

        // i32 DebugCompare = atoi(DebugInput->Contents[LineIndex]->Content);
        // if (CalibrationNumber != DebugCompare)
        // {
        //     printf("%d is not equal to %d, on line %d", CalibrationNumber, DebugCompare, LineIndex);
        //     exit(EXIT_FAILURE);
        // }

        memset(&NumberAsStringBuffer, 0, sizeof NumberAsStringBuffer);
        BufferIndex = 0;

        PartAnswer += CalibrationNumber;
        //if (LineIndex == 0) break;
    }

    printf("Part answer: %i\n", PartAnswer);
    assert(PartAnswer == 53592);

    return EXIT_SUCCESS;
}


