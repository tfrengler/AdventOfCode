#include "LibString.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
    struct _Node *Left;
    struct _Node *Right;
    // char Name[3];
} Node;

void ParseInput(StringArray *input)
{
    Node **Nodes = malloc(sizeof(Node) * 1000000);
    Node *Test = malloc(sizeof(Node));
    Nodes[0] = Test;
}

// uint64_t hash(char *str)
// {
//     uint64_t hash = 5381;
//     int c;

//     while ((c = *str++))
//         hash = ((hash << 5) + hash) + c;

//     return hash;
// }

int main(void)
{
    int32_t Part1Answer = 0;
    StringArray *TestInput = File_ReadAllLines("Input/08.txt");

    if (TestInput == 0x0) {
        exit(EXIT_FAILURE);
    }

    // ParseInput(TestInput);

    for (int32_t index = 2; index < TestInput->Count; index++) {

        char Buffer[4] = { 0 };
        memcpy(Buffer, TestInput->Contents[index]->Content, 3);
        int NodeAsInt = 0;

        printf("%s : %i%i%i\n", Buffer, (int)Buffer[0], (int)Buffer[1], (int)Buffer[2]);
    }

    printf("Part 1 answer: %i\n", Part1Answer);
    return EXIT_SUCCESS;
}
