#include "LibThomas.h"
#include "stdlib.h"
#include <assert.h>
#include <strings.h>
#include "stdio.h"

int main(void)
{
    StringArray* Input = File_ReadAllLines("Input/01.txt");
    i32 PartOneAnswer = 0;

    char Buffer[3];
    memset(&Buffer, 0, 2);
    Buffer[2] = '\0';
    int BufferIndex = 0;

    for(i32 LineIndex = 0; LineIndex < Input->Count; LineIndex++)
    {
        String* CurrentString = Input->Contents[LineIndex];

        for(i32 StringIndex = 0; StringIndex < CurrentString->Size; StringIndex++)
        {
            char CurrentChar = CurrentString->Content[StringIndex];
            if ((int)CurrentChar < 58 && (int)CurrentChar > 48)
            {
                Buffer[BufferIndex] = CurrentChar;
                if (BufferIndex == 0) BufferIndex = 1;
            }
        }

        if (Buffer[1] == 0) Buffer[1] = Buffer[0];
        i32 CalibrationNumber = atoi(Buffer);

        memset(&Buffer, 0, 2);
        BufferIndex = 0;

        PartOneAnswer += CalibrationNumber;
        //if (LineIndex == 10) break;
    }

    printf("Part one answer: %i\n", PartOneAnswer);
    assert(PartOneAnswer == 55621);

    return EXIT_SUCCESS;
}


