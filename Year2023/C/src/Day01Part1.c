#include "LibThomas.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>

int main(void)
{
    StringArray *Input = File_ReadAllLines("Input/01.txt");
    if (Input == NULL) return EXIT_FAILURE;
    int32_t PartAnswer = 0;

    char Buffer[3];
    memset(&Buffer, 0, 2);
    Buffer[2] = '\0';
    int BufferIndex = 0;

    for (int32_t LineIndex = 0; LineIndex < Input->Count; LineIndex++) {
        String *CurrentString = Input->Contents[LineIndex];

        for (int32_t StringIndex = 0; StringIndex < CurrentString->Size; StringIndex++) {
            char CurrentChar = CurrentString->Content[StringIndex];
            if ((int)CurrentChar < 58 && (int)CurrentChar > 48) {
                Buffer[BufferIndex] = CurrentChar;
                if (BufferIndex == 0) BufferIndex = 1;
            }
        }

        if (Buffer[1] == 0) Buffer[1] = Buffer[0];
        int32_t CalibrationNumber = atoi(Buffer);

        memset(&Buffer, 0, 2);
        BufferIndex = 0;

        PartAnswer += CalibrationNumber;
        // if (LineIndex == 10) break;
    }

    printf("Part answer: %i\n", PartAnswer);
    assert(PartAnswer == 55621);

    return EXIT_SUCCESS;
}
