#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"
#include "libs/data_structures/matrix/matrixTest.h"
#include "libs/algorithms/algorithm.h"
#include <assert.h>
#include <malloc.h>
#include <math.h>
#include "libs/data_structures/string/string_.h"
#include "libs/data_structures/string/string_test.h"
#include "libs/data_structures/string/string_tasks.h"

int main() {
    test_string();
    test_task1_CommonCase();
    test_task1_AllSpace();
    test_task2_CommonCase();
    test_task2_OneSpace();
    test_digitToStartForEveryWord_CommonCase();
    test_digitToStartForEveryWord_digitsInWord();
    test_numberTurnIntoSpaces_CommonCase();
    test_numberTurnIntoSpaces_OnlyDigits();
    test_numberTurnIntoSpaces_OnlyLetters();

    return 0;
}
