#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibThomas.h"
#include "LibString.h"
// #include "LibNumeric.h"

typedef struct {
    int32_t Position;
    int32_t Size;
    int32_t Id; // -1 indicates free block
} Block;

Block *BlockList = NULL;
int32_t BlockCount = 0;

void Setup(void)
{
    String *Input = File_ReadAllText("./Input/09.txt");

    /*String xInput = {0};
    String *Input = &xInput;
    Input->Content = "2333133121414131402";
    Input->Size = 19;*/

    for (int32_t i = 0; i < Input->Size; i = i+2) {
        BlockCount++;
        if (i == (Input->Size-1)) break;
        if (Input->Content[i+1] == '0') continue;
        BlockCount++;
    }

    BlockList = Malloc(sizeof(*BlockList) * BlockCount);

    int32_t BlockIndex = 0;
    int32_t Position = 0;
    int32_t BlockId = 0;

    for (int32_t i = 0; i < Input->Size; i = i+2) {
        BlockList[BlockIndex].Size = Input->Content[i] - '0';
        BlockList[BlockIndex].Id = BlockId;
        BlockList[BlockIndex].Position = Position;
        Position = Position + BlockList[BlockIndex].Size;
        BlockIndex++;
        BlockId++;

        if (i == (Input->Size-1)) break;
        if (Input->Content[i+1] == '0') continue;

        BlockList[BlockIndex].Id = -1;
        BlockList[BlockIndex].Size = Input->Content[i+1] - '0';
        BlockList[BlockIndex].Position = Position;
        Position = Position + BlockList[BlockIndex].Size;
        BlockIndex++;
    }

    String_Free(Input);
    // 00...111...2...333.44.5555.6666.777.888899
    // printf("Blockcount: %i\n", BlockCount);
}

void Part01(void)
{
    int64_t PartAnswer = 0;
    int32_t DiskSize = 0;
    int32_t DiskIndex = 0;

    for(int32_t i = 0; i < BlockCount; i++) {
        DiskSize += BlockList[i].Size;
    }

    Block *Disk = Malloc(sizeof(Block) * DiskSize);

    // 00...111...2...333.44.5555.6666.777.888899
    for(int32_t i = 0; i < BlockCount; i++) {
        Block CurrentBlock = BlockList[i];

        for(int32_t x = 0; x < CurrentBlock.Size; x++) {

            Disk[DiskIndex] = CurrentBlock;
            DiskIndex++;
        }
    }
    // printf("Disk size: %i\n", DiskSize);
    TimerStart();

    // Before and after:
    // 00...111...2...333.44.5555.6666.777.888899
    // 0099811188827773336446555566..............
    for(DiskIndex = (DiskSize-1); DiskIndex != -1; DiskIndex--) {
        if (Disk[DiskIndex].Id == -1) continue;

        for(int32_t freeblockIndex = 0; freeblockIndex < DiskSize; freeblockIndex++) {
            if (Disk[freeblockIndex].Id > -1) continue;
            if (freeblockIndex >= DiskIndex) break;

            Disk[freeblockIndex].Id = Disk[DiskIndex].Id;
            Disk[freeblockIndex].Position = freeblockIndex;
            Disk[DiskIndex].Id = -1;

            break;
        }
    }

    for(int32_t i = 0; i < DiskSize; i++) {
        if (Disk[i].Id == -1) continue;
        PartAnswer += Disk[i].Id * i;
    }

    // Visualize disk map
    /*for(int32_t i = 0; i < DiskSize; i++) {
        if (Disk[i].Id == -1) {
            printf(".");
            continue;
        }
        printf("%i", Disk[i].Id);
    }
    puts("");*/

    TimerStop();
    PrintTimer();

    Free(Disk);
    printf("Part 01 answer: %zu\n", PartAnswer);
    assert(PartAnswer == 6331212425418);
}

void Part02(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %i\n", PartAnswer);
    // assert(PartAnswer == -1);
}

int main(void)
{
    Setup();

    Part01();
    // Part02();

    // String_Free(Input);

    Free(BlockList);
    PrintAllocations();
    return EXIT_SUCCESS;
}
