#include "LibGrid.h"
#include "LibString.h"
#include "LibThomas.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* 2D GRID SUPPORT FUNCTIONS
* Represents utility functions for dealing with a 2d grid of chars as expressed by a StringArray
* The Contents of the StringArray represents the Y-axis where Y = 0 is Contents[0] (so from top left)
* The Contents[0]->Content represents the X-axis where X = 0 is Contents[0]->Content[0]
*/

// ---

static bool FatalBoundaryCross = true;
static int32_t GridWidth = 0;
static int32_t GridHeight = 0;

/* Returns true if boundary is crossed and FatalBoundaryCross is false.
 * Other it returns false (again if FatalBoundaryCross is also false).
 * In all other cases it terminates the process with an error if the boundary is crossed.
*/
static bool IsBoundaryCrossed(StringArray* input, int32_t x, int32_t y)
{
#if DEBUG()
    assert(input != NULL);
#endif

    // if (GridHeight == 0 || GridWidth == 0) {
    //     Fatal("Grid height and width not set");
    // }

    // char* ErrorMessageTemplate = "X (-2147483648) is outside the bounds of the grid (height = -2147483647)";
    char ErrorMessage[74] = {0};

    if (y > (input->Count-1) || y < 0) {
        if (!FatalBoundaryCross) return true;
        sprintf(ErrorMessage, "Y (%i) is outside the bounds of the grid (height = %i)", y, input->Count);
        Fatal(ErrorMessage);
    }

#if DEBUG()
    assert(input->Contents[y] != NULL);
#endif

    if (x > (input->Contents[y]->Size-1) || x < 0) {
        if (!FatalBoundaryCross) return true;
        sprintf(ErrorMessage, "X (%i) is outside the bounds of the grid (width = %i)", x, input->Contents[y]->Size);
        Fatal(ErrorMessage);
    }

    return false;
}

bool Grid_GetNorth(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    int32_t ComputedY = y - 1;
    if (IsBoundaryCrossed(input, x, ComputedY))
    {
        output->Value = '\0';
        output->Y = 0;
        output->X = 0;
        return false;
    }
    String *Y = input->Contents[ComputedY];

    output->Value = Y->Content[x];
    output->Y = ComputedY;
    output->X = x;

    return true;
}

bool Grid_GetSouth(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    int32_t ComputedY = y + 1;
    if (IsBoundaryCrossed(input, x, ComputedY))
    {
        output->Value = '\0';
        output->Y = 0;
        output->X = 0;
        return false;
    }
    String *Y = input->Contents[ComputedY];

    output->Value = Y->Content[x];
    output->Y = ComputedY;
    output->X = x;

    return true;
}

bool Grid_GetWest(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    int32_t ComputedX = x - 1;
    if (IsBoundaryCrossed(input, ComputedX, y))
    {
        output->Value = '\0';
        output->Y = 0;
        output->X = 0;
        return false;
    }
    String *Y = input->Contents[y];

    output->Value = Y->Content[ComputedX];
    output->Y = y;
    output->X = ComputedX;

    return true;
}

bool Grid_GetEast(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    int32_t ComputedX = x + 1;
    if (IsBoundaryCrossed(input, ComputedX, y))
    {
        output->Value = '\0';
        output->Y = 0;
        output->X = 0;
        return false;
    }
    String *Y = input->Contents[y];

    output->Value = Y->Content[ComputedX];
    output->Y = y;
    output->X = ComputedX;

    return true;
}

/*char GetSouthWest(StringArray* input, int32_t x, int32_t y)
{
    int32_t ComputedY = y + 1;
    int32_t ComputedX = x - 1;
    if (!FatalBoundaryCross && IsBoundaryCrossed(input, ComputedX, ComputedY)) return '\0';
    String *Y = input->Contents[ComputedY];
    return Y->Content[ComputedX];
}

char GetSouthEast(StringArray* input, int32_t x, int32_t y)
{
    int32_t ComputedY = y + 1;
    int32_t ComputedX = x - 1;
    if (!FatalBoundaryCross && IsBoundaryCrossed(input, ComputedX, ComputedY)) return '\0';
    String *Y = input->Contents[ComputedY];
    return Y->Content[ComputedX];
}

char GetNorthWest(StringArray* input, int32_t x, int32_t y)
{
    int32_t ComputedY = y - 1;
    int32_t ComputedX = x - 1;
    if (!FatalBoundaryCross && IsBoundaryCrossed(input, ComputedX, ComputedY)) return '\0';
    String *Y = input->Contents[ComputedY];
    return Y->Content[ComputedX];
}

char GetNorthEast(StringArray* input, int32_t x, int32_t y)
{
    int32_t ComputedY = y - 1;
    int32_t ComputedX = x + 1;
    if (!FatalBoundaryCross && IsBoundaryCrossed(input, ComputedX, ComputedY)) return '\0';
    String *Y = input->Contents[ComputedY];
    return Y->Content[ComputedX];
}*/

void Grid_GetCross(StringArray* input, GridPoint* result, int32_t x, int32_t y)
{
#if DEBUG()
    assert(input != NULL);
    assert(result != NULL);
    assert(&result[0] != NULL);
    assert(&result[1] != NULL);
    assert(&result[2] != NULL);
    assert(&result[3] != NULL);
#endif
    Grid_GetNorth(input, &result[0], x, y); // North
    Grid_GetSouth(input, &result[1], x, y); // West
    Grid_GetEast(input, &result[2], x, y); // East
    Grid_GetWest(input, &result[3], x, y); // South
}

/*
int32_t GetStar(StringArray* input, char* result, int32_t x, int32_t y)
{

}

int32_t GetBox(StringArray* input, char* result, int32_t x, int32_t y)
{

}

int32_t CheckCross(StringArray* input, char toCheckFor, int32_t x, int32_t y)
{

}

bool CheckStar(StringArray* input, char toCheckFor, int32_t x, int32_t y)
{

}

bool CheckBox(StringArray* input, char toCheckFor, int32_t x, int32_t y)
{

}
*/
void Grid_BoundaryCrossIsNotFatal(void)
{
    FatalBoundaryCross = false;
}

void Grid_BoundaryCrossIsFatal(void)
{
    FatalBoundaryCross = true;
}

void SetBoundaries(int32_t width, int32_t height)
{
    GridWidth = width;
    GridHeight = height;
}
