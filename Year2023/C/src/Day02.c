#include "LibThomas.h"
#include "LibNumeric.h"
#include "LibString.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>
#include <strings.h>

int main(void)
{
    StringArray *InputParts = File_ReadAllLines("Input/02.txt");
    if (InputParts == NULL) return EXIT_FAILURE;

    int32_t FinalAnswerPart1 = 0;
    int32_t FinalAnswerPart2 = 0;

    for (int32_t LineIndex = 0; LineIndex < InputParts->Count; LineIndex++) {
        String *CurrentLine = InputParts->Contents[LineIndex];
        char GameIndexBuffer[4] = { 0 };
        memcpy(GameIndexBuffer, CurrentLine->Content + 5, 3);

        int32_t Red = 0;
        int32_t Green = 0;
        int32_t Blue = 0;

        int32_t GameIndex = atoi(GameIndexBuffer);

        int32_t ColorIndex = 5;
        if (GameIndex < 10)
            ColorIndex += 3;
        else if (GameIndex < 100)
            ColorIndex += 4;
        else
            ColorIndex += 5;

        char *CurrentLineContent = CurrentLine->Content;
        for (int32_t ColorParseIndex = ColorIndex; ColorParseIndex < CurrentLine->Size;) {
            char ColorCountBuffer[3] = { 0 };

            ColorCountBuffer[0] = CurrentLineContent[ColorParseIndex];
            ColorCountBuffer[1] = CurrentLineContent[ColorParseIndex + 1];

            int32_t ColorCount;
            if (!StringToInt(ColorCountBuffer, sizeof(ColorCountBuffer)-1, &ColorCount)) {
                Fatal("Failed to parse string in colorbuffer to int :(");
            }

            if (ColorCount < 10)
                ColorParseIndex += 2;
            else
                ColorParseIndex += 3;

            switch (CurrentLineContent[ColorParseIndex]) {
            case 'r':
                if (ColorCount > Red) Red = ColorCount;
                ColorParseIndex += 5;
                break;
            case 'b':
                if (ColorCount > Blue) Blue = ColorCount;
                ColorParseIndex += 6;
                break;
            case 'g':
                if (ColorCount > Green) Green = ColorCount;
                ColorParseIndex += 7;
                break;
            }
        }

        if (Red <= 12 && Green <= 13 && Blue <= 14) FinalAnswerPart1 += GameIndex;
        FinalAnswerPart2 += (Red * Green * Blue);
    }

    StringArray_Free(InputParts, true);

    printf("Part 1 answer: %i\n", FinalAnswerPart1);
    printf("Part 2 answer: %i\n", FinalAnswerPart2);
    assert(FinalAnswerPart1 == 2204);
    assert(FinalAnswerPart2 == 71036);

    return EXIT_SUCCESS;
}
