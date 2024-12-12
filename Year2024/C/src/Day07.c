#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

StringArray *Input = NULL;
IntegerArray *InputData = NULL;

void Setup(void)
{
    Input = File_ReadAllLines("./Input/07.txt");
    assert(Input != NULL);

    InputData = Malloc(sizeof(IntegerArray) * Input->Count);

    for(int32_t lineIndex = 0; lineIndex < Input->Count; lineIndex++) {
        String *CurrentLine = Input->Contents[lineIndex];

        StringArray *NumbersAsStrings = String_Split(CurrentLine, ' ');
        InputData[lineIndex].Size = NumbersAsStrings->Count;
        InputData[lineIndex].Type = I64;
        InputData[lineIndex].i64Data = Malloc(sizeof(int64_t) * NumbersAsStrings->Count);

        for(int32_t numberIndex = 0; numberIndex < NumbersAsStrings->Count; numberIndex++) {
            String *CurrentNumber = NumbersAsStrings->Contents[numberIndex];
            if (!StringToLong(CurrentNumber->Content, CurrentNumber->Size, &InputData[lineIndex].i64Data[numberIndex]))
            {
                char Error[1000] = {0};
                sprintf(Error, "StringToLong failed on line %i, at number %i\n", lineIndex + 1, numberIndex + 1);
                Fatal(Error);
            }
        }

        StringArray_Free(NumbersAsStrings, true);
    }
}

bool Calculate(int64_t result, int64_t accumulator, int64_t numbers[], int32_t index, int32_t maxDepth)
{
    if (index >= maxDepth) return false;

    int64_t LocalResult = accumulator + numbers[index];
    if (LocalResult == result) return true;
    if (LocalResult > result) return false;

    if (Calculate(result, LocalResult, numbers, index + 1, maxDepth))
    {
        return true;
    }

    LocalResult = accumulator * numbers[index];
    if (LocalResult == result) return true;
    if (LocalResult > result) return false;

    if (Calculate(result, LocalResult, numbers, index + 1, maxDepth))
    {
        return true;
    }

    return false;
}

bool Calculate2(int64_t result, int64_t accumulator, int64_t numbers[], int32_t index, int32_t maxDepth)
{
    if (index >= maxDepth) return false;

    int64_t LocalResult = accumulator + numbers[index];
    if (LocalResult == result) return true;
    if (LocalResult > result) return false;

    if (Calculate2(result, LocalResult, numbers, index + 1, maxDepth))
    {
        return true;
    }

    LocalResult = accumulator * numbers[index];
    if (LocalResult == result) return true;
    if (LocalResult > result) return false;

    if (Calculate2(result, LocalResult, numbers, index + 1, maxDepth))
    {
        return true;
    }

    int64_t pow = 10;
    while(accumulator >= pow)
    {
        pow *= 10;
    }
    LocalResult = numbers[index] * pow + accumulator;

    if (LocalResult == result) return true;
    if (LocalResult > result) return false;

    if (Calculate2(result, LocalResult, numbers, index + 1, maxDepth))
    {
        return true;
    }

    return false;
}

void Part01(void)
{
    int64_t PartAnswer = 0;
    TimerStart();

    for(int32_t index = 0; index < Input->Count; index++) {
        IntegerArray Current = InputData[index];
        if (Calculate(Current.i64Data[0], 0, &Current.i64Data[1], 0, Current.Size - 1))
        {
            PartAnswer += Current.i64Data[0];
        }
    }

    TimerStop();
    PrintTimer();

    printf("Part 01 answer: %zu\n", PartAnswer);
    assert(PartAnswer == 6231007345478);
}

void Part02(void)
{
    int64_t PartAnswer = 0;
    TimerStart();

    for(int32_t index = 0; index < Input->Count; index++) {
        IntegerArray Current = InputData[index];
        if (Calculate2(Current.i64Data[0], 0, &Current.i64Data[1], 0, Current.Size - 1))
        {
            PartAnswer += Current.i64Data[0];
        }
    }

    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %zu\n", PartAnswer);
    // assert(PartAnswer == -1);
}

int main(void)
{
    Setup();

    // Part01();
    Part02();

    for(int32_t index = 0; index < Input->Count; index++) {
        Free(InputData[index].i64Data);
    }
    Free(InputData);
    StringArray_Free(Input, true);

    PrintAllocations();
    return EXIT_SUCCESS;
}
