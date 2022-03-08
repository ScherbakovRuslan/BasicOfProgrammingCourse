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
    test_isEqualWord_CommonCase();
    test_isEqualWord_NoEqual();
    test_isEqualWord_EmptyString();

    return 0;
}
