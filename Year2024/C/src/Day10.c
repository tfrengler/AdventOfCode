#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibGrid.h"
#include "LibMem.h"
#include "LibThomas.h"
#include "LibString.h"

typedef struct _TrailPosition
{
    int32_t Row;
    int32_t Column;
    int32_t Number;
} TrailPosition;

#define VISITED_BUFFER_COUNT() 500

StringArray *Input = nullptr;

int32_t VisitedIndex = 0;
TrailPosition Visited[VISITED_BUFFER_COUNT()] = {0};

size_t TrailheadIndex = 0;
size_t TrailheadCount = 0;
TrailPosition TrailHeads[275] = {0}; // Cheating a bit by knowing how many trailheads are there beforehand

void Setup(void)
{
    MemArena_Init(1024 * 1024 * 1);
    Input = File_ReadAllLines("./Input/10.txt");
    assert(Input != nullptr);

    Grid_BoundaryCrossIsNotFatal();

    for(int32_t rowIndex = 0; rowIndex < Input->Count; rowIndex++) {
        String *CurrentRow = Input->Contents[rowIndex];

        for(int32_t columnIndex = 0; columnIndex < Input->Count; columnIndex++) {

            if (CurrentRow->Content[columnIndex] == '0') {
                TrailHeads[TrailheadIndex] = (TrailPosition){ .Row = rowIndex, .Column = columnIndex };
                TrailheadIndex++;
            }
        }
    }

    TrailheadCount = TrailheadIndex;
}

void EnumerateTrail(TrailPosition position, bool checkVisited, int32_t *score) {

    if (position.Number == 9) {
        if (checkVisited) {
            for(int32_t visitIndex = 0; visitIndex < VisitedIndex; visitIndex++) {
                if (Visited[visitIndex].Row == position.Row && Visited[visitIndex].Column == position.Column) {
                    return;
                }
            }

            Visited[VisitedIndex] = position;
            VisitedIndex++;
        }

        (*score)++;
        return;
    }

    GridPoint AdjacentPositions[4] = {0};
    Grid_GetCross(
        Input,
        AdjacentPositions,
        position.Column,
        position.Row);

    for(int32_t index = 0; index < 4; index++) {
        GridPoint *CurrentAdjacentPosition = &AdjacentPositions[index];
        if (!CurrentAdjacentPosition->IsValid) continue;

        int32_t AdjacentPositionValue = CurrentAdjacentPosition->Value - '0';

        if (AdjacentPositionValue - position.Number != 1) {
            continue;
        }

        TrailPosition NextPosition = (TrailPosition){ .Number = AdjacentPositionValue, .Row = AdjacentPositions[index].Y, AdjacentPositions[index].X };
        EnumerateTrail(NextPosition, checkVisited, score);
    }
}

void Part01(void)
{
    int64_t PartAnswer = 0;
    TimerStart();

    for(TrailheadIndex = 0; TrailheadIndex < TrailheadCount; TrailheadIndex++) {

        memset(Visited, 0, VISITED_BUFFER_COUNT());
        VisitedIndex = 0;
        int32_t Score = 0;
        EnumerateTrail(TrailHeads[TrailheadIndex], true, &Score);

        PartAnswer += Score;
    }

    TimerStop();
    PrintTimer();

    printf("Part 01 answer: %zu\n", PartAnswer);
    assert(PartAnswer == 746);
}

void Part02(void)
{
    int64_t PartAnswer = 0;
    TimerStart();

    for(TrailheadIndex = 0; TrailheadIndex < TrailheadCount; TrailheadIndex++) {

        memset(Visited, 0, VISITED_BUFFER_COUNT());
        VisitedIndex = 0;
        int32_t Score = 0;
        EnumerateTrail(TrailHeads[TrailheadIndex], false, &Score);

        PartAnswer += Score;
    }

    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %zu\n", PartAnswer);
    assert(PartAnswer == 1541);
}

int main(void)
{
    Setup();

    Part01();
    Part02();

    MemFree(Input);
    // PrintAllocations();
    return EXIT_SUCCESS;
}
