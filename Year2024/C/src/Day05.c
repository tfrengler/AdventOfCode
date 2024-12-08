#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

StringArray *Input = NULL;

typedef struct {
    int32_t First;
    int32_t Second;
} IntPair;

int32_t RuleCount = 0;
int32_t PageCount = 0;
IntPair *Rules = NULL;
IntegerArray *Pages = NULL;

bool RulesContain(int32_t first, int32_t second)
{
    for (int32_t index = 0; index < RuleCount; index++) {
        if (Rules[index].First == first && Rules[index].Second == second) {
            return true;
        }
    }

    return false;
}

bool SequenceEquals(int32_t *sequenceA, int32_t *sequenceB, int32_t length)
{
    for (int32_t index = 0; index < length; index++) {
        if (sequenceA[index] != sequenceB[index]) {
            return false;
        }
    }
    return true;
}

int CompareRules(const void* first, const void* second)
{
    int32_t First = *((int32_t *)first);
    int32_t Second = *((int32_t*)second);
    if (RulesContain(First, Second)) return -1;
    if (RulesContain(Second, First)) return 1;
    return 0;
}

void Setup(void)
{
    TimerStart();
    Input = File_ReadAllLines("./Input/05.txt");
    assert(Input != NULL);

    int32_t StartIndexPages = 0;

    for (int32_t inputIndex = 0; inputIndex < Input->Count; inputIndex++) {
        if (Input->Contents[inputIndex]->Content == NULL) {
            StartIndexPages = inputIndex + 1;
            RuleCount = inputIndex + 1;
        }
    }

    Rules = Malloc(sizeof(IntPair) * RuleCount);
    PageCount = Input->Count - StartIndexPages;
    Pages = Malloc(sizeof(IntegerArray) * PageCount);

    for (int32_t inputIndex = 0; inputIndex < StartIndexPages - 1; inputIndex++) {
        String *CurrentLine = Input->Contents[inputIndex];

        Rules[inputIndex].First = CurrentLine->Content[0] - '0';
        Rules[inputIndex].First *= 10;
        Rules[inputIndex].First += CurrentLine->Content[1] - '0';

        Rules[inputIndex].Second = CurrentLine->Content[3] - '0';
        Rules[inputIndex].Second *= 10;
        Rules[inputIndex].Second += CurrentLine->Content[4] - '0';
    }

    int32_t PageIndex = 0;

    for (int32_t inputIndex = StartIndexPages; inputIndex < Input->Count; inputIndex++) {
        int32_t IntegerPairs = (int32_t)ceil((double)Input->Contents[inputIndex]->Size / 3);
        int32_t *Values = Malloc(sizeof(int32_t) * IntegerPairs);
        int32_t ValueIndex = 0;

        for (int32_t index = 0; index < Input->Contents[inputIndex]->Size; index += 3) {
            Values[ValueIndex] = Input->Contents[inputIndex]->Content[index] - '0';
            Values[ValueIndex] *= 10;
            Values[ValueIndex] += Input->Contents[inputIndex]->Content[index+1] - '0';
            ValueIndex++;
        }

        Pages[PageIndex].Size = IntegerPairs;
        Pages[PageIndex].Type = I32;
        Pages[PageIndex].i32Data = Values;
        PageIndex++;
    }


    TimerStop();
    PrintTimer();
    puts("SETUP DONE");
}

void Part01(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    for(int32_t index = 0; index < PageCount; index++)
    {
        IntegerArray Current = Pages[index];
        int32_t CopiedValues[Current.Size];
        memcpy(CopiedValues, Current.i32Data, Current.Size * sizeof(int32_t));

        IntegerArray Sorted = Current;
        Sorted.i32Data = CopiedValues;

        qsort(Sorted.i32Data, Sorted.Size, sizeof(int32_t), CompareRules);

        if (SequenceEquals(Sorted.i32Data, Current.i32Data, Sorted.Size))
        {
            PartAnswer += Current.i32Data[ Current.Size / 2 ];
        }
    }

    TimerStop();
    PrintTimer();

    printf("Part 01 answer: %i\n", PartAnswer);
    assert(PartAnswer == 5452);
}

void Part02(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    for(int32_t index = 0; index < PageCount; index++)
    {
        IntegerArray Current = Pages[index];
        int32_t CopiedValues[Current.Size];
        memcpy(CopiedValues, Current.i32Data, Current.Size * sizeof(int32_t));

        IntegerArray Sorted = Current;
        Sorted.i32Data = CopiedValues;

        qsort(Sorted.i32Data, Sorted.Size, sizeof(int32_t), CompareRules);

        if (!SequenceEquals(Sorted.i32Data, Current.i32Data, Sorted.Size))
        {
            PartAnswer += Sorted.i32Data[ Current.Size / 2 ];
        }
    }

    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %i\n", PartAnswer);
    assert(PartAnswer == 4598);
}

int main(void)
{
    Setup();

    Part01();
    Part02();

    StringArray_Free(Input, true);
    Free(Rules);
    for(int32_t index = 0; index < PageCount; index++) {
        Free(Pages[index].i32Data);
    }
    Free(Pages);

    // PrintAllocations();
    return EXIT_SUCCESS;
}
