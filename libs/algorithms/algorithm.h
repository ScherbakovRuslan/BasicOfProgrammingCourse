#ifndef INC_1_ALGORITHMS_H
#define INC_1_ALGORITHMS_H

#include <stdlib.h>

//возвращает 1, если число по адресу a больше числа по адресу b
//возвращает -1, если число по адресу a меньше числа по адресу b
//возвращает 0, если числа равны
int compare_ints(const void *a, const void *b);

void universalSwap(void *a, void *b, size_t size);

#endif //INC_1_ALGORITHMS_H
