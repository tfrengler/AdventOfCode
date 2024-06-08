

cflags.debug 		:= -std=c17 -Wall -Wextra -Wconversion -Wshadow-all -Wundef -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-variable -Wfloat-equal -pedantic-errors -Wtype-limits -Wno-unused-function -Wno-sign-conversion -Wdouble-promotion -Wformat=2 -Wformat-pedantic -Wfor-loop-analysis -pthread -fsanitize=undefined -fsanitize=address -fsanitize-trap -fno-omit-frame-pointer -fno-common -g3 -O0
cflags.release 		:= -std=c17 -Wall -Wextra -Wconversion -Wshadow-all -Wundef -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-variable -Wfloat-equal -pedantic-errors -Wtype-limits -Wno-unused-function -Wno-sign-conversion -Wdouble-promotion -Wformat=2 -Wformat-pedantic -Wfor-loop-analysis -pthread -O2

BUILD 				:= release
CC					:= clang
CFLAGS				:= ${cflags.${BUILD}}
SRC_DIR				:= src/
BUILD_DIR			:= build/
OBJ_DIR				:= obj/
LIBS				:= ${OBJ_DIR}LibThomas.o
SOURCE_FILES 		:= $(wildcard $(SRC_DIR)*.c)
OBJECT_FILES		:= $(SOURCE_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPENDENCY_FILES	:= $(OBJECT_FILES:.o=.d)
-include $(DEPENDENCY_FILES)

all: Day01 Day02 Day03 Day04 Day05

Day01: $(OBJ_DIR)Day01.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@_$(BUILD).exe $^

Day02: $(OBJ_DIR)Day02.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@_$(BUILD).exe $^

Day03: $(OBJ_DIR)Day03.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@_$(BUILD).exe $^

Day04: $(OBJ_DIR)Day04.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@_$(BUILD).exe $^

Day05: $(OBJ_DIR)Day05.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@_$(BUILD).exe $^

clean:
	@echo "Cleaning build- and object dir"
	@-rm $(BUILD_DIR)*.* $(OBJ_DIR)*.*

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "(re)compiling object file from $<"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@