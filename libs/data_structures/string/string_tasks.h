#ifndef INC_1_STRING_TASKS_H
#define INC_1_STRING_TASKS_H

#include "string_.h"
#include <stdbool.h>

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line);

char *getEndOfString(char *s);

void removeNonLetters(char *s);

// удалит из строки все пробельные символы
void task1(char *s);

void test_task1_CommonCase();

void test_task1_AllSpace();

// Сокращает количество пробелов между
// словами данного предложения до одного
void removeExtraSpaces(char *s);

void test_task2_CommonCase();

void test_task2_OneSpace();

int getWord(char *beginSearch, WordDescriptor *word);

// Преобразовать строку таким образом, чтобы цифры каждого слова были
// перенесены в начало слова без изменения порядка следования их в слове,
// буквы перенести в конец слова.
void digitToStartWithSavingOrder(WordDescriptor word);

void digitToStartForEveryWord(char *s);

void test_digitToStartForEveryWord_CommonCase();

void test_digitToStartForEveryWord_digitsInWord();

// Преобразовать строку, заменяя каждую цифру соответствующим ей числом
// пробелов
void replacingNumberWithSpaces(char *s);

void test_numberTurnIntoSpaces_CommonCase();

void test_numberTurnIntoSpaces_OnlyDigits();

void test_numberTurnIntoSpaces_OnlyLetters();

// Заменить все вхождения слова 𝑤1 на слово 𝑤2
void replace(char *source, char *w1, char *w2);

void test_replace_CommonCase();

int areWordsEqual(WordDescriptor w1,
                  WordDescriptor w2);

// Определить, упорядочены ли лексикографически слова данного предложения
bool isLexicallyOrderedSentence(char *s);

void test_isLexicallyOrderedSentence_CommonCase();

void test_isLexicallyOrderedSentence_onlySpaces();

void test_isLexicallyOrderedSentence_notOrdered();

#endif //INC_1_STRING_TASKS_H
