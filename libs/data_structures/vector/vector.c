#include "vector.h"
#include <stdlib.h>
#include <malloc.h>

vector createVector(size_t n) {
    return (vector) {(int *)malloc(sizeof(int) * n), 0, n};
}

void reserve(vector *v, size_t newCapacity) {
    v->capacity = newCapacity;
    if(newCapacity == 0) {
        v->data = NULL;
        v->size = 0;
    } else if(newCapacity < v->size) {
        v->size = newCapacity;
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    v->capacity = v->size;
}

void deleteVector(vector *v) {
    v->size = 0;
    v->capacity = 0;
    free(v->data);
}