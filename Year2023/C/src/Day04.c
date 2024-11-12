#include "LibThomas.h"
#include "LibNumeric.h"
#include "LibString.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>

IntegerArray *AllCards;
int32_t Part02Answer = 0;

void ProcessWinningCards(int32_t cardId)
{
    // To prevent the recursion from overflowing, since it takes index + 1
    if (cardId >= AllCards->Size) return;

    Part02Answer++;
    int32_t CardsToTake = AllCards->i32Data[cardId];
    for (int32_t index = cardId + 1; CardsToTake > 0; index++) {
        ProcessWinningCards(index);
        CardsToTake--;
    }
}

int main(void)
{
    StringArray *Input = File_ReadAllLines("Input/04.txt");
    if (Input == NULL) return EXIT_FAILURE;

    int32_t Part01Answer = 0;
    const int32_t WinningCardCount = 10;
    const int32_t ScratchcardsPlayedCount = 25;
    AllCards = i32Array_Make(Input->Count, NULL);

    /*StringArray* Input = malloc(sizeof *Input + sizeof(String*[6]));
    Input->Count = 6;
    Input->Contents[0] = String_Make("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53", 48);
    Input->Contents[1] = String_Make("Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19", 48);
    Input->Contents[2] = String_Make("Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1", 48);
    Input->Contents[3] = String_Make("Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83", 48);
    Input->Contents[4] = String_Make("Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36", 48);
    Input->Contents[5] = String_Make("Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11", 48);*/

    for (int32_t LineIndex = 0; LineIndex < Input->Count; LineIndex++) {
        String *CurrentString = Input->Contents[LineIndex];

        int32_t WinningCards[WinningCardCount];
        int32_t WinningCardIndex = 0;

        for (int32_t Index = 10; Index < 40; Index += 3) {
            if (!StringToInt(&CurrentString->Content[Index], 2, &WinningCards[WinningCardIndex])) {
                Fatal("Failed to parse string to int32");
            }
            WinningCardIndex++;
        }

        int32_t Scratchcards[ScratchcardsPlayedCount];
        int32_t ScratchcardIndex = 0;

        for (int32_t Index = 42; Index < CurrentString->Size; Index += 3) {
            if (!StringToInt(&CurrentString->Content[Index], 2, &Scratchcards[ScratchcardIndex])) {
                Fatal("Failed to parse string to int32");
            }
            ScratchcardIndex++;
        }

        int32_t Score = 0;
        int32_t HowManyWinningCardHits = 0;

        for (int32_t Index1 = 0; Index1 < ScratchcardsPlayedCount; Index1++) {
            int32_t CurrentNumber = Scratchcards[Index1];
            for (int32_t Index2 = 0; Index2 < WinningCardCount; Index2++) {
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

    for (int32_t Index = 0; Index < Input->Count; Index++) {
        ProcessWinningCards(Index);
    }

    printf("Part 2 answer: %i\n", Part02Answer);
    assert(Part02Answer == 9997537);

    IntegerArray_Free(AllCards, false);

    return EXIT_SUCCESS;
}
