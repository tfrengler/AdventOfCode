#include "LibThomas.h"
#include "stdlib.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "stdio.h"

typedef struct _MapEntry
{
    u64 Source;
    u64 Destination;
    u64 Range;
} MapEntry;

typedef struct _SeedAndRange
{
    u64 Seed;
    u64 Range;
} SeedAndRange;

i64* Seeds;

MapEntry* SeedToSoilMap;
MapEntry* SoilToFertilizerMap;
MapEntry* FertilizerToWaterMap;
MapEntry* WaterToLightMap;
MapEntry* LightToTemperatureMap;
MapEntry* TemperatureToHumidityMap;
MapEntry* HumidityToLocationMap;

MapEntry** MapsInOrder;

u64 CalculateLocation(u64 seed);
void Part01(void);
void Part02(void);
SeedAndRange* GetTaskInput(void);
void* CalculateLocationTask(void* _);

const i32 MapCount = 7;
const i32 SeedCount = 20;

i32 MapSizes[7];
StringArray* Input;
u64Array* Part2Locations;

int main(void)
{
    MapSizes[0] = 10;
    MapSizes[1] = 16;
    MapSizes[2] = 15;
    MapSizes[3] = 45;
    MapSizes[4] = 15;
    MapSizes[5] = 23;
    MapSizes[6] = 11;

    i32 MapStartAndEndIndices[14] = {
        3, 12,
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

    Seeds = malloc(sizeof(u64) * SeedCount);

    Input = File_ReadAllLines("Input/05.txt");
    if (Input == NULL) return EXIT_FAILURE;

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

    i32 MapStartAndEndIndex = 0;
    for(i32 Index = 0; Index < MapCount; Index++)
    {
        MapEntry* CurrentMap = MapsInOrder[Index];
        i32 MapStart = MapStartAndEndIndices[MapStartAndEndIndex];
        i32 MapEnd = MapStartAndEndIndices[MapStartAndEndIndex+1] + 1;
        i32 MapIndex = 0;

        for(i32 Index2 = MapStart; Index2 < MapEnd; Index2++)
        {
            String* CurrentMapLine = Input->Contents[Index2];
            StringArray* Parts = String_Split(CurrentMapLine, ' ');
            assert(Parts->Count == 3);

            MapEntry NewEntry =
            {
                .Destination = atoll(Parts->Contents[0]->Content),
                .Source = atoll(Parts->Contents[1]->Content),
                .Range = atoll(Parts->Contents[2]->Content),
            };
            CurrentMap[MapIndex] = NewEntry;

            MapIndex++;

            StringArray_Free(Parts);
        }

        MapStartAndEndIndex += 2;
    }

    // Part01();
    Part02();

    return EXIT_SUCCESS;
}

void Part01(void)
{
    u64 PartAnswer = LONG_LONG_MAX;
    u64 Location = 0;

    for(i32 Index = 0; Index < SeedCount; Index++)
    {
        u64 CurrentSeed = Seeds[Index];
        Location = CalculateLocation(CurrentSeed);
        PartAnswer = Location < PartAnswer ? Location : PartAnswer;
    }

    printf("Part answer: %llu\n", PartAnswer);
    assert(PartAnswer == 389056265);
}

const i32 ExpectedRanges = 166;
SeedAndRange* SeedsAndRanges;

void Part02(void)
{
    const u64 RangeSplit = 10000000;
    SeedsAndRanges = calloc(176 * sizeof(*SeedsAndRanges), sizeof(*SeedsAndRanges));

    i32 SeedAndRangeIndex = 0;

    for(i32 Index = 0; Index < SeedCount; Index += 2)
    {
        u64 SeedStart = Seeds[Index];
        u64 SeedRange = Seeds[Index+1];

        if (SeedRange <= RangeSplit)
        {
            SeedAndRange NewEntry =
            {
                .Seed = SeedStart,
                .Range = SeedRange
            };
            SeedsAndRanges[SeedAndRangeIndex] = NewEntry;
            SeedAndRangeIndex++;
            continue;
        }

        u64 Ranges = SeedRange / RangeSplit;
        u64 Overflow = SeedRange % RangeSplit;
        u64 RangeStart = SeedStart;

        while(Ranges > 0)
        {
            u64 CurrentRange;

            if (Ranges == 1 && Overflow > 0)
            {
                CurrentRange = RangeSplit + Overflow;
            }
            else
            {
                CurrentRange = RangeSplit;
            }

            SeedAndRange NewEntry =
            {
                .Seed = RangeStart,
                .Range = CurrentRange
            };
            SeedsAndRanges[SeedAndRangeIndex] = NewEntry;
            RangeStart = RangeStart + RangeSplit + 1;

            SeedAndRangeIndex++;
            Ranges--;
        }
    }

    Part2Locations = malloc(sizeof(u64Array) * ExpectedRanges);
    Part2Locations->Size = ExpectedRanges;
    Part2Locations->Value = malloc(ExpectedRanges * sizeof(u64));

    pthread_t Thread1, Thread2, Thread3, Thread4;

    pthread_create(&Thread1, NULL, CalculateLocationTask, NULL);
    pthread_create(&Thread2, NULL, CalculateLocationTask, NULL);
    pthread_create(&Thread3, NULL, CalculateLocationTask, NULL);
    pthread_create(&Thread4, NULL, CalculateLocationTask, NULL);
    pthread_join(Thread1, NULL);
    pthread_join(Thread2, NULL);
    pthread_join(Thread3, NULL);
    pthread_join(Thread4, NULL);

    u64 Part2Answer = u64Array_Min(Part2Locations);
    printf("Part 2 answer: %llu\n", Part2Answer);
    assert(Part2Answer == 137516820);
}

u64 LocationIndex = 0;
static pthread_mutex_t LocationIndexLock = PTHREAD_MUTEX_INITIALIZER;

SeedAndRange* GetTaskInput(void)
{
    static pthread_mutex_t Lock = PTHREAD_MUTEX_INITIALIZER;
    static i32 TaskIndex = 0;
    SeedAndRange* ReturnData;

    pthread_mutex_lock(&Lock);
    if (TaskIndex > ExpectedRanges)
    {
        ReturnData = NULL;
    }
    else
    {
        ReturnData = &SeedsAndRanges[TaskIndex];
    }
    TaskIndex++;
    pthread_mutex_unlock(&Lock);

    return ReturnData;
}

void* CalculateLocationTask(void* _)
{
    while(1)
    {
        SeedAndRange* TaskInput = GetTaskInput();
        if (TaskInput == NULL) return NULL;

        u64 MinValue = LONG_LONG_MAX;
        u64 SeedMaxExclusive = TaskInput->Seed + TaskInput->Range;
        for(u64 Index = TaskInput->Seed; Index < SeedMaxExclusive; Index++)
        {
            u64 Location = CalculateLocation(Index);
            MinValue = Location < MinValue ? Location : MinValue;
        }

        pthread_mutex_lock(&LocationIndexLock);

        LocationIndex++;
    }
}

u64 CalculateLocation(u64 seed)
{
    u64 ReturnData = seed;
    for (int ChainIndex = 0; ChainIndex < MapCount; ChainIndex++)
    {
        MapEntry* CurrentMap = MapsInOrder[ChainIndex];

        for (i32 MapIndex = 0; MapIndex < MapSizes[ChainIndex]; MapIndex++)
        {
            MapEntry CurrentMapEntry = CurrentMap[MapIndex];

            if (ReturnData >= CurrentMapEntry.Source && ReturnData < (CurrentMapEntry.Source + CurrentMapEntry.Range))
            {
                ReturnData = (CurrentMapEntry.Destination - CurrentMapEntry.Source) + ReturnData;
                break;
            }
        }
    }

    return ReturnData;
}
