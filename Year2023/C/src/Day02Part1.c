#include "LibThomas.h"
#include "stdlib.h"
#include <assert.h>
#include <strings.h>
#include "stdio.h"

i32 i32Array_Max(const i32Array* input)
{
    if (input == NULL) return 0;
    if (input->Size == 0) return 0;
    if (input->Size == 1) return input->Value[0];

    i32 ReturnData = 0;
    for(i32 Index = 0; Index < input->Size; Index++)
    {
        if (input->Value[Index] > ReturnData)
        {
            ReturnData = input->Value[Index];
        }
    }
    return ReturnData;
}

int main(void)
{
    //char* TestInput = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\nGame 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\nGame 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\nGame 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\nGame 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";

    i32 TestNumbers[] = {2,4,5,8,1,4,3};
    i32Array Test = {7, TestNumbers};

    printf("What is max: %i", i32Array_Max(&Test));
}
