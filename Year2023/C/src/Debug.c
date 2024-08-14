// #include "LibNumeric.h"
// #include "LibString.h"
// #include "LibThomas.h"
// #include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
// #include <string.h>
// #include <time.h>
#include <unistd.h>

typedef struct
{
    int Num;
    char Char;
} Test;

Test* func1(int32_t count)
{
    Test *ReturnData = malloc(sizeof(*ReturnData) * count);
    for (int32_t index = 0; index < count; index++) {
        Test new = { .Num = index };
        ReturnData[index] = new;
    }

    return ReturnData;
}

int main(void)
{
    Test *test = func1(10);
    return EXIT_SUCCESS;
}
