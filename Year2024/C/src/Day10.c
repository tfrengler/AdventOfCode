#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibGrid.h"
#include "LibMem.h"
#include "LibThomas.h"
#include "LibString.h"
// #include "LibNumeric.h"

typedef struct _Trailhead
{
    int32_t Row;
    int32_t Column;
} Trailhead;

StringArray *Input = nullptr;

void Setup(void)
{
    MemArena_Init(1024 * 1024 * 4); // 4mb heap
    // Input = File_ReadAllText("./Input/10.txt");

    Input = File_ReadAllLines("./Input/Debug.txt");
    assert(Input != nullptr);

    Grid_BoundaryCrossIsNotFatal();
}

void Part01(void)
{
    int64_t PartAnswer = 0;
    TimerStart();

    size_t TrailHeadIndex = 0;
    size_t TrailheadCount = 0;
    // Trailhead TrailHeads[275] = {0};
    Trailhead TrailHeads[9] = {0}; // Cheating a bit by knowing how many trailheads are there beforehand

    for(int32_t rowIndex = 0; rowIndex < Input->Count; rowIndex++) {
        String *CurrentRow = Input->Contents[rowIndex];

        for(int32_t columnIndex = 0; columnIndex < Input->Count; columnIndex++) {

            if (CurrentRow->Content[columnIndex] == '0') {
                TrailHeads[TrailHeadIndex] = (Trailhead){ .Row = rowIndex, .Column = columnIndex };
                TrailHeadIndex++;
            }

        }
    }

    TrailheadCount = TrailHeadIndex + 1;
    TrailHeadIndex = 0;
    int32_t NextNumber = 1;
    GridPoint TrailPoints[4] = {0};

    for(; TrailHeadIndex < TrailheadCount; TrailHeadIndex++) {
        Grid_GetCross(Input, TrailPoints, TrailHeads[TrailHeadIndex].Row, TrailHeads[TrailHeadIndex].Column);

        if (TrailPoints[0].IsValid && TrailPoints[0].Value - '0' == NextNumber) {

        }
        if (TrailPoints[1].IsValid && TrailPoints[1].Value - '0' == NextNumber) {

        }
        if (TrailPoints[2].IsValid && TrailPoints[2].Value - '0' == NextNumber) {

        }
        if (TrailPoints[3].IsValid && TrailPoints[3].Value - '0' == NextNumber) {

        }
    }

    // int32_t NextNumber = NextCharacter - '0'; // Convert char to int
    printf("Trailheads: %zu\n", arrayCount(TrailHeads));

    TimerStop();
    PrintTimer();

    printf("Part 01 answer: %zu\n", PartAnswer);
    assert(PartAnswer == 666);
}

void Part02(void)
{
    int64_t PartAnswer = 0;
    TimerStart();


    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %zu\n", PartAnswer);
    assert(PartAnswer == 6363268339304);
}

int main(void)
{
    Setup();

    Part01();
    Part02();

    // PrintAllocations();
    return EXIT_SUCCESS;
}
