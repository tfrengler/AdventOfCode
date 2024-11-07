
cflagsBase 			:= -std=c17 -Wall -Wextra -Wconversion -Wshadow-all -Wundef -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-variable -Wfloat-equal -pedantic-errors -Wtype-limits -Wno-unused-function -Wno-sign-conversion -Wdouble-promotion -Wformat=2 -Wformat-pedantic -Wfor-loop-analysis -pthread
cflags.debug 		:= ${cflagsBase} -fsanitize=undefined -fsanitize=address -fsanitize-trap -fno-omit-frame-pointer -fno-common -g3 -O0
cflags.release 		:= ${cflagsBase} -O2
cflags.test 		:= -std=c17 -g3 -O0

BUILD 				:= debug
CC					:= clang
CFLAGS				:= ${cflags.${BUILD}}
SRC_DIR				:= src/
BUILD_DIR			:= build/
OBJ_DIR				:= obj/
LIBS				:= ${OBJ_DIR}LibThomas.o ${OBJ_DIR}LibString.o ${OBJ_DIR}LibNumeric.o
SOURCE_FILES 		:= $(wildcard $(SRC_DIR)*.c)
OBJECT_FILES		:= $(SOURCE_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPENDENCY_FILES	:= $(OBJECT_FILES:.o=.d)
-include $(DEPENDENCY_FILES)

all: Day01 Day02 Day03 Day04 Day05 Day06 Day07 Day08 Day09

Debug: $(OBJ_DIR)Debug.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) ${CFLAGS} -o $(BUILD_DIR)$@_$(BUILD).exe $^

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

Day06: $(OBJ_DIR)Day06.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@_$(BUILD).exe $^

Day07: $(OBJ_DIR)Day07.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@_$(BUILD).exe $^

Day08: $(OBJ_DIR)Day08.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@_$(BUILD).exe $^

Day09: $(OBJ_DIR)Day09.o $(LIBS)
	@echo "Linking and creating binary for $@"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@_$(BUILD).exe $^

clean:
	@echo "Cleaning build- and object dir"
	@-rm $(BUILD_DIR)*.* $(OBJ_DIR)*.*

clean_libs:
	@echo "Cleaning libs"
	@-rm ${LIBS}

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "(re)compiling object file from $<"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@