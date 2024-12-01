#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

IntegerArray *Left = NULL;
IntegerArray *Right = NULL;
StringArray *Input = NULL;

int compareInts(const void *first, const void *second)
{
    int32_t First = *(const int32_t *)first;
    int32_t Second = *(const int32_t *)second;

    if (First < Second) return -1;
    if (First > Second) return 1;
    return 0;
}

void Setup(void)
{
    Input = File_ReadAllLines("./Input/01.txt");
    assert(Input != NULL);

    Left = i32Array_Make(Input->Count, NULL);
    Right = i32Array_Make(Input->Count, NULL);

    for (int32_t index = 0; index < Input->Count; index++)
    {
        bool Success = StringToInt(Input->Contents[index]->Content, 5, &Left->i32Data[index]);
        assert(Success == true);
        Success = StringToInt(&Input->Contents[index]->Content[8], 5, &Right->i32Data[index]);
        assert(Success == true);
    }
}

void Part01(void)
{
    clock_t start, end;
    start = clock();

    qsort(Left->i32Data, Left->Size, sizeof(int32_t), compareInts);
    qsort(Right->i32Data, Right->Size, sizeof(int32_t), compareInts);

    int32_t Part01Answer = 0;
    for (int32_t index = 0; index < Input->Count; index++) {
        Part01Answer += abs(Left->i32Data[index] - Right->i32Data[index]);
    }

    end = clock();
    PrintTimeDiffInMS(start, end);
    printf("Part 01 answer: %i\n", Part01Answer);
    assert(Part01Answer == 1197984);
}

void Part02(void)
{
    clock_t start, end;
    int32_t PartAnswer = 0;
    start = clock();

    for (int32_t indexOuter = 0; indexOuter < Left->Size; indexOuter++) {

        int32_t CurrentLeft = Left->i32Data[indexOuter];
        int32_t OccurenceFactor = 0;

        for (int32_t indexInner = 0; indexInner < Left->Size; indexInner++) {
            int32_t CurrentRight = Right->i32Data[indexInner];
            if (CurrentRight == CurrentLeft) {
                OccurenceFactor++;
            }
        }

        int32_t Accumulator = CurrentLeft * OccurenceFactor;
        PartAnswer += Accumulator;
    }

    end = clock();
    PrintTimeDiffInMS(start, end);
    printf("Part 02 answer: %i\n", PartAnswer);
    assert(PartAnswer == 23387399);
}

int main(void)
{
    Setup();
    assert(Left != NULL);
    assert(Right != NULL);

    Part01();
    Part02();

    StringArray_Free(Input, true);
    IntegerArray_Free(Left, true);
    IntegerArray_Free(Right, true);

    // PrintAllocations();
    return EXIT_SUCCESS;
}
