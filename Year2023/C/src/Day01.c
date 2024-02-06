#include "LibThomas.h"
#include "stdio.h"
#include "stdlib.h"
#include <strings.h>

typedef struct Point {
    int32 x;
    int32 y;
} Point;

// int argCount, arrayOfStrings args
int main(void)
{
    string InputFile = File_Read("Input/01.txt");

    int32 Index = 0;
    while(1)
    {
        if (InputFile[Index] == '\0')
        {
            DEBUG_PRINT("Size (manual strlen)? %d\n", Index);
            break;
        }
        Index++;
        if (Index > 30000) break;
    }

    FILE *OutputFileHandle1 = fopen("Debug1.txt", "w");
    fwrite(InputFile, 1, Index, OutputFileHandle1);

    int64 FileSize = strlen(InputFile);
    FILE *OutputFileHandle2 = fopen("Debug2.txt", "w");
    fwrite(InputFile, 1, FileSize, OutputFileHandle2);

    fclose(OutputFileHandle1);
    fclose(OutputFileHandle2);

    int TestArray[6] = { 1,2,3,4,5,6 };

    DEBUG_PRINT("ArrayCount count: %d\n", arrayCount(TestArray));
    DEBUG_PRINT("Filesize (strlen): %d\n", FileSize);

    return EXIT_SUCCESS;
}
