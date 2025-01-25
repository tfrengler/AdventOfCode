#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibMem.h"
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
int32_t DiskSize = 0;

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

    BlockList = MemRequest(sizeof(*BlockList) * BlockCount);

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

    for(int32_t i = 0; i < BlockCount; i++) {
        DiskSize += BlockList[i].Size;
    }

    String_Free(Input);
    // 00...111...2...333.44.5555.6666.777.888899
    // printf("Blockcount: %i\n", BlockCount);
}

void Part01(void)
{
    int64_t PartAnswer = 0;
    int32_t DiskIndex = 0;
    int32_t *Disk = MemRequest(sizeof(int32_t) * DiskSize);

    // 00...111...2...333.44.5555.6666.777.888899
    for(int32_t i = 0; i < BlockCount; i++) {
        Block CurrentBlock = BlockList[i];

        for(int32_t x = 0; x < CurrentBlock.Size; x++) {

            Disk[DiskIndex] = CurrentBlock.Id;
            DiskIndex++;
        }
    }
    // printf("Disk size: %i\n", DiskSize);
    TimerStart();

    // Before and after:
    // 00...111...2...333.44.5555.6666.777.888899
    // 0099811188827773336446555566..............
    int32_t FreeblockIndex = 0;
    for(DiskIndex = (DiskSize-1); DiskIndex != -1; DiskIndex--) {
        int32_t Current = Disk[DiskIndex];
        if (Current == -1) continue;

        int32_t freeblockIndex = 0;
        for(freeblockIndex = FreeblockIndex; freeblockIndex < DiskSize; freeblockIndex++) {
            if (freeblockIndex >= DiskIndex) break;
            if (Disk[freeblockIndex] > -1) continue;

            Disk[freeblockIndex] = Current;
            Disk[DiskIndex] = -1;
            FreeblockIndex = freeblockIndex;

            break;
        }
    }

    for(int32_t i = 0; i < DiskSize; i++) {
        if (Disk[i] == -1) continue;
        PartAnswer += Disk[i] * i;
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

    MemFree(Disk);
    printf("Part 01 answer: %zu\n", PartAnswer);
    assert(PartAnswer == 6331212425418);
}

void Part02(void)
{
    int64_t PartAnswer = 0;
    int32_t FreeblockStartIndex = 0;
    TimerStart();

    for(int32_t DiskIndex = (BlockCount-1); DiskIndex != -1; DiskIndex--) {
        if (BlockList[DiskIndex].Id == -1) continue;
        if (FreeblockStartIndex >= DiskIndex) break;

        for(int32_t freeblockIndex = FreeblockStartIndex; freeblockIndex < BlockCount; freeblockIndex++) {
            if (BlockList[freeblockIndex].Id > -1) continue;

            Block CurrentFreeBlock = BlockList[freeblockIndex];
            if (CurrentFreeBlock.Size < BlockList[DiskIndex].Size) continue;
            if (freeblockIndex >= DiskIndex) break;

            BlockList[DiskIndex].Position = CurrentFreeBlock.Position;
            BlockList[freeblockIndex].Size -= BlockList[DiskIndex].Size;
            BlockList[freeblockIndex].Position += BlockList[DiskIndex].Size;

            if (CurrentFreeBlock.Size == 0) {
                FreeblockStartIndex++;
            }

            break;
        }
    }

    for(int32_t i = 0; i < BlockCount; i++) {
        if (BlockList[i].Id == -1) continue;
        int32_t PositionIncrement = BlockList[i].Size - 1;
        while(PositionIncrement != -1)
        {
            PartAnswer += BlockList[i].Id * (BlockList[i].Position + PositionIncrement);
            PositionIncrement--;
        }
    }

    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %zu\n", PartAnswer);
    assert(PartAnswer == 6363268339304);
}

int main(void)
{
    Setup();

    Part01();
    Part02();

    MemFree(BlockList);
    // PrintAllocations();
    return EXIT_SUCCESS;
}
