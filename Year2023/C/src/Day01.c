#include "LibThomas.h"
#include "stdlib.h"
#include <strings.h>

typedef struct _StringTest {
    char* Value;
} StringTest;

int main(void)
{
    // string InputFile = File_Read("Input/01.txt");

    StringTest test;
    test.Value = "test";
    
    printf("main: %p\n", &test.Value);

    return EXIT_SUCCESS;
}

void func1(StringTest input)
{
    printf("func1: %p\n", input.Value);
}

void func2(StringTest* input)
{
    printf("func1: %p\n", &input->Value);
}
