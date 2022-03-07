#ifndef INC_1_STRING_TASKS_H
#define INC_1_STRING_TASKS_H

#include "string_.h"

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

#endif //INC_1_STRING_TASKS_H
