#include "matrix.h"
#include "../../algorithms/algorithm.h"
#include <assert.h>

matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix) {values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices,
                              int nRows, int nCols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        free(m.values[i]);
    }
    free(m.values);
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(ms[i]);
    }
    free(ms);
}

void inputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            scanf("%d", &m.values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        inputMatrix(ms[i]);
    }
}

void outputMatrix(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix m, int i1, int i2) {
    assert(i1 < m.nRows && i2 < m.nRows);

    universalSwap(&m.values[i1], &m.values[i2], sizeof(int *));
}

void swapColumns(matrix m, int j1, int j2) {
    assert(j1 < m.nCols && j2 < m.nCols);

    for (int i = 0; i < m.nRows; i++) {
        universalSwap(&m.values[i][j1], &m.values[i][j2], sizeof(int));
    }
}

void insertionSortRowsMatrixByRowCriteria(matrix m,
                                          int (*criteria)(int *, int)) {
    int *rows = (int *) malloc(sizeof(int) * m.nRows);
    for (int i = 0; i < m.nRows; i++) {
        rows[i] = criteria(m.values[i], m.nCols);
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

void insertionSortColsMatrixByColCriteria(matrix m,
                                          int (*criteria)(int *, int)) {
    int *cols = (int *) malloc(sizeof(int) * m.nCols);
    int *curCols = malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nCols; ++i) {
        for (int j = 0; j < m.nRows; ++j) {
            curCols[j] = m.values[j][i];
        }
        cols[i] = criteria(curCols, m.nRows);
    }

    for (int i = 1; i < m.nCols; ++i) {
        int j = i;
        while (j > 0 && cols[j - 1] > cols[j]) {
            swapColumns(m, j, j - 1);
            universalSwap(&cols[j], &cols[j - 1], sizeof(int));
            j--;
        }
    }

    free(cols);
    free(curCols);
}

bool isSquareMatrix(matrix m) {
    return m.nRows == m.nCols;
}

bool areTwoMatricesEqual(matrix m1, matrix m2) {
    if (m1.nRows != m2.nRows || m1.nCols != m2.nCols) {
        return false;
    }

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m1.nCols; j++) {
            if (m1.values[i][j] != m2.values[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool isEMatrix(matrix m) {
    if (!isSquareMatrix(m)) {
        return false;
    }

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (i == j && m.values[i][j] != 1 || i != j && m.values[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}

bool isSymmetricMatrix(matrix m) {
    if (!isSquareMatrix(m)) {
        return false;
    }

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (i != j && m.values[i][j] != m.values[j][i]) {
                return false;
            }
        }
    }

    return true;
}

void transposeSquareMatrix(matrix m) {
    if (!isSquareMatrix(m)) {
        fprintf(stderr, "Not a square matrix");
        exit(1);
    }

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < i; j++) {
            universalSwap(&m.values[i][j], &m.values[j][i], sizeof(int));
        }
    }
}

position getMinValuePos(matrix m) {
    position minElementPos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            position curPos = {i, j};
            if (m.values[minElementPos.rowIndex][minElementPos.colIndex] >
                m.values[curPos.rowIndex][curPos.colIndex]) {
                minElementPos = curPos;
            }
        }
    }

    return minElementPos;
}

position getMaxValuePos(matrix m) {
    position maxElementPos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            position curPos = {i, j};
            if (m.values[maxElementPos.rowIndex][maxElementPos.colIndex] <
                m.values[curPos.rowIndex][curPos.colIndex]) {
                maxElementPos = curPos;
            }
        }
    }

    return maxElementPos;
}

matrix createMatrixFromArray(const int *a, int nRows,
                             int nCols) {
    matrix m = getMemMatrix(nRows, nCols);

    int k = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            m.values[i][j] = a[k++];

    return m;
}

matrix *createArrayOfMatrixFromArray(const int *values, int nMatrices,
                                     int nRows, int nCols) {

    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    int l = 0;
    for (int k = 0; k < nMatrices; k++)
        for (int i = 0; i < nRows; i++)
            for (int j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];

    return ms;
}