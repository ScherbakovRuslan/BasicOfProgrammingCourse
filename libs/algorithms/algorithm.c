#include "algorithm.h"

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;

    return 0;
}

void universalSwap(void *a, void *b, size_t size) {
    char *a1 = a;
    char *b1 = b;
    for (int i = 0; i < size; i++) {
        char t = *a1;
        *a1 = *b1;
        *b1 = t;

        a1++;
        b1++;
    }
}