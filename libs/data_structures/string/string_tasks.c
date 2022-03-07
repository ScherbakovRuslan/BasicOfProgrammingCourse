#include "string_tasks.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

    ASSERT_STRING("afse", s);
}

void test_task1_AllSpace() {
    char s[] = "   ";
    task1(s);

    ASSERT_STRING("", s);
}

void removeExtraSpaces(char *s) {
    if (*s == '\0') {
        return;
    }

    char *writen = s;
    s++;

    while (*s != '\0') {
        if (isspace(*writen) && isspace(*s)) {
            *writen = ' ';
        } else {
            writen++;
            memcpy(writen, s, sizeof(char));
        }
        s++;
    }
    writen++;
    *writen = '\0';
}

void test_task2_CommonCase() {
    char s[] = "gh  hg  tr";
    removeExtraSpaces(s);

    ASSERT_STRING("gh hg tr", s);
}

void test_task2_OneSpace() {
    char s[] = "gh hgtr";
    removeExtraSpaces(s);

    ASSERT_STRING("gh hgtr", s);
}

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
    return 0;

    word->end = findSpace(word->begin);

    return 1;
}

void digitToStartWithSavingOrder(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIf(_stringBuffer, endStringBuffer, word.begin,
                               isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitToStartForEveryWord(char *s) {
    char *beginSearch = s;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {
        digitToStartWithSavingOrder(word);

        beginSearch = word.end;
    }
}

void test_digitToStartForEveryWord_CommonCase() {
    char s[] = "sgdf432 sdf924";
    digitToStartForEveryWord(s);

    ASSERT_STRING("432sgdf 924sdf", s);
}

void test_digitToStartForEveryWord_digitsInWord() {
    char s[] = "f5k6kh65 s8g43lv09";
    digitToStartForEveryWord(s);

    ASSERT_STRING("5665fkkh 84309sglv", s);
}