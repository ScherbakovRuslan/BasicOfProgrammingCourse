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

// Преобразовать строку таким образом, чтобы цифры каждого слова были
// перенесены в начало слова без изменения порядка следования их в слове,
// буквы перенести в конец слова.
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

// Преобразовать строку, заменяя каждую цифру соответствующим ей числом
// пробелов
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

int areWordsEqual(WordDescriptor w1,
                  WordDescriptor w2) {
    char *begin1 = w1.begin;
    char *begin2 = w2.begin;
    while (*begin1 == *begin2 && (begin1 < w1.end - 1 || begin2 < w2.end - 1)) {
        begin1++;
        begin2++;
    }

    return *begin1  - *begin2;
}

// Определить, упорядочены ли лексикографически слова данного предложения
bool isLexicallyOrderedSentence(char *s) {
    char *beginSearch = s;
    WordDescriptor curWord;

    if (!getWord(beginSearch, &curWord)) {
        return true;
    }

    WordDescriptor lastWord = curWord;
    beginSearch = lastWord.end;

    while (getWord(beginSearch, &curWord)) {
        if (areWordsEqual(lastWord, curWord) == 0) {
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

// получает позиции начала и конца каждого слова строки
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

bool isPalindrome(char *begin, char *end) {
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

// Определить количество слов-палиндромов.
size_t countPalindromeInString(char *s) {
    char *beginSearch = s;
    char *end = getEndOfString(s);
    size_t countPalindromes = 0;
    char *iComma = find(beginSearch, end, ',');

    while (*beginSearch != *end) {
        beginSearch = findNonSpace(beginSearch);
        if (isPalindrome(beginSearch, iComma)) {
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

// Даны две строки. Получить строку, в которой
// чередуются слова первой и второй строки.
// Если в одной из строк число слов больше, чем
// в другой, то оставшиеся слова этой строки должны
// быть дописаны в строку-результат
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

// Вывести слово данной строки, предшествующее первому из слов,
// содержащих букву "а"
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

// Определить последнее из слов первой строки,
// которое есть во второй строке
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

// Определить, есть ли в данной строке одинаковые слова.
bool isEqualWord(char *s) {
    getBagOfWords(&_bag, s);
    for (int i = 0; i < _bag.size; i++) {
        for (int j = i + 1; j < _bag.size; j++) {
            if (areWordsEqual(_bag.words[i], _bag.words[j]) == 0) {
                return true;
            }
        }
    }
    return false;
}

void test_isEqualWord_CommonCase() {
    char s[] = "vse vse ok";

    assert(isEqualWord(s) == true);
}

void test_isEqualWord_NoEqual() {
    char s[] = "vse ok";

    assert(isEqualWord(s) == false);
}

void test_isEqualWord_EmptyString() {
    char s[] = "";

    assert(isEqualWord(s) == false);
}

int cmp_char(const void *a, const void *b) {
    char arg1 = *(const char *) a;
    char arg2 = *(const char *) b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;

    return 0;
}

bool isPairWordsFromSameLetters(char *s) {
    char *endBuffer = copy(s, getEndOfString(s), _stringBuffer);
    *endBuffer = '\0';
    getBagOfWords(&_bag, _stringBuffer);
    for (int i = 0; i < _bag.size; i++) {
        qsort(_bag.words[i].begin, _bag.words[i].end - _bag.words[i].begin,
              sizeof(char), cmp_char);
    }

    return isEqualWord(_stringBuffer);
}

void test_isPairWordsFromSameLetters_CommonCase() {
    char s[] = "vce cev";

    assert(isPairWordsFromSameLetters(s) == true);
}

void test_isPairWordsFromSameLetters_EmptyString() {
    char s[] = "";

    assert(isPairWordsFromSameLetters(s) == false);
}

void test_isPairWordsFromSameLetters_AllSpace() {
    char s[] = "   ";

    assert(isPairWordsFromSameLetters(s) == false);
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend && !isspace(*rbegin))
        rbegin--;

    return rbegin;
}

int getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    word->end = findNonSpaceReverse(rbegin, rend) + 1;

    if (word->end == rend) {
        return false;
    }
    word->begin = findSpaceReverse(rbegin, rend) + 1;

    return true;
}

// Получить строку из слов данной строки, которые отличны от последнего слова
void getStringOfWordsDifferentLastWord(char *s) {
    WordDescriptor lastWord;
    getWordReverse(getEndOfString(s) - 1, s - 1, &lastWord);
    char *beginSearch = s;
    char *sCopy = s;
    WordDescriptor curWord;

    while (getWord(beginSearch, &curWord)) {
        if (areWordsEqual(curWord, lastWord)) {
            sCopy = copy(curWord.begin, curWord.end, sCopy);
            *sCopy = ' ';
            sCopy++;
        }
        beginSearch = curWord.end;
    }

    if (sCopy != s) {
        sCopy--;
    }
    *sCopy = '\0';
}

void test_getStringOfWordsDifferentLastWord_CommonCase() {
    char s[] = "world vse ok world";

    getStringOfWordsDifferentLastWord(s);
    ASSERT_STRING("vse ok",  s);
}

void test_getStringOfWordsDifferentLastWord_OneWord() {
    char s[] = "world";

    getStringOfWordsDifferentLastWord(s);
    ASSERT_STRING("",  s);
}

void test_getStringOfWordsDifferentLastWord_EmptyString() {
    char s[] = "";

    getStringOfWordsDifferentLastWord(s);
    ASSERT_STRING("",  s);
}

void test_getStringOfWordsDifferentLastWord_AllSpace() {
    char s[] = "   ";

    getStringOfWordsDifferentLastWord(s);
    ASSERT_STRING("",  s);
}

// Удалить из данной строки слова-палиндромы
void deletePalindrome(char *s) {
    char *beginSearch = s;
    char *sCopy = s;
    WordDescriptor curWord;

    while (getWord(beginSearch, &curWord)) {
        if (!isPalindrome(curWord.begin, curWord.end)) {
            sCopy = copy(curWord.begin, curWord.end, sCopy);
            *sCopy = ' ';
            sCopy++;
        }
        beginSearch = curWord.end;
    }

    if (sCopy != s) {
        sCopy--;
    }
    *sCopy = '\0';
}

void test_deletePalindrome_CommonCase() {
    char s[] = "dvd vse ok";
    deletePalindrome(s);

    ASSERT_STRING("vse ok", s);
}

void test_deletePalindrome_EmptyString() {
    char s[] = "";
    deletePalindrome(s);

    ASSERT_STRING("", s);
}

void testAll_TaskString() {
    test_task1_CommonCase();
    test_task1_AllSpace();
    test_task2_CommonCase();
    test_task2_OneSpace();
    test_digitToStartForEveryWord_CommonCase();
    test_digitToStartForEveryWord_digitsInWord();
    test_numberTurnIntoSpaces_CommonCase();
    test_numberTurnIntoSpaces_OnlyDigits();
    test_numberTurnIntoSpaces_OnlyLetters();
    test_isLexicallyOrderedSentence_CommonCase();
    test_isLexicallyOrderedSentence_onlySpaces();
    test_isLexicallyOrderedSentence_notOrdered();
    test_getBagOfWords_CommonCase();
    test_getBagOfWords_AllSpace();
    test_nOfPalindromeWords_commonCase();
    test_nOfPalindromeWords_NoPalindromes();
    test_nOfPalindromeWords_emptyWords();
    test_unionString_CommonCase();
    test_unionString_AllWordsInOneString();
    testAll_getWordBeforeFirstWordWithA();
    test_lastWordInFirstStringInSecondString_CommonCase();
    test_lastWordInFirstStringInSecondString_EmptyString();
    test_isEqualWord_CommonCase();
    test_isEqualWord_NoEqual();
    test_isEqualWord_EmptyString();
    test_isPairWordsFromSameLetters_CommonCase();
    test_isPairWordsFromSameLetters_EmptyString();
    test_isPairWordsFromSameLetters_AllSpace();
    test_getStringOfWordsDifferentLastWord_CommonCase();
    test_getStringOfWordsDifferentLastWord_OneWord();
    test_getStringOfWordsDifferentLastWord_EmptyString();
    test_getStringOfWordsDifferentLastWord_AllSpace();
    test_deletePalindrome_CommonCase();
    test_deletePalindrome_EmptyString();
}