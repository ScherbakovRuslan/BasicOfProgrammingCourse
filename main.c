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
    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }

    return max;
}

void sortRowsByMaxElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
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

int getMin(int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }

    return min;
}

void sortColsByMinElement(matrix m) {
    insertionSortColsMatrixByColCriteria(m, getMin);
}

void task3(matrix m) {
    sortColsByMinElement(m);
}

void test_task3() {
    matrix m = createMatrixFromArray((int[]) {3, 5, 2, 4, 3, 3,
                                              2, 5, 1, 8, 2, 7,
                                              6, 1, 4, 4, 8, 3}, 3, 6);
    matrix res = createMatrixFromArray((int[]) {5, 2, 3, 3, 3, 4,
                                                5, 1, 2, 2, 7, 8,
                                                1, 4, 6, 8, 3, 4}, 3, 6);
    task3(m);

    assert(areTwoMatricesEqual(res, m));
}

matrix mulMatrices(matrix m1, matrix m2) {
    matrix m = getMemMatrix(m1.nRows, m1.nCols);

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m1.nCols; j++) {
            m.values[i][j] = 0;
            for (int rows = 0; rows < m2.nRows; rows++) {
                m.values[i][j] += m1.values[i][rows] * m2.values[rows][j];
            }
        }
    }

    return m;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(*m)) {
        *m = mulMatrices(*m, *m);
    }
}

void task4(matrix *m) {
    getSquareOfMatrixIfSymmetric(m);
}

void test_task4() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 1,
                                              2, 1, 3,
                                              1, 3, 1}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {6, 7, 8,
                                                7, 14, 8,
                                                8, 8, 11}, 3, 3);
    task4(&m);

    assert(areTwoMatricesEqual(res, m));
}

bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                return false;
            }
        }
    }

    return true;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long *a = malloc(sizeof(long long) * m.nRows);
    for (int i = 0; i < m.nRows; i++) {
        a[i] = getSum(m.values[i], m.nCols);
    }

    if (isUnique(a, m.nRows)) {
        transposeSquareMatrix(m);
    }
}

void task5(matrix m) {
    if (isSquareMatrix(m)) {
        transposeIfMatrixHasNotEqualSumOfRows(m);
    }
}

void test_task5() {
    matrix m = createMatrixFromArray((int[]) {1, 1, 1,
                                              1, 1, 2,
                                              1, 1, 3}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {1, 1, 1,
                                                1, 1, 1,
                                                1, 2, 3}, 3, 3);
    task5(m);

    assert(areTwoMatricesEqual(res, m));
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    if(isEMatrix(mulMatrices(m1, m2))) {
        return true;
    }

    return false;
}

bool task6(matrix m1, matrix  m2) {
    return isMutuallyInverseMatrices(m1, m2);
}

void test_task6() {
    matrix m1 = createMatrixFromArray((int[]) {1, 2,
                                               2, 3}, 2, 2);
    matrix m2 = createMatrixFromArray((int[]) {-3, 2,
                                               2, -1}, 2, 2);

    assert(task6(m1, m2) == true);
}

int max(int a, int b) {
    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    int sum = 0;
    for(int i = 1; i < m.nRows; i++) {
        int rIndex = i;
        int cIndex = 0;
        int maxElement = m.values[rIndex][cIndex];
        while (cIndex < m.nCols &&  rIndex < m.nRows) {
            if(m.values[rIndex][cIndex] > maxElement) {
                maxElement = m.values[rIndex][cIndex];
            }
            cIndex++;
            rIndex++;
        }

        sum += maxElement;
    }

    for (int i = 1; i < m.nCols; i++) {
        int rIndex = 0;
        int cIndex = i;
        int maxElement = m.values[rIndex][cIndex];
        while (cIndex < m.nCols && rIndex < m.nRows) {
            if (m.values[rIndex][cIndex] > maxElement) {
                maxElement = m.values[rIndex][cIndex];
            }
            cIndex++;
            rIndex++;
        }
        sum += maxElement;
    }

    return sum;
}

long long task7(matrix m) {
    return findSumOfMaxesOfPseudoDiagonal(m);
}

void test_task7() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 5, 4,
                                              1, 3, 6, 3,
                                              3, 2, 1, 2}, 3, 4);
    long long res = task7(m);

    assert(res == 20);
}

int getMinInArea(matrix m) {
    position posMaxElement = getMaxValuePos(m);

    int rIndex = posMaxElement.rowIndex;

    int lCol = posMaxElement.colIndex;
    int rCol = posMaxElement.colIndex;

    int min = m.values[posMaxElement.rowIndex][posMaxElement.colIndex];
    while (rIndex >= 0) {
        int i = lCol;
        while (i < rCol) {
            if(m.values[rIndex][i] < min) {
                min = m.values[rIndex][i];
            }
            i++;
        }

        if(lCol > 0) {
            lCol--;
        }
        if(rCol + 1 < m.nCols) {
            rCol++;
        }
        rIndex--;
    }

    return min;
}

int task8(matrix m) {
    return getMinInArea(m);
}

void test_task8() {
    matrix m = createMatrixFromArray((int[]) {10, 7, 5, 6,
                                              3, 11, 8, 9,
                                              4, 1, 12, 2}, 3, 4);
    long long res = task8(m);

    assert(res == 5);
}

int main() {
    test_task1_CommonCase();
    test_task1_minAndMaxInOneLine();
    test_task2();
    test_task3();
    test_task4();
    test_task5();
    test_task6();
    test_task7();
    test_task8();

    return 0;
}
