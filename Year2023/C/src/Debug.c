// #include "LibNumeric.h"
// #include "LibString.h"
#include "LibThomas.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <windows.h>
#include <unistd.h>

typedef struct _TestStruct1 {
    int64_t TheLong;
    int32_t TheNormal;
    int16_t TheShort;
} TestStruct1;

typedef struct _TestStruct2 {
    char TheChar;
} TestStruct2;

int main(void)
{
    puts("START");
    TestStruct1* MyStruct1 = Malloc(17);
    MyStruct1->TheLong = 64;
    MyStruct1->TheNormal = 32;
    MyStruct1->TheShort = 16;

    char* MyStruct2 = (char*)(byte*)MyStruct1+16;
    memset(MyStruct2, 'X', 1);

    printf("Our long: %zi\n", *(int64_t*)MyStruct1);
    printf("Our int: %i\n", *(int32_t*)((byte*)MyStruct1+8));
    printf("Our short: %i\n", *(int16_t*)((byte*)MyStruct1+12));
    printf("Our short: %c\n", *(char*)((byte*)MyStruct1+16));

    Free(MyStruct1);
    puts("END");
    return EXIT_SUCCESS;
}
