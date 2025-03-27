#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibGrid.h"
#include "LibThomas.h"
#include "LibString.h"

#define VISITED_BUFFER_COUNT 10000
StringArray *Input = nullptr;
GridPoint StartPosition = {0};
GridPoint Visited[VISITED_BUFFER_COUNT] = {0};
int32_t VisitIndex = 0;

typedef struct {
    int32_t X;
    int32_t Y;
} Point;

void Setup(void)
{
    Input = File_ReadAllLines("./Input/06.txt");
    assert(Input != nullptr);

    for (int32_t yIndex = 0; yIndex < Input->Count; yIndex++) {
        String *Current = Input->Contents[yIndex];
        for (int32_t xIndex = 0; xIndex < Current->Size; xIndex++) {
            if (Current->Content[xIndex] == '^') {
                StartPosition.Value = '^';
                StartPosition.IsValid = true;
                StartPosition.Y = yIndex;
                StartPosition.X = xIndex;
                Current->Content[xIndex] = '.';
                break;
            }
        }
    }
    Grid_BoundaryCrossIsNotFatal();
}

bool HasBeenVisited(GridPoint point)
{
    for(int32_t index = 0; index < VISITED_BUFFER_COUNT; index++) {
        if ( Visited[index].X == point.X && Visited[index].Y == point.Y )
        {
            return true;
        }
    }

    return false;
}

void Part01(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    GridPoint CurrentPosition = StartPosition;
    GridPoint NextPosition = {0};

    while(true) {

        switch (CurrentPosition.Value) {
            case '^':
                Grid_GetNorth(Input, &NextPosition, CurrentPosition.X, CurrentPosition.Y);
                break;
            case '>':
                Grid_GetEast(Input, &NextPosition, CurrentPosition.X, CurrentPosition.Y);
                break;
            case '<':
                Grid_GetWest(Input, &NextPosition, CurrentPosition.X, CurrentPosition.Y);
                break;
            case 'v':
                Grid_GetSouth(Input, &NextPosition, CurrentPosition.X, CurrentPosition.Y);
                break;
        }

        if (!NextPosition.IsValid) {
            PartAnswer++;
            break;
        }

        if (NextPosition.Value != '#') {

            if (!HasBeenVisited(CurrentPosition)) {
                Visited[VisitIndex].X = CurrentPosition.X;
                Visited[VisitIndex].Y = CurrentPosition.Y;
                VisitIndex++;
                PartAnswer++;
            }

            char Direction = CurrentPosition.Value;
            CurrentPosition = NextPosition;
            CurrentPosition.Value = Direction;

            continue;
        }

        switch (CurrentPosition.Value) {
            case '^':
                CurrentPosition.Value = '>';
                break;
            case '>':
                CurrentPosition.Value = 'v';
                break;
            case '<':
                CurrentPosition.Value = '^';
                break;
            case 'v':
                CurrentPosition.Value = '<';
                break;
        }
    }

    TimerStop();
    PrintTimer();

    printf("Part 01 answer: %i\n", PartAnswer);
    // assert(PartAnswer == -1);
}

void Part02(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %i\n", PartAnswer);
    assert(PartAnswer == -1);
}

int main(void)
{
    Setup();

    Part01();
    // Part02();

    StringArray_Free(Input, true);

    // PrintAllocations();
    return EXIT_SUCCESS;
}
