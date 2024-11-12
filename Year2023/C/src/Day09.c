#include "LibNumeric.h"
#include "LibString.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "LibThomas.h"

#define NUMBERS_PER_ROW() 21
#define ROWS() 200
const int32_t NumbersPerRow = NUMBERS_PER_ROW();
const int32_t Rows = ROWS();
int32_t **Sequences;

void ParseInput(void)
{
    size_t AllocSize = Rows * sizeof(int32_t*);
    Sequences = Malloc(AllocSize);

    StringArray *TestInput = File_ReadAllLines("Input/09.txt");

    if (TestInput == 0x0) {
        exit(EXIT_FAILURE);
    }

    for (int32_t index = 0; index < Rows; index++) {

        String *CurrentLine = TestInput->Contents[index];
        Sequences[index] = Malloc(NumbersPerRow * sizeof(int32_t));

        int32_t ColumnIndex = 0;
        int32_t ExtractStartIndex = 0;

        for (int32_t lineIndex = 0; lineIndex < CurrentLine->Size; lineIndex++) {

            bool EndOfLine = lineIndex == (CurrentLine->Size - 1);
            if (CurrentLine->Content[lineIndex] == ' ' || EndOfLine) {

                int32_t ExtractLength = lineIndex - ExtractStartIndex;
                if (EndOfLine) ExtractLength++;
                StringToInt(&CurrentLine->Content[ExtractStartIndex], ExtractLength, &Sequences[index][ColumnIndex]);

                ColumnIndex++;
                ExtractStartIndex = lineIndex;
            }

        }
    }

    StringArray_Free(TestInput, true);
}

int32_t CalculateAnswer(void)
{
    int32_t PartAnswer = 0;

    for (int32_t rowIndex = 0; rowIndex < Rows; rowIndex++) {

        int32_t Differences[NUMBERS_PER_ROW()] = {0};
        int32_t *CurrentRow = Sequences[rowIndex];
        int32_t Difference = 0;

        int32_t AllZeroesAccumulator = 0;
        memcpy(&Differences, CurrentRow, NumbersPerRow * sizeof(*CurrentRow));
        int32_t NextValueAddition = 0;
        int32_t DifferenceHead = NumbersPerRow;

        while (true) {

            AllZeroesAccumulator = 0;
            DifferenceHead--;

            for (int32_t columnIndex = 0; columnIndex < DifferenceHead; columnIndex++) {

                Difference = Differences[columnIndex+1] - Differences[columnIndex];
                Differences[columnIndex] = Difference;
                AllZeroesAccumulator += abs(Difference);
            }

            NextValueAddition += Difference;
            if (AllZeroesAccumulator == 0) break;
        }

        int32_t HistoryValue = NextValueAddition + CurrentRow[NumbersPerRow - 1];
        //printf("Row %i: %i\n", rowIndex, HistoryValue);
        PartAnswer += HistoryValue;
    }

    return PartAnswer;
}

void Part01(void)
{
    int32_t Answer = CalculateAnswer();
    printf("Part 1 answer: %i\n", Answer);
    assert(Answer == 1974913025);
}

void Part02(void)
{
    // Easiest part two answer ever. Just reverse the arrays and do the same calculations
    for (int32_t index = 0; index < Rows; index++) {

        int32_t *CurrentArray = Sequences[index];
        int32_t start = 0;
        int32_t end = NumbersPerRow - 1;

        while (start < end) {
            int32_t temp = CurrentArray[start];
            CurrentArray[start] = CurrentArray[end];
            CurrentArray[end] = temp;
            start++;
            end--;
        }
    }

    int32_t Answer = CalculateAnswer();
    printf("Part 2 answer: %i\n", Answer);
    assert(Answer == 884);
}

int main(void)
{
    ParseInput();
    Part01();
    Part02();

    for (int32_t index = 0; index < Rows; index++) {
        Free(Sequences[index]);
    }
    Free(Sequences);
    // PrintAllocations();

    exit(EXIT_SUCCESS);
}
