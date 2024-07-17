// #include "LibNumeric.h"
#include "LibString.h"
#include "LibThomas.h"
#include "LibString.h"
#include "stdio.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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
    char Cards[5];
} Hand;

int32_t DetermineCardValue(const char input)
{
    switch (input)
    {
        case 'A': return 13;
        case 'K': return 12;
        case 'Q': return 11;
        case 'J': return 10;
        case 'T': return 9;
        case '9': return 8;
        case '8': return 7;
        case '7': return 6;
        case '6': return 5;
        case '5': return 4;
        case '4': return 3;
        case '3': return 2;
        case '2': return 1;
        default: return 0;
    }
}

Hand* ParseCardIntoHand(const String *input)
{
    int32_t CardCount[13] = { 0 }; 
    
    for (int32_t index = 0; index < 5; index++) {

        char NextChar = input->Content[index];

        switch (NextChar) {
            case 'A': CardCount[0]++; break;
            case 'K': CardCount[1]++; break;
            case 'Q': CardCount[2]++; break;
            case 'J': CardCount[3]++; break;
            case 'T': CardCount[4]++; break;
            case '9': CardCount[5]++; break;
            case '8': CardCount[6]++; break;
            case '7': CardCount[7]++; break;
            case '6': CardCount[8]++; break;
            case '5': CardCount[9]++; break;
            case '4': CardCount[10]++; break;
            case '3': CardCount[11]++; break;
            case '2': CardCount[12]++; break;
        }
    }

    Hand *ReturnData = malloc(sizeof(Hand) + sizeof(char[5]));
    ReturnData->Bid = 0;
    ReturnData->Type = HandType_NONE;

    bool TwoOfAKind = false;
    bool ThreeOfAKind = false;
    int32_t Singles = 0;

    for (int32_t index = 0; index < 13; index++) {
        int32_t Current = CardCount[index];

        if (Current == 5) {
            ReturnData->Type = HandType_FiveOfaKind;
            break;
        }

        if (Current == 4) {
            ReturnData->Type = HandType_FourOfaKind;
            break;
        }

        if (Current == 1) {
            Singles++;
            if (Singles == 5) {
                ReturnData->Type = HandType_HighCard;
                break;
            }
        }

        if (Current == 3) {

            if (TwoOfAKind) {
                ReturnData->Type = HandType_FullHouse;
                break;
            }

            ThreeOfAKind = true;
        }

        if (Current == 2) {

            if (TwoOfAKind) {
                ReturnData->Type = HandType_TwoPair;
                break;
            }

            if (ThreeOfAKind) {
                ReturnData->Type = HandType_FullHouse;
                break;
            }

            TwoOfAKind = true;
        }

        if (ThreeOfAKind && Singles == 2) {
            ReturnData->Type = HandType_ThreeOfaKind;
            break;
        }

        if (TwoOfAKind && Singles == 3) {
            ReturnData->Type = HandType_OnePair;
            break;
        }
    }

#if DEBUG()
    assert(ReturnData->Type != HandType_NONE);
#endif

    int32_t Bid = 0;
    for(int32_t index = 6; index < input->Size; index++) {
        Bid = Bid * 10;
        Bid = Bid + (input->Content[index] - '0');
    }

    ReturnData->Bid = Bid;
    memcpy(ReturnData->Cards, input->Content, 5);

    return ReturnData;
}

int SortHands(const void *elem1, const void *elem2)
{
    Hand *Value1 = (Hand*)elem1;
    Hand *Value2 = (Hand*)elem2;

    if (Value1->Type < Value2->Type) return -1;
    if (Value1->Type > Value2->Type) return 1;

    for (int Index = 0; Index < 5; Index++)
    {
        if (DetermineCardValue(Value1->Cards[Index]) < DetermineCardValue(Value2->Cards[Index])) return -1;
        if (DetermineCardValue(Value1->Cards[Index]) > DetermineCardValue(Value2->Cards[Index])) return 1;
    }

    return 0;
}

int main(void)
{
    int32_t Part1Answer = 0;
    
    /*String *TestString[19] = {0};
    TestString[0] = &(String){ .Size = 8, .Content = "JJJJJ 37" }; // 50: Five of a kind
    TestString[1] = &(String){ .Size = 8, .Content = "AAAAA 61" }; // 65: Five of a kind
    TestString[2] = &(String){ .Size = 8, .Content = "JAAAA 43" }; // 62: Four of a kind
    TestString[3] = &(String){ .Size = 8, .Content = "AAAAJ 59" }; // 62: Four of a kind
    TestString[4] = &(String){ .Size = 8, .Content = "2AAAA 23" }; // 53: Four of a kind
    TestString[5] = &(String){ .Size = 8, .Content = "2JJJJ 53" }; // 41: Four of a kind
    TestString[6] = &(String){ .Size = 8, .Content = "JJJJ2 41" }; // 41: Four of a kind
    TestString[7] = &(String){ .Size = 8, .Content = "Q2Q2Q 19" }; // 35: Full house
    TestString[8] = &(String){ .Size = 8, .Content = "T3Q33 11" }; // 26: Three of a kind
    TestString[9] = &(String){ .Size = 8, .Content = "T55J5 29" }; // 31: Three of a kind
    TestString[10] = &(String){ .Size = 8, .Content = "QQQJA 31" };// 56: Three of a kind
    TestString[11] = &(String){ .Size = 8, .Content = "T3T3J 17" };// 32: Two pairs
    TestString[12] = &(String){ .Size = 7, .Content = "KK677 7" }; // 41: Two pairs
    TestString[13] = &(String){ .Size = 8, .Content = "KTJJT 34" };// 50: Two pairs
    TestString[14] = &(String){ .Size = 8, .Content = "Q2KJJ 13" };// 44: One pair
    TestString[15] = &(String){ .Size = 7, .Content = "32T3K 5" }; // 26: One pair
    TestString[16] = &(String){ .Size = 7, .Content = "2345A 1" }; // 23: High card
    TestString[17] = &(String){ .Size = 7, .Content = "2345J 3" }; // 20: High card
    TestString[18] = &(String){ .Size = 7, .Content = "J345A 2" }; // 32: High card
    StringArray *TestInput = StringArray_Make(TestString, sizeof(TestString) / sizeof(TestString[0]));*/

    StringArray *TestInput = File_ReadAllLines("Input/07.txt");

    Hand Hands[TestInput->Count];
    memset(Hands, 0, sizeof(Hand));

#if DEBUG()
    assert(sizeof(Hands) / sizeof(Hands[0]) == TestInput->Count);
#endif

    // PART 01
    for (int32_t index = 0; index < TestInput->Count; index++) {
        
        String *CurrentInput = TestInput->Contents[index];
        Hand *TheHand = ParseCardIntoHand(CurrentInput);
        Hands[index] = *TheHand;
    }

    qsort(Hands, TestInput->Count, sizeof(Hands[0]), SortHands);

    for(int Index = TestInput->Count - 1; Index != -1; Index--)
    {
        Hand CurrentHand = Hands[Index];
        Part1Answer += CurrentHand.Bid * (Index + 1);
    }
    // END PART 01

    StringArray_Free(TestInput, true);

    printf("Part 01 answer: %i\n", Part1Answer);
    assert(Part1Answer == 246424613);
    // assert(Part1Answer == 6592);
}
