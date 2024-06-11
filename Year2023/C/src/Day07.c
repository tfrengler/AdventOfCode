#include "LibNumeric.h"
#include "LibString.h"
#include "LibThomas.h"
#include "stdio.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

typedef enum {
    HandType_NONE = 0,
    HandType_FiveOfaKind = 7,
    HandType_FourOfaKind = 6,
    HandType_FullHouse = 5,
    HandType_ThreeOfaKind = 4,
    HandType_TwoPair = 3,
    HandType_OnePair = 2,
    HandType_HighCard = 1
} HandType;

typedef struct _Hand {
    HandType Type;
    int32_t Bid;
    uint8_t **Values;
    char *CardString;
} Hand;

int main(void)
{
    uint8_t CardValues[85] = { 0 };
    CardValues['A'] = 13;
    CardValues['K'] = 12;
    CardValues['Q'] = 11;
    CardValues['J'] = 10;
    CardValues['T'] = 9;
    CardValues['9'] = 8;
    CardValues['8'] = 7;
    CardValues['7'] = 6;
    CardValues['6'] = 5;
    CardValues['5'] = 4;
    CardValues['4'] = 3;
    CardValues['3'] = 2;
    CardValues['2'] = 1;

    Hand Hands[19] = { 0 };
    uint8_t CardBuffer[13] = { 0 };
    uint8_t Cards[5] = { 0 };
    int32_t Part1Answer = 0;
    int32_t HandInsertIndex = 0;

    String *TestStringX[19] = {0};
    TestStringX[0] = &(String){ .Size = 7, .Content = "2345A 1" };  // 00 High card
    TestStringX[1] = &(String){ .Size = 7, .Content = "Q2KJJ 13" }; // 01 One pair
    TestStringX[2] = &(String){ .Size = 7, .Content = "Q2Q2Q 19" }; // 02 Full house
    TestStringX[3] = &(String){ .Size = 7, .Content = "T3T3J 17" }; // 03 Two pairs
    TestStringX[4] = &(String){ .Size = 7, .Content = "T3Q33 11" }; // 04 Three of a kind
    TestStringX[5] = &(String){ .Size = 7, .Content = "2345J 3" };  // 05 High card
    TestStringX[6] = &(String){ .Size = 7, .Content = "J345A 2" };  // 06 High card
    TestStringX[7] = &(String){ .Size = 7, .Content = "32T3K 5" };  // 07 One pair
    TestStringX[8] = &(String){ .Size = 7, .Content = "T55J5 29" }; // 08 Three of a kind
    TestStringX[9] = &(String){ .Size = 7, .Content = "KK677 7" };  // 09 Two pairs
    TestStringX[10] = &(String){ .Size = 7, .Content = "KTJJT 34" }; // 10 Two pairs
    TestStringX[11] = &(String){ .Size = 7, .Content = "QQQJA 31" }; // 11 Three of a kind
    TestStringX[12] = &(String){ .Size = 7, .Content = "JJJJJ 37" }; // 12 Five of a kind-
    TestStringX[13] = &(String){ .Size = 7, .Content = "JAAAA 43" }; // 13 Four of a kind
    TestStringX[14] = &(String){ .Size = 7, .Content = "AAAAJ 59" }; // 14 Four of a kind
    TestStringX[15] = &(String){ .Size = 7, .Content = "AAAAA 61" }; // 15 Five of a kind
    TestStringX[16] = &(String){ .Size = 7, .Content = "2AAAA 23" }; // 16 Four of a kind
    TestStringX[17] = &(String){ .Size = 7, .Content = "2JJJJ 53" }; // 17 Four of a kind
    TestStringX[18] = &(String){ .Size = 7, .Content = "JJJJ2 41" }; // 18 Four of a kind
    StringArray *TestInput = StringArray_Make(TestStringX, sizeof(TestStringX) / sizeof(TestStringX[0]));

    for (int32_t InputIndex = 0; InputIndex < TestInput->Count; InputIndex++) {

        String *CurrentInputString = TestInput->Contents[InputIndex];

        for (size_t CardLetterIndex = 0; CardLetterIndex < 5; CardLetterIndex++) {
            char CurrentCardChar = CurrentInputString->Content[CardLetterIndex];

            if (CurrentCardChar == 'A')
                CardBuffer[12]++;
            else if (CurrentCardChar == 'K')
                CardBuffer[11]++;
            else if (CurrentCardChar == 'Q')
                CardBuffer[10]++;
            else if (CurrentCardChar == 'J')
                CardBuffer[9]++;
            else if (CurrentCardChar == 'T')
                CardBuffer[8]++;
            else if (CurrentCardChar == '9')
                CardBuffer[7]++;
            else if (CurrentCardChar == '8')
                CardBuffer[6]++;
            else if (CurrentCardChar == '7')
                CardBuffer[5]++;
            else if (CurrentCardChar == '6')
                CardBuffer[4]++;
            else if (CurrentCardChar == '5')
                CardBuffer[3]++;
            else if (CurrentCardChar == '4')
                CardBuffer[2]++;
            else if (CurrentCardChar == '3')
                CardBuffer[1]++;
            else if (CurrentCardChar == '2')
                CardBuffer[0]++;

            Cards[CardLetterIndex] = CardValues[(int32_t)CurrentCardChar];
        }

        int32_t Bid;
        if (!StringToInt(&CurrentInputString->Content[6], CurrentInputString->Size - 6, &Bid)) {
            Fatal("Failed to parse bid from hand into an int\n");
        }

        Hand NewHand = {
            .Type = HandType_NONE,
            .Bid = Bid
        };

        HandType HandType = HandType_NONE;
        bool AnyCountOf3 = false;
        bool AnyCountOf2 = false;
        int32_t CountsOfOne = 0;

        // Do card parsing

        memset(&CardBuffer, 0, sizeof(CardBuffer));
        memset(&Cards, 0, sizeof(Cards));
    }

    // StringArray *InputParts = File_ReadAllLines("Input/07.txt");
    // if (InputParts == NULL) return EXIT_FAILURE;
    StringArray_Free(TestInput, false);

    assert(Part1Answer == 6592);
    puts("Done");
}
