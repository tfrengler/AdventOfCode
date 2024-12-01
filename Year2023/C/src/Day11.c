#include "LibString.h"
#include "LibThomas.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct {
    int32_t X;
    int32_t Y;
} Galaxy;

int main(void)
{
    StringArray *Input = File_ReadAllLines("Input/11.txt");
    if (Input == NULL) {
        Fatal("Unable to read test input");
    }

    int32_t Answer = 0;
    int32_t NumGalaxies = 0;
    Galaxy* StarMapBeforeExpansion = NULL;
    Galaxy* StarMapAfterExpansion = NULL;

    // Determining number of galaxies so we can pre-alloc the space
    for(int32_t yIndex = 0; yIndex < Input->Count; yIndex++)
    {
        String* CurrentLine = Input->Contents[yIndex];
        for(int32_t xIndex = 0; xIndex < CurrentLine->Size; xIndex++)
        {
            if (CurrentLine->Content[xIndex] == '#')
            {
                NumGalaxies++;
            }
        }
    }

    size_t StarMapByteSize = sizeof(Galaxy) * NumGalaxies;
    StarMapBeforeExpansion = Malloc(StarMapByteSize);
    StarMapAfterExpansion = Malloc(StarMapByteSize);

    int32_t StarMapIndex = 0;
    int32_t yExpansionFactor = 0;

    // First pass. Creating galaxies including y-axis expansion
    for(int32_t yIndex = 0; yIndex < Input->Count; yIndex++)
    {
        String* CurrentLine = Input->Contents[yIndex];
        int32_t EmptyCount = 0;

        for(int32_t xIndex = 0; xIndex < CurrentLine->Size; xIndex++)
        {
            if (CurrentLine->Content[xIndex] == '.')
            {
                EmptyCount++;
                continue;;
            }

            StarMapBeforeExpansion[StarMapIndex] = (Galaxy){ .X = xIndex, .Y = yIndex + yExpansionFactor };
            StarMapIndex++;
        }

        if (EmptyCount == CurrentLine->Size)
        {
            yExpansionFactor++;
        }
    }

    memcpy(StarMapAfterExpansion, StarMapBeforeExpansion, StarMapByteSize);

    // Second pass, calculating the x-axis expansion
    for(int32_t xIndex = 0; xIndex < Input->Contents[0]->Size; xIndex++)
    {
        int32_t EmptyCount = 0;

        for(int32_t yIndex = 0; yIndex < Input->Count; yIndex++)
        {
            if (Input->Contents[yIndex]->Content[xIndex] == '.')
            {
                EmptyCount++;
            }
        }

        if (EmptyCount != Input->Count)
        {
            continue;
        }

        for(int32_t galaxyIndex = 0; galaxyIndex < NumGalaxies; galaxyIndex++)
        {
            Galaxy Current = StarMapBeforeExpansion[galaxyIndex];
            if (Current.X > xIndex)
            {
                int CurrentX = StarMapAfterExpansion[galaxyIndex].X;
                StarMapAfterExpansion[galaxyIndex].X = CurrentX + 1;
            }
        }
    }
    // Calculating the answer
    for(int32_t outerIndex = 0; outerIndex < NumGalaxies; outerIndex++)
    {
        Galaxy Current = StarMapAfterExpansion[outerIndex];
        for(int32_t innerIndex = outerIndex+1; innerIndex < NumGalaxies; innerIndex++)
        {
            Galaxy Partner = StarMapAfterExpansion[innerIndex];
            Answer += abs(Current.X - Partner.X) + abs(Current.Y - Partner.Y);
        }
    }

    Free(StarMapBeforeExpansion);
    Free(StarMapAfterExpansion);
    StringArray_Free(Input, true);

    // PrintAllocations();
    printf("Part 1 answer: %i\n", Answer);
    assert(Answer == 9233514);
}
