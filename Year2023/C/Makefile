

cflags.debug 		:= -std=c17 -Wall -Wextra -Wconversion -Wshadow-all -Wundef -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-variable -Wfloat-equal -pedantic-errors -Wtype-limits -Wno-unused-function -Wno-sign-conversion -Wdouble-promotion -Wformat=2 -Wformat-pedantic -Wfor-loop-analysis -fsanitize=undefined -fsanitize=address -fsanitize-trap -fno-omit-frame-pointer -fno-common -g3 -O0
cflags.release 		:= -std=c17 -Wall -Wextra -Wconversion -Wshadow-all -Wundef -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-variable -Wfloat-equal -pedantic-errors -Wtype-limits -Wno-unused-function -Wno-sign-conversion -Wdouble-promotion -Wformat=2 -Wformat-pedantic -Wfor-loop-analysis -O2
# call make like this: make BUILD=release

BUILD 				:= release
CC					:= clang
CFLAGS				:= ${cflags.${BUILD}}
SRC_DIR				:= src/
BUILD_DIR			:= build/
OBJ_DIR				:= obj/
SOURCE_FILES 		:= $(wildcard $(SRC_DIR)*.c)
OBJECT_FILES		:= $(SOURCE_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPENDENCY_FILES	:= $(OBJECT_FILES:.o=.d)

all: Day1Part1 Day1Part2 Day2Part1And2

Day1Part1:
	$(CC) $(CFLAGS) $(SRC_DIR)LibThomas.c $(SRC_DIR)Day01Part1.c -o $(BUILD_DIR)Day01Part1.exe

Day1Part2:
	$(CC) $(CFLAGS) $(SRC_DIR)LibThomas.c $(SRC_DIR)Day01Part2.c -o $(BUILD_DIR)Day01Part2.exe

Day2Part1And2:
	$(CC) $(CFLAGS) $(SRC_DIR)LibThomas.c $(SRC_DIR)Day02Part1And2.c -o $(BUILD_DIR)Day02Part1And2.exe
