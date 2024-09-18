// #include "LibNumeric.h"
#include "LibString.h"
#include "LibThomas.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <windows.h>
#include <unistd.h>

int main(void)
{
    // SYSTEM_INFO si;
    // GetSystemInfo(&si);
    // printf("The page size for this system is %lu bytes.\n", si.dwPageSize);

    StringArray *TestInput = File_ReadAllLines("Input/Debug.txt");
    StringArray_Free(TestInput, true);
    PrintAllocations();

    puts("DONE");
    return EXIT_SUCCESS;
}
