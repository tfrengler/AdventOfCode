#include "LibThomas.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>

IntegerArray *AllCards;
i32 Part02Answer = 0;

void ProcessWinningCards(i32 cardId)
{
    // To prevent the recursion from overflowing, since it takes index + 1
    if (cardId >= AllCards->Size) return;

    Part02Answer++;
    i32 CardsToTake = AllCards->i32Data[cardId];
    for (i32 index = cardId + 1; CardsToTake > 0; index++) {
        ProcessWinningCards(index);
        CardsToTake--;
    }
}

int main(void)
{
    StringArray *Input = File_ReadAllLines("Input/04.txt");
    if (Input == NULL) return EXIT_FAILURE;

    i32 Part01Answer = 0;
    const i32 WinningCardCount = 10;
    const i32 ScratchcardsPlayedCount = 25;
    AllCards = i32Array_Make(Input->Count, NULL);

    /*StringArray* Input = malloc(sizeof *Input + sizeof(String*[6]));
    Input->Count = 6;
    Input->Contents[0] = String_Make("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53", 48);
    Input->Contents[1] = String_Make("Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19", 48);
    Input->Contents[2] = String_Make("Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1", 48);
    Input->Contents[3] = String_Make("Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83", 48);
    Input->Contents[4] = String_Make("Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36", 48);
    Input->Contents[5] = String_Make("Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11", 48);*/

    for (i32 LineIndex = 0; LineIndex < Input->Count; LineIndex++) {
        String *CurrentString = Input->Contents[LineIndex];
        char CardIdBuffer[4] = { 0 };
        char CardBuffer[3] = { 0 };

        memcpy(CardIdBuffer, &CurrentString->Content[5], 3);
        // i32 CardId = atoi(CardIdBuffer);
        //  printf("Card id: %i\n", CardId);

        i32 *WinningCards = malloc(sizeof *WinningCards * WinningCardCount);
        i32 WinningCardIndex = 0;
        for (i32 Index = 10; Index < 40; Index += 3) {
            memcpy(CardBuffer, &CurrentString->Content[Index], 2);
            WinningCards[WinningCardIndex] = atoi(CardBuffer);
            WinningCardIndex++;
        }

        i32 *Scratchcards = malloc(sizeof *Scratchcards * ScratchcardsPlayedCount);
        i32 ScratchcardIndex = 0;
        for (i32 Index = 42; Index < CurrentString->Size; Index += 3) {
            memcpy(CardBuffer, &CurrentString->Content[Index], 2);
            Scratchcards[ScratchcardIndex] = atoi(CardBuffer);
            ScratchcardIndex++;
        }

        i32 Score = 0;
        i32 HowManyWinningCardHits = 0;
        for (i32 Index1 = 0; Index1 < ScratchcardsPlayedCount; Index1++) {
            i32 CurrentNumber = Scratchcards[Index1];
            for (i32 Index2 = 0; Index2 < WinningCardCount; Index2++) {
                if (WinningCards[Index2] == CurrentNumber) {
                    Score = Score == 0 ? 1 : Score * 2;
                    HowManyWinningCardHits++;
                }
            }
        }

        Part01Answer += Score;
        AllCards->i32Data[LineIndex] = HowManyWinningCardHits;
    }

    printf("Part 1 answer: %i\n", Part01Answer);
    assert(Part01Answer == 26218);

    for (i32 Index = 0; Index < Input->Count; Index++) {
        ProcessWinningCards(Index);
    }

    printf("Part 2 answer: %i\n", Part02Answer);
    assert(Part02Answer == 9997537);

    IntegerArray_Free(AllCards);

    return EXIT_SUCCESS;
}
