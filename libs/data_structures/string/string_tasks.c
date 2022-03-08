#include "string_tasks.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

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
    while (*s != '\0') {
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

void replacingNumberWithSpaces(char *s) {
    char *beginBuffer = _stringBuffer;
    char *endBuffer = copy(s, s + strlen_(s), _stringBuffer);

    while (beginBuffer < endBuffer) {
        if (isdigit(*beginBuffer)) {
            for (int i = 0; i < *beginBuffer - '0'; i++) {
                *s = ' ';
                s++;
            }
        } else {
            *s = *beginBuffer;
            s++;
        }
        beginBuffer++;
    }

    *s = '\0';
}

void test_numberTurnIntoSpaces_CommonCase() {
    char s[] = "g1fp2d3f";
    replacingNumberWithSpaces(s);

    ASSERT_STRING("g fp  d   f", s);
}

void test_numberTurnIntoSpaces_OnlyDigits() {
    char s[] = "36";
    replacingNumberWithSpaces(s);

    ASSERT_STRING("         ", s);
}

void test_numberTurnIntoSpaces_OnlyLetters() {
    char s[] = "vseOk";
    replacingNumberWithSpaces(s);

    ASSERT_STRING("vseOk", s);
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};

    char *readPtr, *recPtr;
    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

}

void test_replace_CommonCase() {
    char s[] = "ne ok";
    char w1[] = "ne";
    char w2[] = "vse";
    replace(s, w1, w2);

    ASSERT_STRING("vse ok", s);
}

int areWordsEqual(WordDescriptor w1,
                  WordDescriptor w2) {
    if(w1.end - w1.begin != w2.end - w2.begin) {
        return 0;
    }

    while (*w1.begin != *w1.end) {
        if(*w1.begin != *w2.begin) {
            return 0;
        }
        w1.begin++;
        w2.begin++;
    }

    return 1;
}

bool isLexicallyOrderedSentence(char *s) {
    char *beginSearch = s;
    WordDescriptor curWord;

    if (!getWord(beginSearch, &curWord)) {
        return true;
    }

    WordDescriptor lastWord = curWord;
    beginSearch = lastWord.end;

    while (getWord(beginSearch, &curWord)) {
        if (areWordsEqual(lastWord, curWord) > 0) {
            return false;
        }

        lastWord = curWord;
        beginSearch = curWord.end;
    }

    return true;
}

void test_isLexicallyOrderedSentence_CommonCase() {
    char s[] = "avse bvse vse";

    assert(isLexicallyOrderedSentence(s));
}

void test_isLexicallyOrderedSentence_onlySpaces() {
    char s[] = "        ";

    assert(isLexicallyOrderedSentence(s));
}

void test_isLexicallyOrderedSentence_notOrdered() {
    char s[] = "vse vse";

    assert(!isLexicallyOrderedSentence(s));
}
