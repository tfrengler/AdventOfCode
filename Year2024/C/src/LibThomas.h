#ifndef LIB_THOMAS_H
#define LIB_THOMAS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

// Enables extra checks, such as NULL checks after each malloc, asserts on function parameters etc.
#define DEBUG() 1

// To set up use vscode with the following extensions:
// clangd (intellisense) and CodeLLDB (for debugging)
// For toolchain use MSYS2 with the following package(s): pacman -S mingw-w64-clang-x86_64-toolchain
// Use the following compiler flags for debugging. For release-like mode omit -g3, fsanitize-flags and use -O3
/*
    -std=c17
    -Wall
    -Wextra
    -Wconversion
    -Wshadow-all
    -Wundef
    -Wunreachable-code
    -Wuninitialized
    -Wold-style-cast
    -Wno-error=unused-variable
    -Wfloat-equal
    -pedantic-errors
    -Wtype-limits
    -Wno-unused-function
    -Wno-sign-conversion
    -Wdouble-promotion
    -Wformat=2
    -Wformat-pedantic
    -Wfor-loop-analysis
	-pthread
	-fsanitize=undefined
	-fsanitize=address
	-fsanitize-trap
	-fno-omit-frame-pointer
	-fno-common
	-g3
	-O0
*/

// NOTE: Only useful for stack allocated arrays. Note that strings will be one extra due to the null terminator!
#define arrayCount(x) (sizeof(x) / sizeof(*x))
typedef uint8_t byte;

#if DEBUG()
#define DEBUG_PRINT(f_, ...) printf((f_), __VA_ARGS__)
#else
#define DEBUG_PRINT(f, ...) \
	do {                    \
	} while (0)
#endif

void Fatal(const char *message);

void Free(void* ptr);
void *Malloc(size_t size);

size_t GetAllocations(void);
void PrintAllocations(void);
size_t GetDeAllocations(void);
void TimerStart(void);
void TimerStop(void);
void PrintTimer(void);

#endif
