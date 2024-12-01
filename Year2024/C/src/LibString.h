#ifndef LIB_STRING_H
#define LIB_STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* The maximum size of a string as used by String-instances. */
static const int32_t STRING_MAX_SIZE = 65535;

/* Represents a wrapper around a C-string (char*) with a max size of 64kb. Content is the string and Size is the length without the null-terminator.*/
typedef struct _String {
	int32_t Size; // Size is until but not including the line terminator
	char *Content;
} String;

/* Represents a wrapper around an fixed length array of String*-instances. Count is the amount of structs in Contents, and Contents is the array (ptr to the start)*/
typedef struct _StringArray {
	int32_t Count;
	String **Contents;
} StringArray;

StringArray *File_ReadAllLines(const char *fileNameAndPath);
StringArray *String_Split(const String *inputString, char delimiter);
void StringArray_Free(StringArray *input, bool freeContent);
StringArray* StringArray_Make(String **input, int32_t size);

void String_Free(String *input);
String *File_ReadAllText(const char *fileNameAndPath);
String *String_Make(const char *content, int32_t size);
String *String_Empty(void);
bool String_StartsWith(const String *input, const String *pattern, bool caseInsensitive);
bool String_EndsWith(const String *input, const String *pattern, bool caseInsensitive);
bool String_Contains(const String *input, const String *pattern, bool caseInsensitive);
bool String_Equals(const String *original, const String *compare, bool caseInsensitive);
String *String_Trim(const String *input);

#endif
