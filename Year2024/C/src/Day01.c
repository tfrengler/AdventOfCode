#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

int compareInts(const void *first, const void *second)
{
    int32_t First = *(const int32_t *)first;
    int32_t Second = *(const int32_t *)second;

    if (First < Second) return -1;
    if (First > Second) return 1;
    return 0;
}

int main(void)
{
    StringArray *Input = File_ReadAllLines("./Input/01.txt");
    assert(Input != NULL);

    IntegerArray *Left = i32Array_Make(Input->Count, NULL);
    IntegerArray *Right = i32Array_Make(Input->Count, NULL);

    for (int32_t index = 0; index < Input->Count; index++)
    {
        bool Success = StringToInt(Input->Contents[index]->Content, 5, &Left->i32Data[index]);
        assert(Success == true);
        Success = StringToInt(&Input->Contents[index]->Content[8], 5, &Right->i32Data[index]);
        assert(Success == true);
    }

    qsort(Left->i32Data, Left->Size, sizeof(int32_t), compareInts);
    qsort(Right->i32Data, Right->Size, sizeof(int32_t), compareInts);

    int32_t Part01Answer = 0;
    for (int32_t index = 0; index < Input->Count; index++) {
        Part01Answer += abs(Left->i32Data[index] - Right->i32Data[index]);
    }

    printf("Part 01 answer: %i\n", Part01Answer);

    StringArray_Free(Input, true);
    IntegerArray_Free(Left, true);
    IntegerArray_Free(Right, true);

    PrintAllocations();

    assert(Part01Answer == 1197984);
    return EXIT_SUCCESS;
}
