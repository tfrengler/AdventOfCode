#include "LibThomas.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>
#include <strings.h>
#include "stdio.h"

int main(void)
{
    StringArray *InputParts = File_ReadAllLines("Input/02.txt");
    if (InputParts == NULL) return EXIT_FAILURE;

    i32 FinalAnswerPart1 = 0;
    i32 FinalAnswerPart2 = 0;

    for(i32 LineIndex = 0; LineIndex < InputParts->Count; LineIndex++)
    {
        String *CurrentLine = InputParts->Contents[LineIndex];
        char GameIndexBuffer[4] = {0};
        memcpy(GameIndexBuffer, CurrentLine->Content + 5, 3);

        u8 Red = 0;
        u8 Green = 0;
        u8 Blue = 0;

        i32 GameIndex = atoi(GameIndexBuffer);

        i32 ColorIndex = 5;
        if (GameIndex < 10) ColorIndex += 3;
        else if (GameIndex < 100) ColorIndex += 4;
        else ColorIndex += 5;

        char *CurrentLineContent = CurrentLine->Content;
        for(i32 ColorParseIndex = ColorIndex; ColorParseIndex < CurrentLine->Size;)
        {
            char ColorCountBuffer[3] = {0};

            ColorCountBuffer[0] = CurrentLineContent[ColorParseIndex];
            ColorCountBuffer[1] = CurrentLineContent[ColorParseIndex+1];

            u8 ColorCount = (u8)atoi(ColorCountBuffer);

            if (ColorCount < 10) ColorParseIndex += 2;
            else ColorParseIndex += 3;

            switch(CurrentLineContent[ColorParseIndex])
            {
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

    StringArray_Free(InputParts);

    printf("Answer (part 1): %i\n", FinalAnswerPart1);
    printf("Answer (part 2): %i\n", FinalAnswerPart2);
    assert(FinalAnswerPart1 == 2204);
    assert(FinalAnswerPart2 == 71036);

    return EXIT_SUCCESS;
}
