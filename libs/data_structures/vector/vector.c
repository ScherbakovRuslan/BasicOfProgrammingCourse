#include "vector.h"
#include <stdlib.h>
#include <malloc.h>

vector createVector(size_t n) {
    if (n > SIZE_MAX) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return (vector) {(int *) malloc(sizeof(int) * n), 0, n};
}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        v->data = NULL;
        return;
    } else if (newCapacity < v->size) {
        v->size = newCapacity;
    } else {
        realloc(v->data, sizeof(int) * newCapacity);
    }
    v->capacity = newCapacity;
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

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    return v->data[i];
}

void pushBack(vector *v, int x) {
    if (v->capacity == 0) {
        reserve(v, 1);
    } else if (isFull(v)) {
        reserve(v, v->capacity * 2);
    }
    v->data[v->size] = x;
    v->size++;
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    } else {
        v->size--;
    }
}

int *atVector(vector *v, size_t index) {
    if (index > v->size - 1) {
        fprintf(stderr, "IndexError: a[%lld] is not exists", index);
        exit(1);
    }

    return v->data + index;
}

int *back(vector *v) {
    return v->data + v->size - 1;
}

int *front(vector *v) {
    return v->data;
}
