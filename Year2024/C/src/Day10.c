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
    int32_t Number;
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

void EnumerateTrail(Trailhead trailhead, int32_t *score) {

    GridPoint TrailPoints[4] = {0};
    Grid_GetCross(
        Input,
        TrailPoints,
        trailhead.Column,
        trailhead.Row);

    for(int32_t index = 0; index < 4; index++) {
        if (!TrailPoints[index].IsValid) continue;

        int32_t NextNumber = TrailPoints[index].Value - '0';
        if (trailhead.Number == 8 && NextNumber == 9) {
            // Is a full trail
            (*score)++;
            return;
        }

        if (NextNumber - trailhead.Number == 1) {
            EnumerateTrail(
                (Trailhead){ .Number = NextNumber, .Row = TrailPoints[index].Y, TrailPoints[index].X },
                score
            );
        }
    }
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

    TrailheadCount = TrailHeadIndex;
    TrailHeadIndex = 0;

    for(; TrailHeadIndex < TrailheadCount; TrailHeadIndex++) {
        int32_t Score = 0;
        EnumerateTrail(TrailHeads[TrailHeadIndex], &Score);
        printf("Trailhead %zu score is: %d\n", TrailHeadIndex, Score);
        PartAnswer += Score;
    }

    // int32_t NextNumber = NextCharacter - '0'; // Convert char to int
    // printf("Trailheads: %zu\n", arrayCount(TrailHeads));

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
