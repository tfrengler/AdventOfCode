#include "LibThomas.h"
#include "stdio.h"
#include <assert.h>
#include <stdint.h>
#include <strings.h>

typedef struct _Race {
    int64_t TimeInMS;
    int64_t BestDistance;
} Race;

int main(void)
{
    Race Part01Input[4] = {
        { .TimeInMS = 56, .BestDistance = 499 },
        { .TimeInMS = 97, .BestDistance = 2210 },
        { .TimeInMS = 77, .BestDistance = 1097 },
        { .TimeInMS = 93, .BestDistance = 1440 }
    };

    int32_t FinalAnswerPart1 = 1;
    int32_t FinalAnswerPart2 = 0;

    for (size_t Index = 0; Index < arrayCount(Part01Input); Index++) {

        int32_t WinningCombos = 0;
        Race CurrentRace = Part01Input[Index];

        for (int32_t IndexMiliseconds = 1; IndexMiliseconds < CurrentRace.TimeInMS; IndexMiliseconds++)
        {
            int64_t DistanceDone = (CurrentRace.TimeInMS - IndexMiliseconds) * IndexMiliseconds;
            if (DistanceDone > CurrentRace.BestDistance)
            {
                WinningCombos++;
            }
        }

        FinalAnswerPart1 *= WinningCombos;
    }

    printf("Part 1 answer: %i\n", FinalAnswerPart1);
    assert(FinalAnswerPart1 == 1710720);

    // Part 02

    Race Part02Input = { .TimeInMS = 56977793, .BestDistance = 499221010971440 };
    int32_t WinningCombos = 0;
    int64_t TimeInMS = Part02Input.TimeInMS / 2;

    for (int64_t IndexMiliseconds = TimeInMS; IndexMiliseconds > 1; IndexMiliseconds--)
    {
        int64_t DistanceDone = (Part02Input.TimeInMS - IndexMiliseconds) * IndexMiliseconds;
        if (DistanceDone > Part02Input.BestDistance)
        {
            WinningCombos++;
            continue;
        }

        break;
    }

    for (int64_t IndexMiliseconds = TimeInMS+1; IndexMiliseconds < Part02Input.TimeInMS; IndexMiliseconds++)
    {
        int64_t DistanceDone = (Part02Input.TimeInMS - IndexMiliseconds) * IndexMiliseconds;
        if (DistanceDone > Part02Input.BestDistance)
        {
            WinningCombos++;
            continue;
        }

        break;
    }

    FinalAnswerPart2 = WinningCombos;
    printf("Part 2 answer: %i\n", FinalAnswerPart2);
    assert(FinalAnswerPart2 == 35349468);
}
