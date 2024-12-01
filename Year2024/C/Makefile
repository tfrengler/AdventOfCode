
cflagsBase 			:= -std=c17 -Wall -Wextra -Wconversion -Wshadow-all -Wundef -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-variable -Wfloat-equal -pedantic-errors -Wtype-limits -Wno-unused-function -Wno-sign-conversion -Wdouble-promotion -Wformat=2 -Wformat-pedantic -Wfor-loop-analysis -pthread
cflags.debug 		:= ${cflagsBase} -fsanitize=undefined -fsanitize=address -fsanitize-trap -fno-omit-frame-pointer -fno-common -g3 -O0
cflags.release 		:= ${cflagsBase} -O2
cflags.test 		:= -std=c17 -g3 -O0

NR					:= INVALID
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

Debug: $(OBJ_DIR)Debug.o $(LIBS)
	@echo "Linking and creating binary for $@ ($(BUILD_DIR)$@_$(BUILD).exe)"
	@$(CC) ${CFLAGS} -o $(BUILD_DIR)$@_$(BUILD).exe $^ $(LDFLAGS)

day: $(OBJ_DIR)Day${NR}.o $(LIBS)
	@echo "Linking and creating binary for $@ ($(BUILD_DIR)$@${NR}_$(BUILD).exe)"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$@${NR}_$(BUILD).exe $^

.PHONY: clean
clean:
	@echo "Cleaning build- and object dir"
	@-rm $(BUILD_DIR)*.* $(OBJ_DIR)*.*

.PHONY: clean_libs
clean_libs:
	@echo "Cleaning libs"
	@-rm ${LIBS}

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "(re)compiling object file $@ from source file $<"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@