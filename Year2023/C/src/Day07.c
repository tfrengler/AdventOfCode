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

    String *TestString[19] = {0};
    TestString[0] = &(String){ .Size = 7, .Content = "2345A 1" };  // 00 High card
    TestString[1] = &(String){ .Size = 7, .Content = "Q2KJJ 13" }; // 01 One pair
    TestString[2] = &(String){ .Size = 7, .Content = "Q2Q2Q 19" }; // 02 Full house
    TestString[3] = &(String){ .Size = 7, .Content = "T3T3J 17" }; // 03 Two pairs
    TestString[4] = &(String){ .Size = 7, .Content = "T3Q33 11" }; // 04 Three of a kind
    TestString[5] = &(String){ .Size = 7, .Content = "2345J 3" };  // 05 High card
    TestString[6] = &(String){ .Size = 7, .Content = "J345A 2" };  // 06 High card
    TestString[7] = &(String){ .Size = 7, .Content = "32T3K 5" };  // 07 One pair
    TestString[8] = &(String){ .Size = 7, .Content = "T55J5 29" }; // 08 Three of a kind
    TestString[9] = &(String){ .Size = 7, .Content = "KK677 7" };  // 09 Two pairs
    TestString[10] = &(String){ .Size = 7, .Content = "KTJJT 34" }; // 10 Two pairs
    TestString[11] = &(String){ .Size = 7, .Content = "QQQJA 31" }; // 11 Three of a kind
    TestString[12] = &(String){ .Size = 7, .Content = "JJJJJ 37" }; // 12 Five of a kind-
    TestString[13] = &(String){ .Size = 7, .Content = "JAAAA 43" }; // 13 Four of a kind
    TestString[14] = &(String){ .Size = 7, .Content = "AAAAJ 59" }; // 14 Four of a kind
    TestString[15] = &(String){ .Size = 7, .Content = "AAAAA 61" }; // 15 Five of a kind
    TestString[16] = &(String){ .Size = 7, .Content = "2AAAA 23" }; // 16 Four of a kind
    TestString[17] = &(String){ .Size = 7, .Content = "2JJJJ 53" }; // 17 Four of a kind
    TestString[18] = &(String){ .Size = 7, .Content = "JJJJ2 41" }; // 18 Four of a kind
    StringArray *TestInput = StringArray_Make(TestString, sizeof(TestString) / sizeof(TestString[0]));

    for (int32_t InputIndex = 0; InputIndex < TestInput->Count; InputIndex++) {

        String *CurrentInputString = TestInput->Contents[InputIndex];

        for (size_t CardLetterIndex = 0; CardLetterIndex < 5; CardLetterIndex++) {
            char CurrentCardChar = CurrentInputString->Content[CardLetterIndex];

            switch(CurrentCardChar)
            {
                case 'A':
                    CardBuffer[12]++;
                    break;
                case 'K':
                    CardBuffer[11]++;
                    break;
                case 'Q':
                    CardBuffer[10]++;
                    break;
                case 'J':
                    CardBuffer[9]++;
                    break;
                case 'T':
                    CardBuffer[8]++;
                    break;
                case '9':
                    CardBuffer[7]++;
                    break;
                case '8':
                    CardBuffer[6]++;
                    break;
                case '7':
                    CardBuffer[5]++;
                    break;
                case '6':
                    CardBuffer[4]++;
                    break;
                case '5':
                    CardBuffer[3]++;
                    break;
                case '4':
                    CardBuffer[2]++;
                    break;
                case '3':
                    CardBuffer[1]++;
                    break;
                case '2':
                    CardBuffer[0]++;
                    break;
            }

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
