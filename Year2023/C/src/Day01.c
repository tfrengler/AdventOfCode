#include "Types.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include <strings.h>

// int argCount, arrayOfStrings args
int main(void)
{
    FILE* InputFileHandle = fopen("Input/01.txt", "r");

    fseek(InputFileHandle, 0, SEEK_END);
    int64 FileSize = ftell(InputFileHandle);
    fseek(InputFileHandle, 0, SEEK_SET);

    char Input[FileSize];
    int64 Index = 0;

    while (1) {
        if (feof(InputFileHandle)) break;
        Input[Index] = (char)fgetc(InputFileHandle);
        Index++;
    }
    Input[Index] = '\0';
    Index--;

    string token = strtok(Input, "\n");

    while( token != NULL ) {
        printf( "-%s\n", token ); //printing each token
        token = strtok(NULL, "\n");
    }

    // FILE *OutputFileHandle = fopen("Debug.txt", "w");
    // fwrite(Input, 1, Index, OutputFileHandle);

    return EXIT_SUCCESS;
}
