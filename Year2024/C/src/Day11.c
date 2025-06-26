#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibMem.h"
#include "LibThomas.h"
#include "LibString.h"
#include "LibNumeric.h"

String *Input = nullptr;
i32Array *ParsedInput = nullptr;

void Setup(void)
{
    MemArena_Init(1024 * 1024 * 1);
    Input = File_ReadAllText("./Input/11.txt");
    assert(Input != nullptr);

    ParsedInput = MemRequest(sizeof(*ParsedInput) * 8);
    int32_t outputIndex = 0;
    int32_t from = 0;

    for(int32_t index = 0; index < Input->Size; index++) {

        if (Input->Content[index] == ' ' || index == (Input->Size - 1)) {

            if (!StringToInt(&Input->Content[from], index - from, &ParsedInput->Data[outputIndex])) {
                Fatal("Failed to convert input to integer???");
            }

            from = index+1;
            outputIndex++;
        }

    }
}

void Part01(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    TimerStop();
    PrintTimer();

    printf("Part 01 answer: %i\n", PartAnswer);
    assert(PartAnswer == -1);
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
