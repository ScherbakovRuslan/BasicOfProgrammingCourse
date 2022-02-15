#include "matrixTest.h"
#include "matrix.h"
#include <assert.h>

void test_swapRows_swapTheSameRows() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9}, 3, 3);

    swapRows(m, 1, 1);

    assert(areTwoMatricesEqual(res, m));

    freeMemMatrix(m);
    freeMemMatrix(res);
}

void test_swapRows_CommonCase() {
    matrix m = createMatrixFromArray((int[]) {4, 5, 6,
                                              1, 2, 3,
                                              7, 8, 9}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9}, 3, 3);

    swapRows(m, 0, 1);

    assert(areTwoMatricesEqual(res, m));

    freeMemMatrix(m);
    freeMemMatrix(res);
}

void test_swapColumns_swapTheSameCols() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9}, 3, 3);

    swapColumns(m, 1, 1);

    assert(areTwoMatricesEqual(res, m));

    freeMemMatrix(m);
    freeMemMatrix(res);
}

void test_swapColumns_CommonCase() {
    matrix m = createMatrixFromArray((int[]) {2, 1, 3,
                                              5, 4, 6,
                                              8, 7, 9}, 3, 3);
    matrix res = createMatrixFromArray((int[]) {1, 2, 3,
                                                4, 5, 6,
                                                7, 8, 9}, 3, 3);

    swapColumns(m, 0, 1);

    assert(areTwoMatricesEqual(res, m));

    freeMemMatrix(m);
    freeMemMatrix(res);
}

void test_areTwoMatricesEqual_equalMatrices() {
    matrix m1 = createMatrixFromArray((int[]) {1, 2, 3,
                                               4, 5, 6,
                                               7, 8, 9}, 3, 3);
    matrix m2 = createMatrixFromArray((int[]) {1, 2, 3,
                                               4, 5, 6,
                                               7, 8, 9}, 3, 3);

    assert(areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_areTwoMatricesEqual_nonEqualMatrices() {
    matrix m1 = createMatrixFromArray((int[]) {1, 2,
                                               3, 4}, 2, 2);
    matrix m2 = createMatrixFromArray((int[]) {1, 2,
                                               4, 5}, 2, 2);

    assert(!areTwoMatricesEqual(m1, m2));

    freeMemMatrix(m1);
    freeMemMatrix(m2);
}

void test_isSquareMatrix_squareMatrix() {
    matrix m = getMemMatrix(2, 2);

    assert(isSquareMatrix(m));

    freeMemMatrix(m);
}

void test_isSquareMatrix_nonSquareMatrix() {
    matrix m = getMemMatrix(3, 2);

    assert(!isSquareMatrix(m));

    freeMemMatrix(m);
}

void test_isEMatrix_identicalMatrix() {
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    assert(isEMatrix(m));

    freeMemMatrix(m);
}

void test_isEMatrix_nonIdenticalMatrix() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    assert(!isEMatrix(m));

    freeMemMatrix(m);
}

void test_isEMatrix_nonSquareMatrix() {
    matrix m = getMemMatrix(2, 3);

    assert(!isEMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix_symmetricMatrix() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              2, 5, 4,
                                              3, 4, 0}, 3, 3);

    assert(isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix_nonSymmetricMatrix() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 0,
                                              2, 5, 4,
                                              3, 4, 0}, 3, 3);

    assert(!isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_isSymmetricMatrix_nonSquareMatrix() {
    matrix m = getMemMatrix(2, 3);

    assert(!isSymmetricMatrix(m));

    freeMemMatrix(m);
}

void test_transposeSquareMatrix_CommonCase() {
    matrix m = createMatrixFromArray((int[]) {1, 2,
                                              3, 4}, 2, 2);
    matrix res = createMatrixFromArray((int[]) {1, 3,
                                                2, 4}, 2, 2);

    transposeSquareMatrix(m);

    assert(areTwoMatricesEqual(res, m));

    freeMemMatrix(m);
    freeMemMatrix(res);
}

void test_getMinValuePos_CommonCase() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 1,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    position pos = getMinValuePos(m);

    assert(pos.rowIndex == 0);
    assert(pos.colIndex == 2);

    freeMemMatrix(m);
}

void test_getMinValuePos_matrixOfUnitDimension() {
    matrix m = createMatrixFromArray((int[]) {10}, 1, 1);

    position pos = getMinValuePos(m);

    assert(pos.rowIndex == 0);
    assert(pos.colIndex == 0);

    freeMemMatrix(m);
}

void test_getMaxValuePos_CommonCase() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 1,
                                              4, 9, 6,
                                              7, 8, 5}, 3, 3);

    position pos = getMaxValuePos(m);

    assert(pos.rowIndex == 1);
    assert(pos.colIndex == 1);

    freeMemMatrix(m);
}

void test_getMaxValuePos_matrixOfUnitDimension() {
    matrix m = createMatrixFromArray((int[]) {10}, 1, 1);

    position pos = getMaxValuePos(m);

    assert(pos.rowIndex == 0);
    assert(pos.colIndex == 0);

    freeMemMatrix(m);
}

void test_matrix() {
    test_areTwoMatricesEqual_equalMatrices();
    test_areTwoMatricesEqual_nonEqualMatrices();
    test_swapRows_swapTheSameRows();
    test_swapRows_CommonCase();
    test_swapColumns_swapTheSameCols();
    test_swapColumns_CommonCase();
    test_isSquareMatrix_squareMatrix();
    test_isSquareMatrix_nonSquareMatrix();
    test_isEMatrix_identicalMatrix();
    test_isEMatrix_nonIdenticalMatrix();
    test_isEMatrix_nonSquareMatrix();
    test_isSymmetricMatrix_symmetricMatrix();
    test_isSymmetricMatrix_nonSymmetricMatrix();
    test_isSymmetricMatrix_nonSquareMatrix();
    test_transposeSquareMatrix_CommonCase();
    test_getMinValuePos_matrixOfUnitDimension();
    test_getMinValuePos_CommonCase();
    test_getMaxValuePos_matrixOfUnitDimension();
    test_getMaxValuePos_CommonCase();
}
