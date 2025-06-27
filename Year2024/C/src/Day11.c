#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibMem.h"
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

String *Input = nullptr;
i32Array *ParsedInput = nullptr;
const int32_t InputCount = 8;

void Setup(void)
{
    MemArena_Init(1024 * 1024 * 1);
    Input = File_ReadAllText("./Input/11.txt");
    assert(Input != nullptr);

    ParsedInput = MemRequest(sizeof(*ParsedInput));
    ParsedInput->Data = MemRequest(sizeof(*ParsedInput->Data) * InputCount);
    ParsedInput->Capacity = 0;
    ParsedInput->Size = InputCount;

    int32_t outputIndex = 0;
    int32_t from = 0;

    for(int32_t index = 0; index <= Input->Size; index++) {

        if (Input->Content[index] == ' ' || index == Input->Size) {

            if (!StringToInt(
                    &Input->Content[from],
                    index - from,
                    &ParsedInput->Data[outputIndex])
            ) {
                Fatal("Failed to convert input to integer???");
            }

            from = index+1;
            outputIndex++;
        }
    }

    // puts("Parsed input:");
    // for(size_t index = 0; index < ParsedInput->Size; index++) {
    //     printf("[%zu] => %i\n", index, ParsedInput->Data[index]);
    // }
}

void Part01(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    int32_t stones[5000];
    size_t stoneIndex = 0;
    size_t stoneCount = ParsedInput->Size;

    for(size_t index = 0; index < ParsedInput->Size; index++) {
        stones[index] = ParsedInput->Data[index];
    }

    for(size_t blinks = 25; blinks != 0; blinks--) {

        for(stoneIndex = 0; stoneIndex < stoneCount; stoneIndex++) {
            int32_t stone = stones[stoneIndex];

            if (stone == 0) {
                stones[stoneIndex] = 1;
                continue;
            }

            char stoneAsString[20] = {0};
            itoa(stone, stoneAsString, 10);
            uint64_t stoneAsStringSize = strlen(stoneAsString);

            if (stoneAsStringSize % 2 == 0) {

                // Move all subsequent values up on
                stones[stoneIndex] = 0; // First half
                stones[stoneIndex+1] = 0; // Second half
                stoneCount++;
                stoneIndex++;

                continue;
            }

            stones[stoneIndex] = stone * 2024;
        }
    }

    TimerStop();
    PrintTimer();

    printf("Part 01 answer: %i\n", PartAnswer);
    // assert(PartAnswer == -1);
}

void Part02(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %i\n", PartAnswer);
    assert(PartAnswer == -1);
}

int main(void)
{
    Setup();

    Part01();
    // Part02();

    String_Free(Input);

    PrintAllocations();
    return EXIT_SUCCESS;
}
