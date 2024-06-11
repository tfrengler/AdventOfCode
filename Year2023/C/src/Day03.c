#include "LibNumeric.h"
#include "LibThomas.h"
#include "LibString.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>

typedef struct _Gear {
    int64_t SymbolPosition;
    int32_t Number;
} Gear;

bool IsSymbol(char input)
{
    // Can't use a single range because dot (.) is NOT a symbol and is at 46
    // Can't do "an anything not 46"-check either because we might be next to another number...
    if (input > 31 && input < 46) return true;
    if (input == 47) return true;
    if (input > 57 && input < 65) return true;

    return false;
}

int main(void)
{
    StringArray *InputParts = File_ReadAllLines("Input/03.txt");

    // TEST DATA:
    // char* TestInput = "467..114..\n...*......\n..35..633.\n......#...\n617*......\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664.598..";
    // String *TestString = String_Make(TestInput, 109);
    // StringArray *InputParts = String_Split(TestString, '\n');
    // String_Free(TestString);

    if (InputParts == NULL) Fatal("Failed to read input\n");
    assert(InputParts->Count == 140);

    int32_t Part1Answer = 0;
    int32_t Part2Answer = 0;

    Gear Gears[700] = {0};
    const int32_t GearCount = arrayCount(Gears);
    int32_t GearIndex = 0;

    for (int32_t LineIndex = 0; LineIndex < InputParts->Count; LineIndex++) {
        String *CurrentLine = InputParts->Contents[LineIndex];
        char *CurrentString = CurrentLine->Content;

        String *LinesToCheck[3] = { 0 };
        if (LineIndex > 0) LinesToCheck[0] = InputParts->Contents[LineIndex - 1];
        LinesToCheck[1] = CurrentLine;
        if (LineIndex < InputParts->Count - 1) LinesToCheck[2] = InputParts->Contents[LineIndex + 1];

        for (int32_t StringIndex = 0; StringIndex < CurrentLine->Size;) {
            if (CurrentString[StringIndex] < 48 || CurrentString[StringIndex] > 57) {
                StringIndex++;
                continue;
            }

            char NumberBuffer[4] = { 0 };
            memcpy(&NumberBuffer, &CurrentString[StringIndex], 3);

            int32_t Number;
            if (!StringToInt(NumberBuffer, sizeof(NumberBuffer) - 1, &Number)) {
                Fatal("Failed to parse NumberBuffer to int\n");
            }
            int32_t DigitsToCheck = 0;
            int32_t NumberStartPosition = StringIndex;
            int32_t SymbolPositionsLeftToCheck = 0;

            if (Number < 10) {
                DigitsToCheck = 3;
                StringIndex += 2;
            } else if (Number < 100) {
                DigitsToCheck = 4;
                StringIndex += 3;
            } else {
                DigitsToCheck = 5;
                StringIndex += 4;
            }

            // To account for numbers against the edges. In that case check one less digit (column)
            if (NumberStartPosition == 0 || (CurrentLine->Size - DigitsToCheck) < DigitsToCheck) {
                DigitsToCheck--;
            }

            int32_t LinesToCheckIndex = 0;
            while (LinesToCheckIndex < 3) {
                String *LineToCheck = LinesToCheck[LinesToCheckIndex];
                if (LineToCheck == NULL) {
                    LinesToCheckIndex++;
                    continue;
                }

                bool SymbolFound = false;
                SymbolPositionsLeftToCheck = DigitsToCheck;
                int32_t SymbolCheckIndex = NumberStartPosition == 0 ? NumberStartPosition : NumberStartPosition - 1;

                while (SymbolPositionsLeftToCheck > 0) {
                    char PotentialSymbol = LineToCheck->Content[SymbolCheckIndex];
                    SymbolFound = IsSymbol(PotentialSymbol);
                    if (SymbolFound) {
                        Part1Answer += Number;

                        if (PotentialSymbol == '*') {

                            Gear CurrentGear = {
                                .SymbolPosition = (int64_t)&LineToCheck->Content[SymbolCheckIndex],
                                .Number = Number
                            };

                            Gears[GearIndex] = CurrentGear;
                            GearIndex++;
                        }

                        break;
                    }
                    SymbolCheckIndex++;
                    SymbolPositionsLeftToCheck--;
                }

                if (SymbolFound) break;
                LinesToCheckIndex++;
            }
        }
    }

    //DEBUG_PRINT("Gears parsed: %i\n", GearIndex + 1);

    printf("Part 1 answer: %i\n", Part1Answer);
    assert(Part1Answer == 538046);

    for (int32_t OuterGearIndex = 0; OuterGearIndex < GearCount; OuterGearIndex++) {
        Gear CurrentGear = Gears[OuterGearIndex];
        if (CurrentGear.Number == 0 && CurrentGear.SymbolPosition == 0) break;
        int32_t Occurences = 1;

        Gear PreviousCompareGear;

        for (int32_t InnerGearIndex = 0; InnerGearIndex < GearCount; InnerGearIndex++) {
            if (InnerGearIndex == OuterGearIndex) continue;
            Gear CurrentCompareGear = Gears[InnerGearIndex];
            if (CurrentCompareGear.Number == 0 && CurrentCompareGear.SymbolPosition == 0) break;

            if (CurrentGear.SymbolPosition == CurrentCompareGear.SymbolPosition) {
                Occurences++;
                if (Occurences > 2) break;
                PreviousCompareGear = Gears[InnerGearIndex];
            }
        }

        if (Occurences == 2) {
            Part2Answer += CurrentGear.Number * PreviousCompareGear.Number;
        }
    }

    Part2Answer = Part2Answer / 2;
    printf("Part 2 answer: %i\n", Part2Answer);
    assert(Part2Answer == 81709807);

    return EXIT_SUCCESS;
}
