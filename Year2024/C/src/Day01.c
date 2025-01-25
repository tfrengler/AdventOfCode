#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

i64Array Left = {0};
i64Array Right = {0};
StringArray *Input = NULL;

void Setup(void)
{
    Input = File_ReadAllLines("./Input/01.txt");
    assert(Input != NULL);

    int64_t* LeftData = Malloc(Input->Count * sizeof(int64_t));
    int64_t* RightData = Malloc(Input->Count * sizeof(int64_t));
    Left.Size = Input->Count;
    Left.Capacity = Input->Count;
    Left.Data = LeftData;
    Right.Size = Input->Count;
    Right.Capacity = Input->Count;
    Right.Data = RightData;

    for (int32_t index = 0; index < Input->Count; index++)
    {
        bool Success = StringToLong(Input->Contents[index]->Content, 5, &Left.Data[index]);
        assert(Success == true);
        Success = StringToLong(&Input->Contents[index]->Content[8], 5, &Right.Data[index]);
        assert(Success == true);
    }
}

void Part01(void)
{
    TimerStart();

    i64Array_SortDesc(&Left);
    i64Array_SortDesc(&Right);

    int32_t Part01Answer = 0;
    for (int32_t index = 0; index < Input->Count; index++) {
        Part01Answer += llabs(Left.Data[index] - Right.Data[index]);
    }

    TimerStop();
    PrintTimer();
    printf("Part 01 answer: %i\n", Part01Answer);
    assert(Part01Answer == 1197984);
}

void Part02(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    for (size_t indexOuter = 0; indexOuter < Left.Size; indexOuter++) {

        int64_t CurrentLeft = Left.Data[indexOuter];
        int32_t OccurenceFactor = 0;

        for (size_t indexInner = 0; indexInner < Left.Size; indexInner++) {
            int64_t CurrentRight = Right.Data[indexInner];
            if (CurrentRight == CurrentLeft) {
                OccurenceFactor++;
            }
        }

        int64_t Accumulator = CurrentLeft * OccurenceFactor;
        PartAnswer += Accumulator;
    }

    TimerStop();
    PrintTimer();
    printf("Part 02 answer: %i\n", PartAnswer);
    assert(PartAnswer == 23387399);
}

int main(void)
{
    Setup();
    assert(Left.Data != NULL);
    assert(Right.Data != NULL);

    Part01();
    Part02();

    StringArray_Free(Input, true);
    Free(Left.Data);
    Free(Right.Data);

    // PrintAllocations();
    return EXIT_SUCCESS;
}
