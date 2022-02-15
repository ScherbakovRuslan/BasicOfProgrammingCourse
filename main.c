#include <stdio.h>
#include <stdint.h>
#include "libs/data_structures/vector/vector.h"
#include "libs/data_structures/matrix/matrix.h"
#include "libs/data_structures/matrix/matrixTest.h"
#include "libs/algorithms/algorithm.h"
#include <assert.h>
#include <malloc.h>

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

int getMax(int *a, int n) {
    int max = a[0];
    for(int i = 1; i < n; i++) {
        if(a[i] > max) {
            max = a[i];
        }
    }

    return max;
}

void sortRowsByMaxElement(matrix m) {
    int *rows = (int *) malloc(sizeof(int) * m.nRows);
    for (int i = 0; i < m.nRows; i++) {
        rows[i] = getMax(m.values[i], m.nCols);
    }

    for (int i = 1; i < m.nRows; i++) {
        int j = i;
        while (j > 0 && rows[j - 1] > rows[j]) {
            swapRows(m, j, j - 1);
            universalSwap(&rows[j], &rows[j - 1], sizeof(int));
            j--;
        }
    }

    free(rows);
}

void task2(matrix m) {
    sortRowsByMaxElement(m);
}

void test_task2() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              3, 2, 3}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {3, 2, 3,
                                                7, 1, 2,
                                                1, 8, 1}, 3, 3);
    task2(m);

    assert(areTwoMatricesEqual(res, m));
}

int main() {
    test_task1_CommonCase();
    test_task1_minAndMaxInOneLine();
    test_task2();

    return 0;
}
