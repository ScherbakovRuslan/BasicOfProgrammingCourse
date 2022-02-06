#include "unordered_array.h"

unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

unordered_array_set unordered_array_set_create_from_array(
        const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++) {
        unordered_array_set_insert(&set, a[i]);
    }

    return set;
}

size_t unordered_array_set_in(unordered_array_set *set, int value) {
    return linearSearch_(set->data, set->size, value);
}

bool unordered_array_set_isEqual(
        unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size) {
        return false;
    }
    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(&set1, set1.data[i]) == set2.size) {
            return false;
        }
    }
    return true;
}

void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}

void unordered_array_set_insert(
        unordered_array_set *set, int value) {
    if (unordered_array_set_in(set, value) == set->size) {
        unordered_array_set_isAbleAppend(set);
        append_(set->data, &set->size, value);
    }
}

void unordered_array_set_deleteElement(
        unordered_array_set *set, int value) {
    size_t posDeleteElement = linearSearch_(set->data, set->size, value);
    if (posDeleteElement < set->size) {
        set->data[posDeleteElement] = set->data[set->size - 1];
        set->size--;
    }
}

unordered_array_set unordered_array_set_union(
        unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set setUnion = unordered_array_set_create(
            set1.size + set2.size);
    setUnion.size = set1.size;

    memcpy(setUnion.data, set1.data, set1.size * sizeof(int));

    for (size_t i = 0; i < set2.size; i++) {
        int value = set2.data[i];
        int pos = linearSearch_(setUnion.data, setUnion.size, value);

        if (pos == setUnion.size) {
            append_(setUnion.data, &setUnion.size, value);
        }
    }

    return setUnion;
}

unordered_array_set unordered_array_set_intersection(
        unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set setIntersection = unordered_array_set_create(set1.size);

    for (size_t i = 0; i < set1.size; i++) {
        int value = set1.data[i];
        if (unordered_array_set_in(&set2, value) != set2.size) {
            append_(setIntersection.data, &setIntersection.size, value);
        }
    }

    return setIntersection;
}

unordered_array_set unordered_array_set_difference(
        unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set setDifference = set1;
    for (size_t i = 0; i < set2.size; i++) {
        int value = set2.data[i];
        unordered_array_set_deleteElement(&setDifference, value);
    }

    return setDifference;
}

unordered_array_set unordered_array_set_symmetricDifference(
        unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set setDif1 = unordered_array_set_difference(set1, set2);
    unordered_array_set setDif2 = unordered_array_set_difference(set2, set1);
    unordered_array_set setSymmetricDifference = unordered_array_set_union(
            setDif1, setDif2);

    unordered_array_set_delete(setDif1);
    unordered_array_set_delete(setDif2);

    return setSymmetricDifference;
}

unordered_array_set unordered_array_set_complement(
        unordered_array_set set, unordered_array_set universumSet) {
    return unordered_array_set_difference(universumSet, set);
}

void unordered_array_set_print(unordered_array_set set) {
    printf("{");
    for (size_t i = 0; i < set.size; i++) {
        printf("%d ", set.data[i]);
    }

    printf("\b}\n");
}

void unordered_array_set_delete(unordered_array_set set) {
    free(set.data);
    set.size = 0;
    set.capacity = 0;
}

