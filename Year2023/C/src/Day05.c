#include "LibNumeric.h"
#include "LibString.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct _MapEntry {
    int64_t Source;
    int64_t Destination;
    int64_t Range;
} MapEntry;

typedef struct _SeedAndRange {
    int64_t Seed;
    int64_t Range;
} SeedAndRange;

int64_t *Seeds;

MapEntry *SeedToSoilMap;
MapEntry *SoilToFertilizerMap;
MapEntry *FertilizerToWaterMap;
MapEntry *WaterToLightMap;
MapEntry *LightToTemperatureMap;
MapEntry *TemperatureToHumidityMap;
MapEntry *HumidityToLocationMap;

MapEntry **MapsInOrder;

int64_t CalculateLocation(int64_t seed);
void Part01(void);
void Part02(void);
SeedAndRange *GetTaskInput(void);
void *CalculateLocationTask(void *_);

const int32_t MapCount = 7;
const int32_t SeedCount = 20;

int32_t MapSizes[7];
StringArray *Input;
IntegerArray *Part2Locations;

int main(void)
{
    MapSizes[0] = 10;
    MapSizes[1] = 16;
    MapSizes[2] = 15;
    MapSizes[3] = 45;
    MapSizes[4] = 15;
    MapSizes[5] = 23;
    MapSizes[6] = 11;

    int32_t MapStartAndEndIndices[14] = {
        3, 12,
        15, 30,
        33, 47,
        50, 94,
        97, 111,
        114, 136,
        139, 149
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

    Seeds = malloc(sizeof(int64_t) * SeedCount);

    Input = File_ReadAllLines("Input/05.txt");
    if (Input == NULL) return EXIT_FAILURE;

    String *SeedInput = Input->Contents[0];
    char SeedConversionBuffer[11] = { 0 };

    int32_t SeedIndex = 0;
    int64_t CopyFromIndex = 7;

    for (int64_t Index = CopyFromIndex; Index < SeedInput->Size + 1; Index++) {
        char NextChar = Index < SeedInput->Size ? SeedInput->Content[Index] : ' ';
        if (NextChar == ' ') {
            memcpy(SeedConversionBuffer, &SeedInput->Content[CopyFromIndex], Index - CopyFromIndex);
            Seeds[SeedIndex] = atoll(SeedConversionBuffer);
            SeedIndex++;
            CopyFromIndex = Index + 1;
            memset(SeedConversionBuffer, 0, 11);
        }
    }

    int32_t MapStartAndEndIndex = 0;
    for (int64_t Index = 0; Index < MapCount; Index++) {
        MapEntry *CurrentMap = MapsInOrder[Index];
        int32_t MapStart = MapStartAndEndIndices[MapStartAndEndIndex];
        int64_t MapEnd = MapStartAndEndIndices[MapStartAndEndIndex + 1] + 1;
        int32_t MapIndex = 0;

        for (int64_t Index2 = MapStart; Index2 < MapEnd; Index2++) {
            String *CurrentMapLine = Input->Contents[Index2];
            StringArray *Parts = String_Split(CurrentMapLine, ' ');
            assert(Parts->Count == 3);

            MapEntry NewEntry = {
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

    Part01();
    // Part02();

    return EXIT_SUCCESS;
}

void Part01(void)
{
    int64_t PartAnswer = LONG_LONG_MAX;
    int64_t Location = 0;

    for (int64_t Index = 0; Index < SeedCount; Index++) {
        int64_t CurrentSeed = Seeds[Index];
        Location = CalculateLocation(CurrentSeed);
        PartAnswer = Location < PartAnswer ? Location : PartAnswer;
    }

    printf("Part 1 answer: %llu\n", PartAnswer);
    assert(PartAnswer == 389056265);
    puts("Part 1 passed");
}

const int32_t ExpectedRanges = 166;
SeedAndRange *SeedsAndRanges;

// NOTE: Compile without address sanitizer or it will take forever
// At O2 with 4 threads it takes about 24 seconds
// At O0 with 4 threads it takes about 89 seconds
void Part02(void)
{
    const int64_t RangeSplit = 10000000;
    SeedsAndRanges = calloc(ExpectedRanges * sizeof(*SeedsAndRanges), sizeof(*SeedsAndRanges));

    int32_t SeedAndRangeIndex = 0;

    for (int32_t Index = 0; Index < SeedCount; Index += 2) {
        int64_t SeedStart = Seeds[Index];
        int64_t SeedRange = Seeds[Index + 1];

        if (SeedRange <= RangeSplit) {
            SeedAndRange NewEntry = {
                .Seed = SeedStart,
                .Range = SeedRange
            };
            SeedsAndRanges[SeedAndRangeIndex] = NewEntry;
            SeedAndRangeIndex++;
            continue;
        }

        int64_t Ranges = SeedRange / RangeSplit;
        int64_t Overflow = SeedRange % RangeSplit;
        int64_t RangeStart = SeedStart;

        while (Ranges > 0) {
            int64_t CurrentRange;

            if (Ranges == 1 && Overflow > 0) {
                CurrentRange = RangeSplit + Overflow;
            } else {
                CurrentRange = RangeSplit;
            }

            SeedAndRange NewEntry = {
                .Seed = RangeStart,
                .Range = CurrentRange
            };
            SeedsAndRanges[SeedAndRangeIndex] = NewEntry;
            RangeStart = RangeStart + RangeSplit + 1;

            SeedAndRangeIndex++;
            Ranges--;
        }
    }

    Part2Locations = i64Array_Make(ExpectedRanges, 0);

    int64_t NumThreads = 4;
    pthread_t Threads[NumThreads];
    time_t Start = clock();

    for (int64_t Index = 0; Index < NumThreads; Index++) {
        pthread_create(&Threads[Index], NULL, CalculateLocationTask, NULL);
        printf("Thread %zu created \n", Index);
    }

    puts("Waiting for threads to finish...");

    for (int64_t Index = 0; Index < NumThreads; Index++) {
        pthread_join(Threads[Index], NULL);
        printf("Thread %zu done \n", Index);
    }

    time_t End = clock();
    double TimeSpent = (double)(End - Start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", TimeSpent);

    int64_t Part2Answer = i64Array_Min(Part2Locations);
    printf("Part 2 answer: %llu\n", Part2Answer);
    assert(Part2Answer == 137516820);
    puts("Part 2 passed");
}

int64_t LocationIndex = 0;
static pthread_mutex_t LocationIndexLock = PTHREAD_MUTEX_INITIALIZER;

SeedAndRange *GetTaskInput(void)
{
    static pthread_mutex_t Lock = PTHREAD_MUTEX_INITIALIZER;
    static int32_t TaskIndex = 0;
    SeedAndRange *ReturnData;

    pthread_mutex_lock(&Lock);
    if (TaskIndex > ExpectedRanges) {
        ReturnData = NULL;
    } else {
        ReturnData = &SeedsAndRanges[TaskIndex];
    }
    TaskIndex++;
    pthread_mutex_unlock(&Lock);

    return ReturnData;
}

void *CalculateLocationTask(void *_)
{
    while (1) {
        SeedAndRange *TaskInput = GetTaskInput();
        if (TaskInput == NULL) return NULL;

        int64_t MinValue = LONG_MAX;
        int64_t SeedMaxExclusive = TaskInput->Seed + TaskInput->Range;
        for (int64_t Index = TaskInput->Seed; Index < SeedMaxExclusive; Index++) {
            int64_t Location = CalculateLocation(Index);
            MinValue = Location < MinValue ? Location : MinValue;
        }

        pthread_mutex_lock(&LocationIndexLock);
        Part2Locations->i64Data[LocationIndex] = MinValue;
        LocationIndex++;
        pthread_mutex_unlock(&LocationIndexLock);
    }
}

int64_t CalculateLocation(int64_t seed)
{
    int64_t ReturnData = seed;
    for (int ChainIndex = 0; ChainIndex < MapCount; ChainIndex++) {
        const MapEntry *CurrentMap = MapsInOrder[ChainIndex];

        for (int32_t MapIndex = 0; MapIndex < MapSizes[ChainIndex]; MapIndex++) {
            const MapEntry CurrentMapEntry = CurrentMap[MapIndex];

            if (ReturnData >= CurrentMapEntry.Source && ReturnData < (CurrentMapEntry.Source + CurrentMapEntry.Range)) {
                ReturnData = (CurrentMapEntry.Destination - CurrentMapEntry.Source) + ReturnData;
                break;
            }
        }
    }

    return ReturnData;
}
