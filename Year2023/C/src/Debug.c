// #include "LibNumeric.h"
#include "LibThomas.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

typedef struct _Node {
    char *Name;
    char *Left;
    char *Right;
} Node;

int main(void)
{
    #define NodeCount() 762
    const int32_t AmountOfNodes = NodeCount();
    int32_t NodeInsertIndex = 0;
    Node Nodes[NodeCount()] = { 0 };

    for (int32_t index = 0; index < AmountOfNodes; index++) {

        char *Name = Malloc(4);
        char *Left = Malloc(4);
        char *Right = Malloc(4);
        Name[3] = 0x0;
        Left[3] = 0x0;
        Right[3] = 0x0;

        memcpy(Name, "TST", 3);
        memcpy(Left, "TST", 3);
        memcpy(Right, "TST", 3);

        Node NewNode = {
            .Name = Name,
            .Left = Left,
            .Right = Right
        };
        Nodes[NodeInsertIndex] = NewNode;
        NodeInsertIndex++;
    }

    for(int32_t index = 0; index < AmountOfNodes; index++) {
        Free(Nodes[index].Name);
        Free(Nodes[index].Left);
        Free(Nodes[index].Right);
    }

    PrintAllocations();

    puts("DONE");
    return EXIT_SUCCESS;
}
