#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"
#include "libs/data_structures/matrix/matrixTest.h"

#include <assert.h>

void test_pushBack_emptyVector() {
    vector v = createVector(3);
    pushBack(&v, 3);

    assert(v.size == 1);
}

void test_pushBack_fullVector() {
    vector v = createVector(3);
    v.size = 3;
    pushBack(&v, 3);

    assert(v.size == 4);
    assert(v.capacity == 6);
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);

    assert(v.size == 1);

    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_atVector_notEmptyVector() {
    vector v = createVector(3);
    v.size = 3;

    assert(atVector(&v, 1) == &v.data[1]);
}

void test_atVector_requestToLastElement() {
    vector v = createVector(3);
    v.size = 3;

    assert(atVector(&v, 2) == &v.data[2]);
}

void test_back_oneElementInVector() {
    vector v = createVector(1);
    v.size = 1;

    assert(back(&v) == &v.data[0]);
}

void test_front_oneElementInVector() {
    vector v = createVector(1);
    v.size = 1;

    assert(front(&v) == &v.data[0]);
}

void task1(matrix m) {
    position max = getMaxValuePos(m);
    position min = getMinValuePos(m);

    swapRows(m, max.rowIndex, min.rowIndex);
}

void test_task1_CommonCase() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {7, 8, 9,
                                                4, 5, 6,
                                                1, 2, 3}, 3, 3);
    task1(m);

    assert(areTwoMatricesEqual(res, m));
}

void test_task1_minAndMaxInOneLine() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 9,
                                              4, 5, 6,
                                              7, 8, 3}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {1, 2, 9,
                                                4, 5, 6,
                                                7, 8, 3}, 3, 3);
    task1(m);

    assert(areTwoMatricesEqual(res, m));
}

int main() {
    test_task1_CommonCase();
    test_task1_minAndMaxInOneLine();

    return 0;
}
