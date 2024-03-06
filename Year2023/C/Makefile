#BUILD := debug
#
#cflags.debug := flags here...
#cflags.release := flags here...
#CFLAGS := ${cxxflags.${BUILD}}
# call make like this: make BUILD=release

# These flags require the AddressSanitizer-module
# -fsanitize=undefined,address -fsanitize-trap -fno-common

CC					:= clang
CFLAGS				:= -std=c17 -Wall -Wextra -Wconversion -Wshadow-all -Wundef -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-variable -Wfloat-equal -pedantic-errors -Wtype-limits -Wno-unused-function -Wno-sign-conversion -Wdouble-promotion -Wformat=2 -Wformat-pedantic -Wfor-loop-analysis -g3 -O0
SRC_DIR				:= src/
BUILD_DIR			:= build/
OBJ_DIR				:= obj/
OUTFILE				:= bin
SOURCE_FILES 		:= $(wildcard $(SRC_DIR)*.c)
OBJECT_FILES		:= $(SOURCE_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPENDENCY_FILES	:= $(OBJECT_FILES:.o=.d)

#1: Generate main target which depend on the object files...
all: $(OBJECT_FILES)
	$(CC) -o $(BUILD_DIR)$(OUTFILE) $^

#2: Generate the object files which depend on the source files...
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

#3: Include the dependency files (which are in the format: X.o: X.c X.h, but without a recipe...)
-include $(DEPENDENCY_FILES)

#4: Generate dependency files to ensure that changes to header-files causes object files to be rebuilt
$(OBJ_DIR)%.d: $(SRC_DIR)%.c
	@$(CC) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)*.*
