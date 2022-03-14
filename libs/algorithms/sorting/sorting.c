#include "sorting.h"
#include "../array/array.h"

double getTime() {
    clock_t start_time = clock();
    // фрагмент кода
    // время которого измеряется
    clock_t end_time = clock();\
    clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}

void timeExperiment() {
    // описание функций сортировки
    SortFunc sorts[] = {
            {bubbleSort,    "bubbleSort"},
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {combSort,      "combSort"},
            {shellSort,     "shellSort"},
            {radixSort,     "radixSort"},
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            // генерируется случайный массив
            {generateRandomArray,      "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray,     "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time ",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }
}

void checkTime(void (*sortFunc )(int *, size_t),
               void (*generateFunc )(int *, size_t),
               size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf(" Name : %s\n", experimentName);
    // замер времени
    double time;
    TIME_TEST ({
                   sortFunc(innerBuffer, size);
               }, time);
    // результаты замера
    printf(" Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n", time);

        // запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf(" Wrong !\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
    }
}

void checkNComps(long long (*sortFunc )(int *, size_t),
                 void (*generateFunc )(int *, size_t),
                 size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf(" Name : %s\n", experimentName);

    // получение количества операций
    long long nComps = sortFunc(innerBuffer, size);

    // результаты
    printf(" Status : ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! NComps : %.3lld.\n", nComps);

        // запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf(" FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3lld\n", size, nComps);
        fclose(f);
    } else {
        printf(" Wrong !\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
    }
}

void NCompsExperiment() {
    // описание функций сортировки
    SortFuncNComps sorts[] = {
            {getBubbleSortNComp, "getBubbleSortNComp"},
            {getSelectionSortNComp, "getSelectionSortNComp"},
            {getInsertionSortNComp, "getInsertionSortNComp"},
            {getCombSortNComp, "getCombSortNComp"},
            {getShellSortNComp, "getShellSortNComp"},
            {getRadixSortNComp, "getRadixSortNComp"}

    };

    const unsigned FUNCS_N = ARRAY_SIZE
                             (sorts);
    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            // генерируется случайный массив
            {generateRandomArray,      "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray,     " ordered "},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE
                             (generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename,
                        "%s_%s_nComps ",
                        sorts[i].name, generatingFuncs[j].name);
                checkNComps(sorts[i].sort,
                            generatingFuncs[j].generate,
                            size, filename);
            }
        }
        printf("\n");
    }
}


void generateRandomArray(int *a, size_t n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        a[i] = rand();
    }
}

void generateOrderedArray(int *a, size_t n) {
    for (size_t i = 0; i < n; i++)
        a[i] = i;
}

void generateOrderedBackwards(int *a, size_t n) {
    for (size_t i = n - 1; i > 0; i--)
        a[i] = n - i;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubbleSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = size - 1; j > i; j--) {
            if (a[j - 1] > a[j]) {
                swap(&a[j - 1], &a[j]);
            }
        }
    }
}

void selectionSort(int *a, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < size; j++)
            if (a[j] < a[minPos]) {
                minPos = j;
            }
        swap(&a[i], &a[minPos]);
    }
}

void insertionSort(int *a, size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void combSort(int *a, size_t size) {
    size_t step = size;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1) {
            step /= 1.24733;
        }
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
}

void shellSort(int *a, size_t n) {
    int tmp, j;
    for (int step = n / 2; step > 0; step /= 2) {
        for (int i = step; i < n; i++) {
            tmp = a[i];
            for (j = i; j >= step; j -= step) {
                if (tmp < a[j - step]) {
                    a[j] = a[j - step];
                } else {
                    break;
                }
            }
            a[j] = tmp;
        }
    }
}

int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

void radixSort(int *a, size_t n) {
    int *l = a;
    int *r = a + n;
    int N = 8;
    int k = (32 + N - 1) / N;
    int M = 1 << N;
    int *b = (int *) malloc(sizeof(int) * n);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < M; j++) {
            c[j] = 0;
        }

        for (int *j = l; j < r; j++) {
            c[digit(*j, i, N, M)]++;
        }

        for (int j = 1; j < M; j++) {
            c[j] += c[j - 1];
        }

        for (int *j = r - 1; j >= l; j--) {
            b[--c[digit(*j, i, N, M)]] = *j;
        }

        int cur = 0;
        for (int *j = l; j < r; j++) {
            *j = b[cur++];
        }
    }
    free(b);
    free(c);
}

long long getBubbleSortNComp(int *a, size_t size) {
    long long nComps = 0;
    for (size_t i = 0; ++nComps && i < size - 1; i++) {
        for (size_t j = size - 1; ++nComps && j > i; j--) {
            if (++nComps && a[j - 1] > a[j]) {
                swap(&a[j - 1], &a[j]);
            }
        }
    }

    return nComps;
}

long long getSelectionSortNComp(int *a, size_t size) {
    long long nComps = 0;
    for (int i = 0; ++nComps && i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; ++nComps && j < size; j++)
            if (++nComps && a[j] < a[minPos]) {
                minPos = j;
            }
        swap(&a[i], &a[minPos]);
    }

    return nComps;
}

long long getInsertionSortNComp(int *a, size_t size) {
    long long nComps = 0;
    for (size_t i = 1; ++nComps && i < size; i++) {
        int t = a[i];
        int j = i;
        while (++nComps && j > 0 && ++nComps && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }

    return nComps;
}

long long getCombSortNComp(int *a, size_t size) {
    long long nComps = 0;
    size_t step = size;
    int swapped = 1;
    while (++nComps && step > 1 || swapped) {
        if (step > 1) {
            step /= 1.24733;
        }
        swapped = 0;
        for (size_t i = 0, j = i + step; ++nComps && j < size; ++i, ++j)
            if (++nComps && a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }

    return nComps;
}

long long getShellSortNComp(int *a, size_t n) {
    long long nComps = 0;
    int tmp, j;
    for (int step = n / 2; ++nComps && step > 0; step /= 2) {
        for (int i = step; ++nComps && i < n; i++) {
            tmp = a[i];
            for (j = i; ++nComps && j >= step; j -= step) {
                if (++nComps && tmp < a[j - step]) {
                    a[j] = a[j - step];
                } else {
                    break;
                }
            }
            a[j] = tmp;
        }
    }

    return nComps;
}

long long getRadixSortNComp(int *a, size_t n) {
    long long nComps = 0;
    int *l = a;
    int *r = a + n;
    int N = 8;
    int k = (32 + N - 1) / N;
    int M = 1 << N;
    int *b = (int *) malloc(sizeof(int) * n);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; ++nComps && i < k; i++) {
        for (int j = 0; ++nComps && j < M; j++) {
            c[j] = 0;
        }

        for (int *j = l; ++nComps && j < r; j++) {
            c[digit(*j, i, N, M)]++;
        }

        for (int j = 1; ++nComps && j < M; j++) {
            c[j] += c[j - 1];
        }

        for (int *j = r - 1; ++nComps && j >= l; j--) {
            b[--c[digit(*j, i, N, M)]] = *j;
        }

        int cur = 0;
        for (int *j = l; ++nComps && j < r; j++) {
            *j = b[cur++];
        }
    }
    free(b);
    free(c);

    return nComps;
}
