#include "string_tasks.h"
#include <stdio.h>
#include "string_.h"
#include <ctype.h>

#define ASSERT_STRING(expected, got) assertString (expected, got , \
__FILE__, __FUNCTION__, __LINE__ )


void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected : \"%s \"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

char *getEndOfString(char *s) {
    while(*s != '\0') {
        s++;
    }

    return s;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void task1(char *s) {
    removeNonLetters(s);
}

void test_task1_CommonCase() {
    char s[] = "a   fse";
    task1(s);

    char res[] = "afse";

    ASSERT_STRING(res, s);
}

void test_task1_AllSpace() {
    char s[] = "   ";
    task1(s);

    char res[] = "";

    ASSERT_STRING(res, s);
}




