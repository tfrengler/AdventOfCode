#include "LibThomas.h"
#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
//#include <pthread.h>

void TestUnsigned(void)
{
    int Result = 42;
    bool Success = false;

    // Leading zero
    char TestString01[] = "00123"; // True, 0
    // Leading non-digit
    char TestString02[] = "ab123"; // True, 0
    // Leading whitespace
    char TestString03[] = "  123"; // True, 123
    // Trailing whitespace
    char TestString04[] = "123  "; // True, 123
    // Multiple digits, character separated
    char TestString05[] = "123x4"; // True, 123
    // Multiple digits, whitespace separated
    char TestString06[] = "123 4"; // True, 123
    // Max int edge detection, upper bound
    char TestString07[] = "2147483647"; // True, 2147483647

    Success = StringToInt(TestString01, arrayCount(TestString01)-1, &Result);
    assert(Success == true);
    assert(Result == 0);
    puts("Unsigned: leading zero passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString02, arrayCount(TestString02)-1, &Result);
    assert(Success == true);
    assert(Result == 0);
    puts("Unsigned: leading non-digit passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString03, arrayCount(TestString03)-1, &Result);
    assert(Success == true);
    assert(Result == 123);
    puts("Unsigned: leading whitespace passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString04, arrayCount(TestString04)-1, &Result);
    assert(Success == true);
    assert(Result == 123);
    puts("Unsigned: trailing whitespace passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString05, arrayCount(TestString05)-1, &Result);
    assert(Success == true);
    assert(Result == 123);
    puts("Unsigned: multiple digits separated by chars passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString06, arrayCount(TestString06)-1, &Result);
    assert(Success == true);
    assert(Result == 123);
    puts("Unsigned: multiple digits separated by whitespace passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString07, arrayCount(TestString07)-1, &Result);
    assert(Success == true);
    assert(Result == INT_MAX);
    puts("Unsigned: max int at edge passed");

    puts("ALL unsigned test cases OK");
}

void TestSigned(void)
{
    int Result;
    bool Success;
    // Leading zero
    char TestString11[] = "00-123"; // True, 0
    // Leading zero after sign
    char TestString12[] = "-00123"; // True, 0
    // Leading non-digit
    char TestString13[] = "ab-123"; // True, 0
    // Leading whitespace
    char TestString14[] = "  -123"; // True, -123
    // Trailing whitespace
    char TestString15[] = "-123  "; // True, -123
    // Multiple digits, character separated
    char TestString16[] = "-123x4"; // True, -123
    // Multiple digits, whitespace separated
    char TestString17[] = "-123 4"; // True, -123
    // Max int edge detection, lower bound
    char TestString18[] = "-2147483648"; // True, -2147483648

    Result = 42;
    Success = false;
    Success = StringToInt(TestString11, arrayCount(TestString11)-1, &Result);
    assert(Success == true);
    assert(Result == 0);
    puts("Signed: leading zero passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString12, arrayCount(TestString12)-1, &Result);
    assert(Success == true);
    assert(Result == 0);
    puts("Signed: leading zero after sign passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString13, arrayCount(TestString13)-1, &Result);
    assert(Success == true);
    assert(Result == 0);
    puts("Signed: leading non-digit passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString14, arrayCount(TestString14)-1, &Result);
    assert(Success == true);
    assert(Result == -123);
    puts("Signed: leading whitespace passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString15, arrayCount(TestString15)-1, &Result);
    assert(Success == true);
    assert(Result == -123);
    puts("Signed: trailing whitespace passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString16, arrayCount(TestString16)-1, &Result);
    assert(Success == true);
    assert(Result == -123);
    puts("Signed: multiple digits separated by chars passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString17, arrayCount(TestString17)-1, &Result);
    assert(Success == true);
    assert(Result == -123);
    puts("Signed: multiple digits separated by whitespace passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString18, arrayCount(TestString18)-1, &Result);
    assert(Success == true);
    assert(Result == INT_MIN);
    puts("Signed: max int at edge passed");

    puts("ALL signed test cases OK");
}

void TestMisc(void)
{
    int Result;
    bool Success;

    // Overflow, upper bound by calculation
    char TestString21[] = "2147483648"; // False, 0
    // Overflow, lower bound by calculation
    char TestString22[] = "-2147483649"; // False, 0
    // Overflow, upper bound by digits
    char TestString23[] = "21474836471"; // False, 0
    // Overflow, lower bound by digits
    char TestString24[] = "-21474836481"; // False, 0

    Result = 42;
    Success = true;
    Success = StringToInt(TestString21, arrayCount(TestString21)-1, &Result);
    assert(Success == false);
    assert(Result == 0);
    puts("Overflow upperbound by calculation passed");

    Result = 42;
    Success = true;
    Success = StringToInt(TestString22, arrayCount(TestString22)-1, &Result);
    assert(Success == false);
    assert(Result == 0);
    puts("Overflow lowerbound by calculation passed");

    Result = 42;
    Success = true;
    Success = StringToInt(TestString23, arrayCount(TestString23)-1, &Result);
    assert(Success == false);
    assert(Result == 0);
    puts("Overflow upperbound by digits passed");

    Result = 42;
    Success = true;
    Success = StringToInt(TestString24, arrayCount(TestString24)-1, &Result);
    assert(Success == false);
    assert(Result == 0);
    puts("Overflow lowerbound by digits passed");

    Result = 42;
    Success = true;
    Success = StringToInt(NULL, arrayCount(TestString22)-1, &Result);
    assert(Success == false);
    assert(Result == 0);
    puts("Input null passed");

    Result = 42;
    Success = true;
    Success = StringToInt(TestString22, arrayCount(TestString22)-1, NULL);
    assert(Success == false);
    assert(Result == 42);
    puts("Output null passed");

    Result = 42;
    Success = true;
    Success = StringToInt(TestString22, 0, &Result);
    assert(Success == false);
    assert(Result == 0);
    puts("Length less than 1 passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString21, 1, &Result);
    assert(Success == true);
    assert(Result == 2);
    puts("Valid length shorter than input yields unsigned passed");

    Result = 42;
    Success = false;
    Success = StringToInt(TestString22, 2, &Result);
    assert(Success == true);
    assert(Result == -2);
    puts("Valid length shorter than input yields unsigned passed");

    Result = 42;
    Success = false;
    char TestString25[] = "123456";
    TestString25[3] = '\0';

    Success = StringToInt(TestString25, 7, &Result);
    assert(Success == false);
    assert(Result == 0);
    puts("String with null terminator before length argument passed");

    puts("ALL misc test cases OK");
}

int main(void)
{
    TestUnsigned();
    TestSigned();
    TestMisc();

    return EXIT_SUCCESS;
}
