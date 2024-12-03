#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

IntegerArray *Reports = NULL;
StringArray *Input = NULL;

const byte SafeAndLinear = 0x01;

byte IsSafeAndLinear(IntegerArray* input)
{
    byte ReturnData = 0;
    int32_t Decreasing = 0;
    int32_t Increasing = 0;
    int32_t Pairs = (input->Size - 1);

    for (int32_t index = 0; index < Pairs; index++) {
        int32_t First = input->i32Data[index];
        int32_t Second = input->i32Data[index + 1];
        int32_t Difference = abs(Second - First);

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

    Reports = Malloc(sizeof(IntegerArray) * Input->Count);

    for (int32_t index = 0; index < Input->Count; index++)
    {
        StringArray *NumberParts = String_Split(Input->Contents[index], ' ');
        assert(NumberParts != NULL);
        assert(NumberParts->Count > 0);

        int32_t CurrentReportNumbers[NumberParts->Count];

        for (int32_t numberIndex = 0; numberIndex < NumberParts->Count; numberIndex++)
        {
            bool Success = StringToInt(
                NumberParts->Contents[numberIndex]->Content,
                NumberParts->Contents[numberIndex]->Size,
                &CurrentReportNumbers[numberIndex]);

            assert(Success == true);
        }

        IntegerArray *CurrentReport = i32Array_Make(NumberParts->Count, CurrentReportNumbers);
        assert(CurrentReport != NULL);
        Reports[index] = *CurrentReport;

        IntegerArray_Free(CurrentReport, false);
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
        IntegerArray Current = Reports[reportsIndex];

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
        IntegerArray Current = Reports[reportsIndex];

        byte Result = IsSafeAndLinear(&Current);

        if (Result == SafeAndLinear) {
            PartAnswer++;
            continue;
        }

        for (int32_t outerIndex = 0; outerIndex < Current.Size; outerIndex++) {
            IntegerArray* Copy = i32Array_RemoveAt(&Current, outerIndex);

            Result = IsSafeAndLinear(Copy);
            IntegerArray_Free(Copy, true);

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
        Free(Reports[index].i32Data);
    }
    Free(Reports);
    StringArray_Free(Input, true);

    // PrintAllocations();
    return EXIT_SUCCESS;
}
