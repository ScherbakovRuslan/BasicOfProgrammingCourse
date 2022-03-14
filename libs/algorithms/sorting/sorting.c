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
            {bubbleSort, "bubbleSort"},
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {combsort, "combsort"},
            {ShellSort, "ShellSort"}
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
    for (size_t i = n; i > 0; i--)
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

void combsort(int *a, const size_t size) {
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

void ShellSort(int *a, size_t n) {
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