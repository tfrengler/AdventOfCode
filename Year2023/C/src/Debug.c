#include "LibNumeric.h"
#include "LibString.h"
#include "LibThomas.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    StringArray *Input = File_ReadAllLines("Input/01.txt");
    if (Input == NULL) return EXIT_FAILURE;

    String *Test = String_Make("Test", 4);
    String_Free(Test);
    // String_Free(&Input->Contents[2]);

    StringArray_Free(Input, true);
}
