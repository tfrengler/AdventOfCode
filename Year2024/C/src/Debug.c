#include "LibString.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "LibGrid.h"

int main(void)
{
    StringArray *Input = File_ReadAllLines("./Input/Debug.txt");
    assert(Input != NULL);
    assert(Input->Count == 3);

    Grid_BoundaryCrossIsNotFatal();
    GridPoint Start = { .Y = 0, .X = 0 };
    GridPoint CrossSection[4] = {0};

    Grid_GetCross(Input, CrossSection, Start.X, Start.Y);

    puts("--DONE--");

    return 0;
}
