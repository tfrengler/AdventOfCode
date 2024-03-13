#include "LibThomas.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>
#include <strings.h>
#include "stdio.h"

typedef struct _Gear
{
    char Symbol;
    i32 SymbolPosition;
    i32 Number;
} Gear;

int main(void)
{
    //StringArray *InputParts = File_ReadAllLines("Input/03.txt");

    char* TestInput = "467..114..\n...*......\n..35..633.\n......#...\n617*......\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664.598..";
    String *TestString = String_Make(TestInput, 109);
    StringArray *InputParts = String_Split(TestString, '\n');
    String_Free(TestString);
    if (InputParts == NULL) return EXIT_FAILURE;

    assert(InputParts->Count == 10);

    for(i32 LineIndex = 5; LineIndex < InputParts->Count; LineIndex++)
    {
        String *CurrentLine = InputParts->Contents[LineIndex];
        char* CurrentString = CurrentLine->Content;

        for(i32 InnerIndex = 0; InnerIndex < CurrentLine->Size;)
        {
            if (CurrentString[InnerIndex] < 48 || CurrentString[InnerIndex] > 57)
            {
                InnerIndex++;
                continue;
            }

            char NumberBuffer[4] = {0};
            memcpy(&NumberBuffer, &CurrentString[InnerIndex], 3);

            i32 Number = atoi(NumberBuffer);
            i32 DigitsToCheck = 0;
            i32 NumberStartPosition = InnerIndex;

            if (Number < 10)
            {
                DigitsToCheck = 3;
                InnerIndex += 2;
            }
            else if (Number < 100)
            {
                DigitsToCheck = 4;
                InnerIndex += 3;
            }
            else
            {
                DigitsToCheck = 5;
                InnerIndex += 4;
            }

            // To account for numbers against the right edge...
            if (CurrentLine->Size - InnerIndex < 4)
            {
                DigitsToCheck--;
            }

            // Check N if we are not on the first line
            if (LineIndex > 0)
            {
                String *PreviousLine = InputParts->Contents[LineIndex - 1];
                i32 SymbolPositionsLeftToCheck = DigitsToCheck; 
                
                for(i32 SymbolCheckIndex = NumberStartPosition == 0 ? NumberStartPosition : NumberStartPosition -1; SymbolPositionsLeftToCheck > 0; SymbolPositionsLeftToCheck--)
                {
                    char Symbol = PreviousLine->Content[SymbolCheckIndex];
                    SymbolCheckIndex++;
                }
            }
        }
    }

    puts("All done!");
    return EXIT_SUCCESS;
}
