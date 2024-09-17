#include "LibNumeric.h"
#include "LibString.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibThomas.h"

int main(void)
{
    #define NUMBERS_PER_ROW() 21
    #define ROWS() 200
    const int32_t NumbersPerRow = NUMBERS_PER_ROW();
    const int32_t Rows = ROWS();
    int32_t Part1Answer = 0;

    size_t AllocSize = Rows * sizeof(int32_t*);
    int32_t **Sequences = Malloc(AllocSize);

    StringArray *TestInput = File_ReadAllLines("Input/09.txt");

    if (TestInput == 0x0) {
        exit(EXIT_FAILURE);
    }

    for (int32_t index = 0; index < Rows; index++) {
        // printf("ROW STARTED: %i\n", index);

        String *CurrentLine = TestInput->Contents[index];
        Sequences[index] = Malloc(NumbersPerRow * sizeof(int32_t));

        int32_t ColumnIndex = 0;
        int32_t ExtractStartIndex = 0;

        for (int32_t lineIndex = 0; lineIndex < CurrentLine->Size; lineIndex++) {
            // printf("COLUMN STARTED: %i\n", lineIndex);

            bool EndOfLine = lineIndex == (CurrentLine->Size - 1);
            if (CurrentLine->Content[lineIndex] == ' ' || EndOfLine) {
                // printf("EXTRACT NUMBER | ExtractStartIndex: %i | length: %i | column: %i\n", ExtractStartIndex, lineIndex - ExtractStartIndex, ColumnIndex);
                int32_t ExtractLength = lineIndex - ExtractStartIndex;
                if (EndOfLine) ExtractLength++;
                StringToInt(&CurrentLine->Content[ExtractStartIndex], ExtractLength, &Sequences[index][ColumnIndex]);

                ColumnIndex++;
                ExtractStartIndex = lineIndex;
            }

            // printf("COLUMN ENDED: %i\n", lineIndex);
        }

        // printf("ROW ENDED: %i\n", index);
    }

    for (int32_t index = 0; index < Rows; index++) {
        if (index == 1) {
            break;
        }
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

    PrintAllocations();
    exit(EXIT_SUCCESS);
}
