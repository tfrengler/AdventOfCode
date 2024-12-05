#ifndef LIB_GRID_H
#define LIB_GRID_H

#include "LibString.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct _GridPoint {
    int32_t X;
    int32_t Y;
    char Value;
    bool IsValid;
} GridPoint;

bool Grid_GetNorth(StringArray* input, GridPoint* output, int32_t x, int32_t y);
bool Grid_GetSouth(StringArray* input, GridPoint* output, int32_t x, int32_t y);
bool Grid_GetWest(StringArray* input, GridPoint* output, int32_t x, int32_t y);
bool Grid_GetEast(StringArray* input, GridPoint* output, int32_t x, int32_t y);
bool Grid_GetNorthEast(StringArray* input, GridPoint* output, int32_t x, int32_t y);
bool Grid_GetNorthWest(StringArray* input, GridPoint* output, int32_t x, int32_t y);
bool Grid_GetSouthEast(StringArray* input, GridPoint* output, int32_t x, int32_t y);
bool Grid_GetSouthWest(StringArray* input, GridPoint *output, int32_t x, int32_t y);

void Grid_GetCross(StringArray* input, GridPoint* result, int32_t x, int32_t y);
void Grid_GetStar(StringArray* input, GridPoint* result, int32_t x, int32_t y);
void Grid_GetBox(StringArray* input, GridPoint* result, int32_t x, int32_t y);

void Grid_BoundaryCrossIsNotFatal(void);
void Grid_BoundaryCrossIsFatal(void);
void SetBoundaries(int32_t width, int32_t height);

#endif
