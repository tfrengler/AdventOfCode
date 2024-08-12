#include <stdio.h>
#include <stdlib.h>
#include "LibThomas.h"

/**
 * @brief  Panics and terminates the program with EXIT_FAILURE, caused by an unrecoverable error.
 * @param  message: The message to print to perror.
 * @retval None
 */
void Fatal(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void *Malloc(size_t size)
{
    void *ReturnData = malloc(size);
    
    if (ReturnData == 0x0) {
        puts("Fatal, malloc failed");
        exit(EXIT_FAILURE);
    }

    return ReturnData;
}

