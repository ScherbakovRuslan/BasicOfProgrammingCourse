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
    if (w1.end - w1.begin != w2.end - w2.begin) {
        return 0;
    }

    while (*w1.begin != *w1.end) {
        if (*w1.begin != *w2.begin) {
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

void getBagOfWords(BagOfWords *bag, char *s) {
    char *beginSearch = s;
    bag->size = 0;
    WordDescriptor curWord;

    while (getWord(beginSearch, &curWord)) {
        bag->words[bag->size] = curWord;
        beginSearch = curWord.end;

        bag->size++;
    }
}

void test_getBagOfWords_CommonCase() {
    char s[] = "hello world";
    BagOfWords bag;
    getBagOfWords(&bag, s);

    assert(bag.size == 2);
}

void test_getBagOfWords_AllSpace() {
    char s[] = "   ";
    BagOfWords bag;
    getBagOfWords(&bag, s);

    assert(bag.size == 0);
}

bool isPalindrome_(char *begin, char *end) {
    if (begin != end) {
        end--;
        while (begin < end) {
            if (*begin != *end) {
                return false;
            }

            begin++;
            end--;
        }
        return true;
    }

    return false;
}

size_t countPalindromeInString(char *s) {
    char *beginSearch = s;
    char *end = getEndOfString(s);
    size_t countPalindromes = 0;
    char *iComma = find(beginSearch, end, ',');

    while (*beginSearch != *end) {
        beginSearch = findNonSpace(beginSearch);
        if (isPalindrome_(beginSearch, iComma)) {
            countPalindromes++;
        }

        beginSearch = iComma + 1;

        iComma = find(beginSearch, end, ',');
    }

    return countPalindromes;
}

void test_nOfPalindromeWords_commonCase() {
    char *s = "dgd, hello, dvd, world";

    assert(countPalindromeInString(s) == 2);
}

void test_nOfPalindromeWords_NoPalindromes() {
    char *s = "leon, shelli, bull";

    assert(countPalindromeInString(s) == 0);
}

void test_nOfPalindromeWords_emptyWords() {
    char *s = "     ,  , ,      ";

    assert(countPalindromeInString(s) == 0);
}

void unionString(char *s1, char *s2, char *s) {
    if (*s1 == '\0' && *s2 == '\0') {
        *s = '\0';
        return;
    }

    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = s1, *beginSearch2 = s2;
    while ((isW1Found = getWord(beginSearch1, &word1)),
            (isW2Found = getWord(beginSearch2, &word2)),
            isW1Found || isW2Found) {
        if (isW1Found) {
            s = copy(word1.begin, word1.end, s);
            *s = ' ';
            s++;
            beginSearch1 = word1.end;
        }
        if (isW2Found) {
            s = copy(word2.begin, word2.end, s);
            *s = ' ';
            s++;
            beginSearch2 = word2.end;
        }
    }

    s--;
    *s = '\0';
}

void test_unionString_CommonCase() {
    char s[MAX_STRING_SIZE];
    char s1[] = "hello vse";
    char s2[] = "world ok";

    unionString(s1, s2, s);

    ASSERT_STRING("hello world vse ok", s);
}

void test_unionString_AllWordsInOneString() {
    char s[MAX_STRING_SIZE];
    char s1[] = "";
    char s2[] = "hello world vse ok";

    unionString(s1, s2, s);

    ASSERT_STRING("hello world vse ok", s);
}

bool aInWord(WordDescriptor w) {
    while (w.begin != w.end) {
        if (*w.begin == 'a' || *w.begin == 'A') {
            return true;
        }
        w.begin++;
    }

    return false;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s,
                                                               char **beginWordBefore,
                                                               char **endWordBefore) {
    WordDescriptor w1;
    char *begin = s;
    if (!getWord(begin, &w1)) {
        return EMPTY_STRING;
    } else if (aInWord(w1)) {
        return FIRST_WORD_WITH_A;
    }

    begin = w1.end;
    WordDescriptor w2;
    while (getWord(begin, &w2)) {
        if (aInWord(w2)) {
            *beginWordBefore = w1.begin;
            *endWordBefore = w1.end;

            return WORD_FOUND;
        }
        w1 = w2;
        begin = w2.end;
    }
    return NOT_FOUND_A_WORD_WITH_A;
}

void printWordBeforeFirstWordWithA(char *s) {
    char *begin = s;
    char *beginWordBefore, *endWordBefore;

    if (getWordBeforeFirstWordWithA(begin, &beginWordBefore, &endWordBefore) == WORD_FOUND) {
        *endWordBefore = '\0';

        printf("%s\n", beginWordBefore);
    }
}

void testAll_getWordBeforeFirstWordWithA() {
    char *beginWord, *endWord;

    char s1[] = "";
    assert (getWordBeforeFirstWordWithA(s1, &beginWord, &endWord)
            == EMPTY_STRING);

    char s2[] = " ABC";
    assert (getWordBeforeFirstWordWithA(s2, &beginWord, &endWord)
            == FIRST_WORD_WITH_A);

    char s3[] = "BC A";
    assert (getWordBeforeFirstWordWithA(s3, &beginWord, &endWord)
            == WORD_FOUND);
    char got[MAX_WORD_SIZE];
    copy(beginWord, endWord, got);
    got[endWord - beginWord] = '\0';
    ASSERT_STRING ("BC", got);

    char s4[] = "B Q WE YR OW IUWR ";
    assert (getWordBeforeFirstWordWithA(s4, &beginWord, &endWord) ==
            NOT_FOUND_A_WORD_WITH_A);
}

void wordDescriptorToString(WordDescriptor word, char *destination) {
    destination = copy(word.begin, word.end, destination);
    *destination = '\0';
}

WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2) {
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);
    WordDescriptor word = {0, 0};
    for (int i = _bag.size - 1; i >= 0; i--)
        for (int j = _bag2.size - 1; j >= 0; j--)
            if (areWordsEqual(_bag.words[i], _bag2.words[j]) == 0) {
                word = _bag.words[i];
                return word;
            }

    return word;
}

void test_lastWordInFirstStringInSecondString_CommonCase() {
    char s1[] = "hello world vce ok";
    char s2[] = "vce ok hello world";
    WordDescriptor word = lastWordInFirstStringInSecondString(s1, s2);
    char string[MAX_STRING_SIZE];
    wordDescriptorToString(word, string);
    ASSERT_STRING ("ok", string);
}

void test_lastWordInFirstStringInSecondString_EmptyString() {
    char s1[] = "";
    char s2[] = "";
    WordDescriptor word = lastWordInFirstStringInSecondString(s1, s2);
    char string[MAX_STRING_SIZE];
    wordDescriptorToString(word, string);
    ASSERT_STRING ("", string);
}