

cflags.debug 		:= -std=c17 -Wall -Wextra -Wconversion -Wshadow-all -Wundef -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-variable -Wfloat-equal -pedantic-errors -Wtype-limits -Wno-unused-function -Wno-sign-conversion -Wdouble-promotion -Wformat=2 -Wformat-pedantic -Wfor-loop-analysis -pthread -fsanitize=undefined -fsanitize=address -fsanitize-trap -fno-omit-frame-pointer -fno-common -g3 -O0
cflags.release 		:= -std=c17 -Wall -Wextra -Wconversion -Wshadow-all -Wundef -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-variable -Wfloat-equal -pedantic-errors -Wtype-limits -Wno-unused-function -Wno-sign-conversion -Wdouble-promotion -Wformat=2 -Wformat-pedantic -Wfor-loop-analysis -pthread -O2
# call make like this: make BUILD=release

BUILD 				:= release
CC					:= clang
CFLAGS				:= ${cflags.${BUILD}}
SRC_DIR				:= src/
BUILD_DIR			:= build/
OBJ_DIR				:= obj/
LIBS				:= ${SRC_DIR}LibThomas.c
SOURCE_FILES 		:= $(wildcard $(SRC_DIR)*.c)
OBJECT_FILES		:= $(SOURCE_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPENDENCY_FILES	:= $(OBJECT_FILES:.o=.d)

all: D1P1 D1P2 D2 D3 D4 D5

D1P1:
	$(CC) $(CFLAGS) $(LIBS) $(SRC_DIR)Day01Part1.c -o $(BUILD_DIR)Day01Part1_$(BUILD).exe

D1P2:
	$(CC) $(CFLAGS) $(LIBS) $(SRC_DIR)Day01Part2.c -o $(BUILD_DIR)Day01Part2_$(BUILD).exe

D2:
	$(CC) $(CFLAGS) $(LIBS) $(SRC_DIR)Day02Part1And2.c -o $(BUILD_DIR)Day02Part1And2_$(BUILD).exe

D3:
	$(CC) $(CFLAGS) $(LIBS) $(SRC_DIR)Day03Part1And2.c -o $(BUILD_DIR)Day03Part1And2_$(BUILD).exe

D4:
	$(CC) $(CFLAGS) $(LIBS) $(SRC_DIR)Day04Part1And2.c -o $(BUILD_DIR)Day04Part1And2_$(BUILD).exe

D5:
	$(CC) $(CFLAGS) $(LIBS) $(SRC_DIR)Day05Part1And2.c -o $(BUILD_DIR)Day05Part1And2_$(BUILD).exe
