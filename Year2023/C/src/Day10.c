#include "LibString.h"
#include "LibThomas.h"
#include <assert.h>
#include <stdio.h>

const int32_t StartX = 111;
const int32_t StartY = 41;

typedef struct {
    int32_t X; // Column
    int32_t Y; // Row
} Position;

int main(void)
{
    StringArray *Input = File_ReadAllLines("Input/10.txt");
    if (Input == NULL) {
        Fatal("Unable to read input");
    }

    assert(Input->Contents[StartY]->Content[StartX] == 'S');

    Position PossibleDirections[] = {
        {.X = StartX - 1, .Y = StartY},
        {.X = StartX, .Y = StartY - 1},
    };
    Position PreviousPosition = { .Y = StartY, .X = StartX };
    Position CurrentPosition = { .Y = StartY, .X = StartX };
    Position NextPosition = {0};
    int32_t StepsTaken = 1;

    while(1)
    {
        NextPosition = PossibleDirections[0];

        char ThePipe = Input->Contents[NextPosition.Y]->Content[NextPosition.X];
        if (ThePipe == '.' || (PreviousPosition.X == NextPosition.X && PreviousPosition.Y == NextPosition.Y))
        {
            NextPosition = PossibleDirections[1];
            ThePipe = Input->Contents[NextPosition.Y]->Content[NextPosition.X];
        }

        PreviousPosition = CurrentPosition;
        CurrentPosition = NextPosition;

        if (ThePipe == 'S')
        {
            // printf("Back at start (%i)\n", StepsTaken);
            break;
        }

        switch(ThePipe)
        {
            case '7':
            {
                PossibleDirections[0].X = CurrentPosition.X - 1;
                PossibleDirections[0].Y = CurrentPosition.Y;
                PossibleDirections[1].X = CurrentPosition.X;
                PossibleDirections[1].Y = CurrentPosition.Y + 1;
            } break;
            case 'F':
            {
                PossibleDirections[0].X = CurrentPosition.X + 1;
                PossibleDirections[0].Y = CurrentPosition.Y;
                PossibleDirections[1].X = CurrentPosition.X;
                PossibleDirections[1].Y = CurrentPosition.Y + 1;
            } break;
            case 'J':
            {
                PossibleDirections[0].X = CurrentPosition.X;
                PossibleDirections[0].Y = CurrentPosition.Y - 1;
                PossibleDirections[1].X = CurrentPosition.X - 1;
                PossibleDirections[1].Y = CurrentPosition.Y;
            } break;
            case 'L':
            {
                PossibleDirections[0].X = CurrentPosition.X;
                PossibleDirections[0].Y = CurrentPosition.Y - 1;
                PossibleDirections[1].X = CurrentPosition.X + 1;
                PossibleDirections[1].Y = CurrentPosition.Y;
            } break;
            case '|':
            {
                PossibleDirections[0].X = CurrentPosition.X;
                PossibleDirections[0].Y = CurrentPosition.Y - 1;
                PossibleDirections[1].X = CurrentPosition.X;
                PossibleDirections[1].Y = CurrentPosition.Y + 1;
            } break;
            case '-':
            {
                PossibleDirections[0].X = CurrentPosition.X - 1;
                PossibleDirections[0].Y = CurrentPosition.Y;
                PossibleDirections[1].X = CurrentPosition.X + 1;
                PossibleDirections[1].Y = CurrentPosition.Y;
            } break;
            default:
                Fatal("Say what now?");
        }

        if (StepsTaken > 100000)
        {
            puts("Took more than 100k steps");
            break;
        }

        StepsTaken++;
    }

    int32_t Answer = StepsTaken / 2;
    printf("Part 1 answer: %i\n", Answer);
    assert(Answer == 6649);

    StringArray_Free(Input, true);
    //PrintAllocations();
}
