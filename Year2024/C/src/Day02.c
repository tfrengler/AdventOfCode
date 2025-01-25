#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

i64Array *Reports = NULL;
StringArray *Input = NULL;

const byte SafeAndLinear = 0x01;

byte IsSafeAndLinear(i64Array* input)
{
    byte ReturnData = 0;
    size_t Decreasing = 0;
    size_t Increasing = 0;
    size_t Pairs = (input->Size - 1);

    for (size_t index = 0; index < Pairs; index++) {
        int64_t First = input->Data[index];
        int64_t Second = input->Data[index + 1];
        int64_t Difference = llabs(Second - First);

        if (Difference > 3 || Difference < 1) {
            bitset(ReturnData, 7);
        }

        if (Second < First) {
            Decreasing++;
        } else if (Second > First) {
            Increasing++;
        }
    }

    if (Decreasing == Pairs || Increasing == Pairs) {
        bitset(ReturnData, 0);
    }

    return ReturnData;
}

void Setup(void)
{
    TimerStart();

    Input = File_ReadAllLines("./Input/02.txt");
    assert(Input != NULL);
    assert(Input->Count == 1000);

    Reports = Malloc(sizeof(i64Array) * Input->Count);

    for (int32_t index = 0; index < Input->Count; index++)
    {
        StringArray *NumberParts = String_Split(Input->Contents[index], ' ');
        assert(NumberParts != NULL);
        assert(NumberParts->Count > 0);

        int64_t *CurrentReportNumbers = Malloc(NumberParts->Count * sizeof(int64_t));

        for (int32_t numberIndex = 0; numberIndex < NumberParts->Count; numberIndex++)
        {
            bool Success = StringToLong(
                NumberParts->Contents[numberIndex]->Content,
                NumberParts->Contents[numberIndex]->Size,
                &CurrentReportNumbers[numberIndex]);

            assert(Success == true);
        }

        i64Array CurrentReport = { .Size = NumberParts->Count, .Data = CurrentReportNumbers };
        Reports[index] = CurrentReport;

        StringArray_Free(NumberParts, true);
    }

    TimerStop();
    PrintTimer();
    puts("Setup finished");
}

void Part01(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    for (int32_t reportsIndex = 0; reportsIndex < Input->Count; reportsIndex++) {
        i64Array Current = Reports[reportsIndex];

        byte Result = IsSafeAndLinear(&Current);

        if (Result == SafeAndLinear) {
            PartAnswer++;
        }
    }

    TimerStop();
    PrintTimer();
    printf("Part 01 answer: %i\n", PartAnswer);
    assert(PartAnswer == 639);
}

void Part02(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    for (int32_t reportsIndex = 0; reportsIndex < Input->Count; reportsIndex++) {
        i64Array Current = Reports[reportsIndex];

        byte Result = IsSafeAndLinear(&Current);

        if (Result == SafeAndLinear) {
            PartAnswer++;
            continue;
        }

        for (size_t outerIndex = 0; outerIndex < Current.Size; outerIndex++) {
            i64Array* Copy = i64Array_RemoveAt(&Current, outerIndex);

            Result = IsSafeAndLinear(Copy);
            Free(Copy->Data);
            Free(Copy);

            if (Result == SafeAndLinear) {
                PartAnswer++;
                break;
            }
        }
    }

    TimerStop();
    PrintTimer();
    printf("Part 02 answer: %i\n", PartAnswer);
    assert(PartAnswer == 674);
}

int main(void)
{
    Setup();

    Part01();
    Part02();

    for(int32_t index = 0; index < Input->Count; index++)
    {
        Free(Reports[index].Data);
    }
    Free(Reports);
    StringArray_Free(Input, true);

    // PrintAllocations();
    return EXIT_SUCCESS;
}
