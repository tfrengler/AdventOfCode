#include "LibThomas.h"
#include "stdlib.h"
#include <strings.h>

int main(void)
{
    StringArray* Input = File_ReadAllLines("src/Debug.txt");

    char Buffer[10] = {0};

    for(i32 Index = 0; Index < Input->Count; Index++)
    {
        String Current = *Input->Contents[Index];
        // loop through string
        // check if char is digit
        // add to buffer if yes
        memset(&Buffer, 0, 10);
    }

    return EXIT_SUCCESS;
}


