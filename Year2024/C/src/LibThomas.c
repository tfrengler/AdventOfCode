#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

char* GetReadableBytes(size_t bytes) {
    if (bytes == 0) {
        char* ReturnData = malloc(8);
        memcpy(ReturnData, "0 bytes", 8);
        return ReturnData;
    }

    const int32_t i = (int32_t)floor(log((double_t)bytes) / log(1024));
    char* Sizes[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
    double_t FinalSize = ((double_t)bytes / pow(1024, i));

    size_t StringSize = (size_t)((floor(log10(FinalSize)) + 1) + 3);
    char* ReturnData = malloc(StringSize + 1);
    memset(ReturnData, 0, StringSize + 1);

    sprintf(ReturnData, "%zu %s", (size_t)round(FinalSize), Sizes[i]);
    return ReturnData;
}

static struct timespec start;
static struct timespec end;

void TimerStart(void)
{
    clock_gettime(CLOCK_MONOTONIC, &start);
}

void TimerStop(void)
{
    clock_gettime(CLOCK_MONOTONIC, &end);
}

void PrintTimer(void)
{
    printf(
        "Time taken: %.5f seconds\n",
        ((double)end.tv_sec + 1.0e-9*end.tv_nsec) -
        ((double)start.tv_sec + 1.0e-9*start.tv_nsec));
}
