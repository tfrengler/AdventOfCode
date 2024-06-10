#include "LibNumeric.h"
#include "LibString.h"
#include "LibThomas.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

uint8_t CardValues[85] = {0};

int main(void)
{
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


    String TestString[] = {
        { .Size = 7, .Content = "2345A 1" },  // 00 High card
        { .Size = 7, .Content = "Q2KJJ 13" }, // 01 One pair
        { .Size = 7, .Content = "Q2Q2Q 19" }, // 02 Full house
        { .Size = 7, .Content = "T3T3J 17" }, // 03 Two pairs
        { .Size = 7, .Content = "T3Q33 11" }, // 04 Three of a kind
        { .Size = 7, .Content = "2345J 3" },  // 05 High card
        { .Size = 7, .Content = "J345A 2" },  // 06 High card
        { .Size = 7, .Content = "32T3K 5" },  // 07 One pair
        { .Size = 7, .Content = "T55J5 29" }, // 08 Three of a kind
        { .Size = 7, .Content = "KK677 7" },  // 09 Two pairs
        { .Size = 7, .Content = "KTJJT 34" }, // 10 Two pairs
        { .Size = 7, .Content = "QQQJA 31" }, // 11 Three of a kind
        { .Size = 7, .Content = "JJJJJ 37" }, // 12 Five of a kind-
        { .Size = 7, .Content = "JAAAA 43" }, // 13 Four of a kind
        { .Size = 7, .Content = "AAAAJ 59" }, // 14 Four of a kind
        { .Size = 7, .Content = "AAAAA 61" }, // 15 Five of a kind
        { .Size = 7, .Content = "2AAAA 23" }, // 16 Four of a kind
        { .Size = 7, .Content = "2JJJJ 53" }, // 17 Four of a kind
        { .Size = 7, .Content = "JJJJ2 41" }  // 18 Four of a kind
    };

    StringArray* TestInput = StringArray_Make(TestString, arrayCount(TestString));

    // StringArray *InputParts = File_ReadAllLines("Input/07.txt");
    // if (InputParts == NULL) return EXIT_FAILURE;
    StringArray_Free(TestInput, false);
    puts("Done");
}
