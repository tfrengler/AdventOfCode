#include "LibGrid.h"
#include "LibString.h"
#include "LibThomas.h"
#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* 2D GRID SUPPORT FUNCTIONS
* Represents utility functions for dealing with a 2d grid of chars as expressed
* by a StringArray where 0:0 is the top left corner.
* The StringArray->Contents represents the Y-axis where Y = 0 is Contents[0]
* The Contents[0]->Content represents the X-axis where X = 0 is Contents[0]->Content[0]
*/

// ---

static bool FatalBoundaryCross = true;

/* Returns true if boundary is crossed and FatalBoundaryCross is false.
 * Other it returns false (again if FatalBoundaryCross is also false).
 * In all other cases it terminates the process with an error if the boundary is crossed.
*/
static bool _IsBoundaryCrossed(StringArray* input, int32_t x, int32_t y)
{
#if DEBUG()
    assert(input != NULL);
#endif

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

static bool _GetGridPoint(StringArray *input, GridPoint *output, int32_t x, int32_t y)
{
    if (_IsBoundaryCrossed(input, x, y))
    {
        output->Value = '\0';
        output->Y = -1;
        output->X = -1;
        output->IsValid = false;

        return false;
    }

    String *Y = input->Contents[y];

    output->Value = Y->Content[x];
    output->Y = y;
    output->X = x;
    output->IsValid = true;

    return true;
}

/* ******************** NORTH - SOUTH - EAST - WEST ******************** */

bool Grid_GetNorth(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    y--;
    return _GetGridPoint(input, output, x, y);
}

bool Grid_GetSouth(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    y++;
    return _GetGridPoint(input, output, x, y);
}

bool Grid_GetWest(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    x--;
    return _GetGridPoint(input, output, x, y);
}

bool Grid_GetEast(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    x++;
    return _GetGridPoint(input, output, x, y);
}

/* ******************** DIAGONALS ******************** */

bool Grid_GetNorthEast(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    y--; x++;
    return _GetGridPoint(input, output, x, y);
}

bool Grid_GetNorthWest(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    y--; x--;
    return _GetGridPoint(input, output, x, y);
}

bool Grid_GetSouthEast(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    y++; x++;
    return _GetGridPoint(input, output, x, y);
}

bool Grid_GetSouthWest(StringArray* input, GridPoint* output, int32_t x, int32_t y)
{
    y++; x--;
    return _GetGridPoint(input, output, x, y);
}

/* ******************** SPECIALS ******************** */

void Grid_GetCross(StringArray* input, GridPoint* result, int32_t x, int32_t y)
{
#if DEBUG()
    assert(input != NULL);
    assert(result != NULL);
#endif
    Grid_GetNorth(input, &result[0], x, y); // North
    Grid_GetEast(input, &result[1], x, y); // East
    Grid_GetSouth(input, &result[2], x, y); // South
    Grid_GetWest(input, &result[3], x, y); // West
}

void Grid_GetStar(StringArray* input, GridPoint* result, int32_t x, int32_t y)
{
#if DEBUG()
    assert(input != NULL);
    assert(result != NULL);
#endif
    Grid_GetNorthWest(input, &result[0], x, y); // NW
    Grid_GetNorthEast(input, &result[1], x, y); // NE
    Grid_GetSouthEast(input, &result[2], x, y); // SE
    Grid_GetSouthWest(input, &result[3], x, y); // SW
}

void Grid_GetBox(StringArray* input, GridPoint* result, int32_t x, int32_t y)
{
#if DEBUG()
    assert(input != NULL);
    assert(result != NULL);
#endif
    Grid_GetNorth(input, &result[0], x, y); // N
    Grid_GetNorthEast(input, &result[1], x, y); // NE
    Grid_GetEast(input, &result[2], x, y); // E
    Grid_GetSouthEast(input, &result[3], x, y); // SE
    Grid_GetSouth(input, &result[4], x, y); // S
    Grid_GetSouthWest(input, &result[5], x, y); // SW
    Grid_GetWest(input, &result[6], x, y); // W
    Grid_GetNorthWest(input, &result[7], x, y); // NW
}

void Grid_BoundaryCrossIsNotFatal(void)
{
    FatalBoundaryCross = false;
}

void Grid_BoundaryCrossIsFatal(void)
{
    FatalBoundaryCross = true;
}
