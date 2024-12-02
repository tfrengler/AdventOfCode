#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

IntegerArray *Reports = NULL;
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

        bool IsSafe = true;
        int32_t Decreasing = 0;
        int32_t Increasing = 0;
        int32_t Pairs = (Current.Size - 1);

        for (int32_t index = 0; index < Pairs; index++) {
            int32_t First = Current.i32Data[index];
            int32_t Second = Current.i32Data[index + 1];
            int32_t Difference = abs(Second - First);

            if (Difference > 3 || Difference < 1) {
                IsSafe = false;
                break;
            }

            if (Second < First) {
                Decreasing++;
            } else if (Second > First) {
                Increasing++;
            }
        }

        if (IsSafe && (Decreasing == Pairs || Increasing == Pairs)) {
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
    puts("--PART 02 UNSOLVED--");
}

int main(void)
{
    Setup();

    Part01();
    Part02();

    StringArray_Free(Input, true);
    Free(Reports);

    // PrintAllocations();
    return EXIT_SUCCESS;
}
