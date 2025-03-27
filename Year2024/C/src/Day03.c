#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"
#include "LibString.h"

String *Input = nullptr;

void Setup(void)
{
    Input = File_ReadAllText("./Input/03.txt");
    // Input = String_Make("xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))", 71);
    // Input = String_Make("xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))", 73);
    assert(Input != nullptr);
}

void Part01(void)
{
    int32_t PartAnswer = 0;
    TimerStart();

    for(int32_t charIndex = 0; charIndex < Input->Size; charIndex++) {

        if (charIndex + 3 >= Input->Size)
        {
            // puts("End of input string");
            break;
        }

        if (
            !(Input->Content[charIndex] == 'm' &&
            Input->Content[charIndex + 1] == 'u' &&
            Input->Content[charIndex + 2] == 'l' &&
            Input->Content[charIndex + 3] == '(')
        ) {
            continue;
        }

        // puts("Starts with mul(");

        int32_t IndexOfNumberChar = charIndex + 4;

        if (IndexOfNumberChar >= Input->Size)
        {
            // puts("End of input string");
            break;
        }

        if (!isdigit(Input->Content[IndexOfNumberChar])) {
            charIndex = IndexOfNumberChar;
            // puts("Char after mul( is not a digit");
            continue;
        }

        int32_t FirstNumber = 0;
        int32_t SecondNumber = 0;

        // First number
        char NextChar = Input->Content[IndexOfNumberChar];

        while(1) {
            bool IsDigit = isdigit(NextChar);
            if (!IsDigit) break;
            FirstNumber *= 10;
            FirstNumber += (NextChar - '0');
            IndexOfNumberChar++;
            NextChar = Input->Content[IndexOfNumberChar];
        }

        if (NextChar != ',') {
            // puts("Not a comma after first number");
            continue;
        }
        // Second number
        IndexOfNumberChar++;
        NextChar = Input->Content[IndexOfNumberChar];

        while(1) {
            bool IsDigit = isdigit(NextChar);
            if (!IsDigit) break;
            SecondNumber *= 10;
            SecondNumber += (NextChar - '0');
            IndexOfNumberChar++;
            NextChar = Input->Content[IndexOfNumberChar];
        }

        if (NextChar != ')') {
            // puts("Not a closing parenthesis after second number");
            continue;
        }

        // printf("%i * %i\n", FirstNumber, SecondNumber);
        PartAnswer += (FirstNumber * SecondNumber);
    }

    TimerStop();
    PrintTimer();

    printf("Part 01 answer: %i\n", PartAnswer);
    assert(PartAnswer == 192767529);
}

void Part02(void)
{
    int32_t PartAnswer = 0;
    bool Do = true;
    TimerStart();

    for(int32_t charIndex = 0; charIndex < Input->Size; charIndex++) {

        if (charIndex + 3 < Input->Size)
        {
            bool DoIt = (Input->Content[charIndex] == 'd' &&
            Input->Content[charIndex + 1] == 'o' &&
            Input->Content[charIndex + 2] == '(' &&
            Input->Content[charIndex + 3] == ')');

            if (DoIt) {
                // puts("Do it");
                Do = true;
            }
        }

        if (charIndex + 6 < Input->Size)
        {
            bool DontDoIt = (Input->Content[charIndex] == 'd' &&
            Input->Content[charIndex + 1] == 'o' &&
            Input->Content[charIndex + 2] == 'n' &&
            Input->Content[charIndex + 3] == '\'' &&
            Input->Content[charIndex + 4] == 't' &&
            Input->Content[charIndex + 5] == '(' &&
            Input->Content[charIndex + 6] == ')');

            if (DontDoIt) {
                // puts("Don't do it");
                Do = false;
            }
        }

        if (!Do) continue;

        if (charIndex + 3 >= Input->Size)
        {
            puts("End of input string");
            break;
        }

        if (charIndex + 3 >= Input->Size)
        {
            puts("End of input string");
            break;
        }

        if (
            !(Input->Content[charIndex] == 'm' &&
            Input->Content[charIndex + 1] == 'u' &&
            Input->Content[charIndex + 2] == 'l' &&
            Input->Content[charIndex + 3] == '(')
        ) {
            continue;
        }

        // puts("Starts with mul(");

        int32_t IndexOfNumberChar = charIndex + 4;

        if (IndexOfNumberChar >= Input->Size)
        {
            // puts("End of input string");
            break;
        }

        if (!isdigit(Input->Content[IndexOfNumberChar])) {
            charIndex = IndexOfNumberChar;
            // puts("Char after mul( is not a digit");
            continue;
        }

        int32_t FirstNumber = 0;
        int32_t SecondNumber = 0;

        // First number
        char NextChar = Input->Content[IndexOfNumberChar];

        while(1) {
            bool IsDigit = isdigit(NextChar);
            if (!IsDigit) break;
            FirstNumber *= 10;
            FirstNumber += (NextChar - '0');
            IndexOfNumberChar++;
            NextChar = Input->Content[IndexOfNumberChar];
        }

        if (NextChar != ',') {
            // puts("Not a comma after first number");
            continue;
        }
        // Second number
        IndexOfNumberChar++;
        NextChar = Input->Content[IndexOfNumberChar];

        while(1) {
            bool IsDigit = isdigit(NextChar);
            if (!IsDigit) break;
            SecondNumber *= 10;
            SecondNumber += (NextChar - '0');
            IndexOfNumberChar++;
            NextChar = Input->Content[IndexOfNumberChar];
        }

        if (NextChar != ')') {
            // puts("Not a closing parenthesis after second number");
            continue;
        }

        // printf("%i * %i\n", FirstNumber, SecondNumber);
        PartAnswer += (FirstNumber * SecondNumber);
    }

    TimerStop();
    PrintTimer();

    printf("Part 02 answer: %i\n", PartAnswer);
    assert(PartAnswer == 104083373);
}

int main(void)
{
    Setup();

    Part01();
    Part02();

    String_Free(Input);

    // PrintAllocations();
    return EXIT_SUCCESS;
}
