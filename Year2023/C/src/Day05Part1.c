#include "LibThomas.h"
#include "stdlib.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "stdio.h"

typedef struct _MapEntry
{
    i64 Source;
    i64 Destination;
    i64 Range;
} MapEntry;

i64* Seeds;

MapEntry* SeedToSoilMap;
MapEntry* SoilToFertilizerMap;
MapEntry* FertilizerToWaterMap;
MapEntry* WaterToLightMap;
MapEntry* LightToTemperatureMap;
MapEntry* TemperatureToHumidityMap;
MapEntry* HumidityToLocationMap;

MapEntry** MapsInOrder;

int main(void)
{
    const i32 MapCount = 7;
    
    i32 MapSizes[7] = {10,16,15,45,15,23,11};

    i32 MapStartAndEndIndices[14] = {
        3, 13,
        15,30,
        33,47,
        50,94,
        97,111,
        114,136,
        139,149
    };

    SeedToSoilMap = malloc(sizeof(*SeedToSoilMap) * MapSizes[0]);
    SoilToFertilizerMap = malloc(sizeof(*SoilToFertilizerMap) * MapSizes[1]);
    FertilizerToWaterMap = malloc(sizeof(*FertilizerToWaterMap) * MapSizes[2]);
    WaterToLightMap = malloc(sizeof(*WaterToLightMap) * MapSizes[3]);
    LightToTemperatureMap = malloc(sizeof(*LightToTemperatureMap) * MapSizes[4]);
    TemperatureToHumidityMap = malloc(sizeof(*TemperatureToHumidityMap) * MapSizes[5]);
    HumidityToLocationMap = malloc(sizeof(*HumidityToLocationMap) * MapSizes[6]);
    
    MapsInOrder = malloc(sizeof(intptr_t) * 7);
    MapsInOrder[0] = SeedToSoilMap;
    MapsInOrder[1] = SoilToFertilizerMap;
    MapsInOrder[2] = FertilizerToWaterMap;
    MapsInOrder[3] = WaterToLightMap;
    MapsInOrder[4] = LightToTemperatureMap;
    MapsInOrder[5] = TemperatureToHumidityMap;
    MapsInOrder[6] = HumidityToLocationMap;

    Seeds = malloc(sizeof(u64) * 20);

    StringArray* Input = File_ReadAllLines("Input/05.txt");
    if (Input == NULL) return EXIT_FAILURE;
    i32 PartAnswer = 0;

    String* SeedInput = Input->Contents[0];
    char SeedConversionBuffer[11] = {0};

    i32 SeedIndex = 0;
    i32 CopyFromIndex = 7;
    for(i32 Index = CopyFromIndex; Index < SeedInput->Size + 1; Index++)
    {
        char NextChar = Index < SeedInput->Size ? SeedInput->Content[Index] : ' ';
        if (NextChar == ' ')
        {
            memcpy(SeedConversionBuffer, &SeedInput->Content[CopyFromIndex], Index - CopyFromIndex);
            Seeds[SeedIndex] = atoll(SeedConversionBuffer);
            SeedIndex++;
            CopyFromIndex = Index + 1;
            memset(SeedConversionBuffer, 0, 11);
        }
    }

    i32 MapIndex = 0;
    for(i32 Index = 3; Index < 13; Index++)
    {
        String* CurrentMapLine = Input->Contents[Index];
        StringArray* Parts = String_Split(CurrentMapLine, ' ');
        assert(Parts->Count == 3);

        MapEntry* NewEntry = malloc(sizeof *NewEntry);
        NewEntry->Source = atoll(Parts->Contents[0]->Content);
        NewEntry->Destination = atoll(Parts->Contents[1]->Content);
        NewEntry->Range = atoll(Parts->Contents[2]->Content);

        SeedToSoilMap[MapIndex] = *NewEntry;
        MapIndex++;

        StringArray_Free(Parts);
    }

    printf("Part answer: %i\n", PartAnswer);
    //assert(PartAnswer == 389056265);

    return EXIT_SUCCESS;
}


