#include "vector.h"
#include <stdlib.h>
#include <malloc.h>

vector createVector(size_t n) {
    if(n > SIZE_MAX) {
        fprintf(stderr,"bad alloc");
        exit(1);
    }
    return (vector) {(int *) malloc(sizeof(int) * n), 0, n};
}

void reserve(vector *v, size_t newCapacity) {
    if(newCapacity > SIZE_MAX) {
        fprintf(stderr,"bad alloc");
        exit(1);
    }
    if (newCapacity == 0) {
        v->data = NULL;
        v->size = 0;
        v->capacity = newCapacity;
    } else if (newCapacity < v->size) {
        v->size = newCapacity;
        v->capacity = newCapacity;
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    v->capacity = v->size;
}

void deleteVector(vector *v) {
    free(v);
}



