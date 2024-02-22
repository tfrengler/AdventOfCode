#include "LibThomas.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>
#include <strings.h>
#include "stdio.h"

u8 String_StartsWith(const String* input, const String* pattern)
{
    if (pattern->Size > input->Size) return 0;

    for(i32 Index = 0; Index < pattern->Size; Index++)
    {
        if (input->Content[Index] != pattern->Content[Index])
        {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    StringArray* Input = File_ReadAllLines("Input/01.txt");
    // StringArray* Input = File_ReadAllLines("src/Debug.txt");
    i32 PartAnswer = 0;

    String* PatternOne = String_Make("one", 3);
    String* PatternTwo = String_Make("two", 3);
    String* PatternThree = String_Make("three", 5);
    String* PatternFour = String_Make("four", 4);
    String* PatternFive = String_Make("five", 4);
    String* PatternSix = String_Make("six", 3);
    String* PatternSeven = String_Make("seven", 5);
    String* PatternEight = String_Make("eight", 5);
    String* PatternNine = String_Make("nine", 4);

    char NumberAsStringBuffer[3];
    memset(&NumberAsStringBuffer, 0, sizeof(NumberAsStringBuffer));

    i32 BufferIndex = 0;

    for(i32 LineIndex = 0; LineIndex < Input->Count; LineIndex++)
    {
        String* CurrentString = Input->Contents[LineIndex];

        for(i32 StringIndex = 0; StringIndex < CurrentString->Size; StringIndex++)
        {
            char CurrentChar = CurrentString->Content[StringIndex];
            if ((int)CurrentChar < 58 && (int)CurrentChar > 48)
            {
                NumberAsStringBuffer[BufferIndex] = CurrentChar;
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }

            i32 CharsToTake = CurrentString->Size - StringIndex;
            assert(CharsToTake > 0);
            if (CharsToTake > 5) CharsToTake = 5;

            char NumberAsWordBuffer[CharsToTake+1];
            memset(&NumberAsWordBuffer, 0, CharsToTake+1);
            memcpy(&NumberAsWordBuffer, &CurrentString->Content[StringIndex], CharsToTake);
            String* StringToTest = String_Make(NumberAsWordBuffer, (u16)CharsToTake);

            if (String_StartsWith(StringToTest, PatternOne))
            {
                NumberAsStringBuffer[BufferIndex] = '1';
                StringIndex += (PatternOne->Size-1);
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }
            if (String_StartsWith(StringToTest, PatternTwo))
            {
                NumberAsStringBuffer[BufferIndex] = '2';
                StringIndex += (PatternTwo->Size-1);
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }
            if (String_StartsWith(StringToTest, PatternThree))
            {
                NumberAsStringBuffer[BufferIndex] = '3';
                StringIndex += (PatternThree->Size-1);
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }
            if (String_StartsWith(StringToTest, PatternFour))
            {
                NumberAsStringBuffer[BufferIndex] = '4';
                StringIndex += (PatternFour->Size-1);
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }
            if (String_StartsWith(StringToTest, PatternFive))
            {
                NumberAsStringBuffer[BufferIndex] = '5';
                StringIndex += (PatternFive->Size-1);
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }
            if (String_StartsWith(StringToTest, PatternSix))
            {
                NumberAsStringBuffer[BufferIndex] = '6';
                StringIndex += (PatternSix->Size-1);
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }
            if (String_StartsWith(StringToTest, PatternSeven))
            {
                NumberAsStringBuffer[BufferIndex] = '7';
                StringIndex += (PatternSeven->Size-1);
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }
            if (String_StartsWith(StringToTest, PatternEight))
            {
                NumberAsStringBuffer[BufferIndex] = '8';
                StringIndex += (PatternEight->Size-1);
                if (BufferIndex == 0) BufferIndex = 1;
                continue;
            }
            if (String_StartsWith(StringToTest, PatternNine))
            {
                NumberAsStringBuffer[BufferIndex] = '9';
                StringIndex += (PatternNine->Size-1);
                if (BufferIndex == 0) BufferIndex = 1;
            }
        }

        if (NumberAsStringBuffer[1] == 0) NumberAsStringBuffer[1] = NumberAsStringBuffer[0];
        i32 CalibrationNumber = atoi(NumberAsStringBuffer);

        memset(&NumberAsStringBuffer, 0, 2);
        BufferIndex = 0;

        PartAnswer += CalibrationNumber;
        //if (LineIndex == 0) break;
    }

    printf("Part answer: %i\n", PartAnswer);
    assert(PartAnswer == 53592);

    return EXIT_SUCCESS;
}


