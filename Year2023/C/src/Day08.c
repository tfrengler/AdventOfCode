#include "LibString.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    char *Name;
    char *Left;
    char *Right;
} Node;

int main(void)
{
    int32_t Part1Answer = 0;
    StringArray *TestInput = File_ReadAllLines("Input/08.txt");

    if (TestInput == 0x0) {
        exit(EXIT_FAILURE);
    }

    #define AmountOfNodes() 762
    const int32_t AmountOfNodes = AmountOfNodes();
    int32_t NodeInsertIndex = 0;
    Node Nodes[AmountOfNodes()] = { 0 };
    String *Instructions = TestInput->Contents[0];
    int32_t StartNodeIndex = 264;

    // LDN = (BRL, FLC)
    for (int32_t index = 2; index < TestInput->Count; index++) {

        char *Name = malloc(4 * sizeof(char));
        char *Left = malloc(4 * sizeof(char));
        char *Right = malloc(4 * sizeof(char));
        Name[3] = 0x0;
        Left[3] = 0x0;
        Right[3] = 0x0;

        char *Source = TestInput->Contents[index]->Content;
        memcpy(Name, Source, 3);
        memcpy(Left, &Source[7], 3);
        memcpy(Right, &Source[12], 3);

        Node NewNode = {
            .Name = Name,
            .Left = Left,
            .Right = Right
        };
        Nodes[NodeInsertIndex] = NewNode;
        NodeInsertIndex++;
    }

    int32_t NextNodeIndex = StartNodeIndex;
    int32_t NextInstructionIndex = 0;
    Part1Answer++;

    while(true) {

        Node NextNode = Nodes[NextNodeIndex];
        char *NextNodeName = 0x0;
        char NextInstruction = Instructions->Content[NextInstructionIndex];

        if (NextInstruction == 'L') {
            NextNodeName = NextNode.Left;
        }
        else if (NextInstruction == 'R') {
            NextNodeName = NextNode.Right;
        } else {
            // DEBUG_PRINT("NextInstruction is not L or R", 0x0);
            exit(EXIT_FAILURE);
        }

        if (strcmp(NextNodeName, "ZZZ") == 0) {
            break;
        }

        for (int32_t NodeSearchIndex = 0; NodeSearchIndex < (AmountOfNodes - 1); NodeSearchIndex++) {
            if (strcmp(NextNodeName, Nodes[NodeSearchIndex].Name) == 0) {
                NextNodeIndex = NodeSearchIndex;
                break;
            }
        }

        Part1Answer++;

        if (NextInstructionIndex == (Instructions->Size - 1)) {
            NextInstructionIndex = 0;
        } else {
            NextInstructionIndex++;
        }
    }

    printf("Part 1 answer: %i\n", Part1Answer);
    return EXIT_SUCCESS;
}
