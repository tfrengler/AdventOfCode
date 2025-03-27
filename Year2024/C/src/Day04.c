#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"
#include "LibString.h"
#include "LibGrid.h"

StringArray *Input = nullptr;
// Grid function pointers mapped in the order that matches the results gotten from Grid_GetBox
bool (*GridFunctions[8])(StringArray* input, GridPoint* output, int32_t x, int32_t y);

void Setup(void)
{
    Input = File_ReadAllLines("./Input/04.txt");
    assert(Input != nullptr);
    Grid_BoundaryCrossIsNotFatal();

    GridFunctions[0] = Grid_GetNorth;
    GridFunctions[1] = Grid_GetNorthEast;
    GridFunctions[2] = Grid_GetEast;
    GridFunctions[3] = Grid_GetSouthEast;
    GridFunctions[4] = Grid_GetSouth;
    GridFunctions[5] = Grid_GetSouthWest;
    GridFunctions[6] = Grid_GetWest;
    GridFunctions[7] = Grid_GetNorthWest;
}

int8_t FindWord(GridPoint from, char word[], int32_t wordLength)
{
#if DEBUG()
    assert(wordLength > 1);
#endif

    if (from.Value != word[0]) {
        return false;
    }

    GridPoint Result[8] = {0};
    Grid_GetBox(Input, Result, from.X, from.Y);
    int8_t Matches = 0;

    // Determine direction to look in
    for (int32_t index = 0; index < 8; index++) {
        if (!Result[index].IsValid) {
            continue;
        }

        if (Result[index].Value != word[1]) {
            continue;
        }

        GridPoint From = Result[index];
        GridPoint Next = { 0 };
        bool IsMatch = true;

        // We now know the direction. index now matches the function pointer in GridFunctions
        for (int32_t innerIndex = 2; innerIndex < wordLength; innerIndex++) {
            bool Valid = GridFunctions[index](Input, &Next, From.X, From.Y);

            if (!Valid || (Valid && Next.Value != word[innerIndex])) {
                IsMatch = false;
                break; // No matches in this direction after the second letter. Next direction.
            }

            From = Next;
        }

        if (IsMatch) {
            Matches++;
        }
    }

    return Matches;
}

void Part01(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    char TheWord[] = "XMAS";
    int32_t WordSize = arrayCount(TheWord) - 1;
    GridPoint CurrentPoint = { 0 };

    for (int32_t yIndex = 0; yIndex < Input->Count; yIndex++) {
        for (int32_t xIndex = 0; xIndex < Input->Count; xIndex++) {

            char CurrentChar = Input->Contents[yIndex]->Content[xIndex];

            CurrentPoint.Value = CurrentChar;
            CurrentPoint.Y = yIndex;
            CurrentPoint.X = xIndex;
            CurrentPoint.IsValid = true;

            PartAnswer += FindWord(CurrentPoint, TheWord, WordSize);
        }
    }

    TimerStop();
    PrintTimer();

    printf("Part 01 answer: %i\n", PartAnswer);
    assert(PartAnswer == 2370);
}

void Part02(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    GridPoint CurrentPoint = { 0 };
    GridPoint CrossResult[4] = { 0 };

    for (int32_t yIndex = 0; yIndex < Input->Count; yIndex++) {
        for (int32_t xIndex = 0; xIndex < Input->Count; xIndex++) {

            char CurrentChar = Input->Contents[yIndex]->Content[xIndex];

            CurrentPoint.Value = CurrentChar;
            CurrentPoint.Y = yIndex;
            CurrentPoint.X = xIndex;
            CurrentPoint.IsValid = true;

            if (CurrentChar != 'A') {
                continue;
            }

            Grid_GetStar(Input, CrossResult, CurrentPoint.X, CurrentPoint.Y);
            int8_t Matches = 0;

            if ((CrossResult[0].Value == 'M' && CrossResult[2].Value == 'S') || (CrossResult[0].Value == 'S' && CrossResult[2].Value == 'M')) {
                Matches++;
            }
            if ((CrossResult[1].Value == 'M' && CrossResult[3].Value == 'S') || (CrossResult[1].Value == 'S' && CrossResult[3].Value == 'M')) {
                Matches++;
            }
            // Need 2 matches for success
            if (Matches == 2) {
                PartAnswer++;
            }
        }
    }

    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %i\n", PartAnswer);
    assert(PartAnswer == 1908);
}

int main(void)
{
    Setup();

    Part01();
    Part02();

    StringArray_Free(Input, true);

    // PrintAllocations();
    return EXIT_SUCCESS;
}
