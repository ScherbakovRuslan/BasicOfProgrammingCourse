#include "libs/algorithms/array/unordered_array.h"

void test_unordered_array_set_in1() {
    unordered_array_set set = unordered_array_set_create_from_array(
            (int[]) {1, 4, 3, 2}, 4);
    int value = 3;
    int index = 2;
    size_t res = unordered_array_set_in(&set, value);
    assert(res == index);
}

void test_unordered_array_set_in2() {
    unordered_array_set set = unordered_array_set_create_from_array(
            (int[]) {1, 4, 3, 2}, 4);
    int value = 5;
    int index = 4;
    size_t res = unordered_array_set_in(&set, value);
    assert(res == index);
}

void test_unordered_array_set_in3() {
    unordered_array_set set = unordered_array_set_create_from_array(
            (int[]) {1, 4, 3, 2}, 4);
    int value = 1;
    int index = 0;
    size_t res = unordered_array_set_in(&set, value);
    assert(res == index);
}

void test_unordered_array_set_in() {
    test_unordered_array_set_in1();
    test_unordered_array_set_in2();
    test_unordered_array_set_in3();
}

void test_unordered_array_set_insert1() {
    unordered_array_set set = unordered_array_set_create(5);
    unordered_array_set_insert(&set, 5);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {5}, 1);
    assert(unordered_array_set_isEqual(set, res));
    unordered_array_set_delete(set);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_insert2() {
    unordered_array_set set = unordered_array_set_create(5);
    unordered_array_set_insert(&set, 5);
    unordered_array_set_insert(&set, 5);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {5, 5}, 2);
    assert(unordered_array_set_isEqual(set, res));
    unordered_array_set_delete(set);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_insert3() {
    unordered_array_set set = unordered_array_set_create(6);
    unordered_array_set_insert(&set, 5);
    unordered_array_set_insert(&set, 5);
    unordered_array_set_insert(&set, 6);
    unordered_array_set_insert(&set, 1);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {1, 5, 6, 5}, 4);
    assert(unordered_array_set_isEqual(set, res));
    unordered_array_set_delete(set);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_insert() {
    test_unordered_array_set_insert1();
    test_unordered_array_set_insert2();
    test_unordered_array_set_insert3();
}

void test_unordered_array_set_deleteElement1() {
    unordered_array_set set = unordered_array_set_create_from_array(
            (int[]) {5, 2, 4}, 3);
    unordered_array_set_deleteElement(&set, 2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {5, 4}, 2);
    assert(unordered_array_set_isEqual(set, res));
    unordered_array_set_delete(set);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_deleteElement2() {
    unordered_array_set set = unordered_array_set_create_from_array(
            (int[]) {5, 2, 4}, 3);
    unordered_array_set_deleteElement(&set, 2);
    unordered_array_set_deleteElement(&set, 5);
    unordered_array_set_deleteElement(&set, 4);
    unordered_array_set res = unordered_array_set_create(0);
    assert(unordered_array_set_isEqual(set, res));
    unordered_array_set_delete(set);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_deleteElement3() {
    unordered_array_set set = unordered_array_set_create_from_array(
            (int[]) {6, 5, 2, 4}, 4);
    unordered_array_set_deleteElement(&set, 2);
    unordered_array_set_deleteElement(&set, 5);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {4, 6}, 2);
    assert(unordered_array_set_isEqual(set, res));
    unordered_array_set_delete(set);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_deleteElement() {
    test_unordered_array_set_deleteElement1();
    test_unordered_array_set_deleteElement2();
    test_unordered_array_set_deleteElement3();
}

void test_unordered_array_set_union1() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create(0);
    unordered_array_set unionSet = unordered_array_set_union(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    assert(unordered_array_set_isEqual(unionSet, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(unionSet);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_union2() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set unionSet = unordered_array_set_union(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    assert(unordered_array_set_isEqual(unionSet, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(unionSet);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_union3() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array(
            (int[]) {1, 5, 3}, 3);
    unordered_array_set unionSet = unordered_array_set_union(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3, 5}, 4);
    assert(unordered_array_set_isEqual(unionSet, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(unionSet);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_union() {
    test_unordered_array_set_union1();
    test_unordered_array_set_union2();
    test_unordered_array_set_union3();
}

void test_unordered_array_set_intersection1() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array(
            (int[]) {1, 5, 3}, 3);
    unordered_array_set unionSet = unordered_array_set_intersection(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {1, 3}, 2);
    assert(unordered_array_set_isEqual(unionSet, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(unionSet);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_intersection2() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set unionSet = unordered_array_set_intersection(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    assert(unordered_array_set_isEqual(unionSet, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(unionSet);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_intersection3() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create(0);
    unordered_array_set unionSet = unordered_array_set_intersection(set1, set2);
    unordered_array_set res = unordered_array_set_create(0);
    assert(unordered_array_set_isEqual(unionSet, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(unionSet);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_intersection() {
    test_unordered_array_set_intersection1();
    test_unordered_array_set_intersection2();
    test_unordered_array_set_intersection3();
}

void test_unordered_array_set_difference1() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create(0);
    unordered_array_set setDif = unordered_array_set_difference(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    assert(unordered_array_set_isEqual(setDif, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(setDif);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_difference2() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array(
            (int[]) {3, 2, 1}, 3);
    unordered_array_set setDif = unordered_array_set_difference(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {}, 0);
    assert(unordered_array_set_isEqual(setDif, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(setDif);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_difference3() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array(
            (int[]) {1, 5, 6}, 3);
    unordered_array_set setDif = unordered_array_set_difference(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {2, 3}, 2);
    assert(unordered_array_set_isEqual(setDif, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(setDif);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_difference() {
    test_unordered_array_set_difference1();
    test_unordered_array_set_difference2();
    test_unordered_array_set_difference3();
}

void test_unordered_array_set_symmetricDifference1() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array(
            (int[]) {1, 5, 6}, 3);
    unordered_array_set setSymmetricDif = unordered_array_set_symmetricDifference(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {2, 3, 5, 6}, 4);
    assert(unordered_array_set_isEqual(setSymmetricDif, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(setSymmetricDif);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_symmetricDifference2() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array(
            (int[]) {1, 3, 2}, 3);
    unordered_array_set setSymmetricDif = unordered_array_set_symmetricDifference(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {}, 0);
    assert(unordered_array_set_isEqual(setSymmetricDif, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(setSymmetricDif);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_symmetricDifference3() {
    unordered_array_set set1 = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array(
            (int[]) {}, 0);
    unordered_array_set setSymmetricDif = unordered_array_set_symmetricDifference(set1, set2);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    assert(unordered_array_set_isEqual(setSymmetricDif, res));
    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(setSymmetricDif);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_symmetricDifference() {
    test_unordered_array_set_symmetricDifference1();
    test_unordered_array_set_symmetricDifference2();
    test_unordered_array_set_symmetricDifference3();
}

void test_unordered_array_set_complement1() {
    unordered_array_set set = unordered_array_set_create_from_array(
            (int[]) {1}, 1);
    unordered_array_set universum = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set setComplement = unordered_array_set_complement(set, universum);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {2, 3}, 2);
    assert(unordered_array_set_isEqual(setComplement, res));
    unordered_array_set_delete(set);
    unordered_array_set_delete(universum);
    unordered_array_set_delete(setComplement);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_complement2() {
    unordered_array_set set = unordered_array_set_create_from_array(
            (int[]) {1, 2}, 2);
    unordered_array_set universum = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set setComplement = unordered_array_set_complement(set, universum);
    unordered_array_set res = unordered_array_set_create_from_array(
            (int[]) {3}, 1);
    assert(unordered_array_set_isEqual(setComplement, res));
    unordered_array_set_delete(set);
    unordered_array_set_delete(universum);
    unordered_array_set_delete(setComplement);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_complement3() {
    unordered_array_set set = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set universum = unordered_array_set_create_from_array(
            (int[]) {1, 2, 3}, 3);
    unordered_array_set setComplement = unordered_array_set_complement(set, universum);
    unordered_array_set res = unordered_array_set_create(0);
    assert(unordered_array_set_isEqual(setComplement, res));
    unordered_array_set_delete(set);
    unordered_array_set_delete(universum);
    unordered_array_set_delete(setComplement);
    unordered_array_set_delete(res);
}

void test_unordered_array_set_complement() {
    test_unordered_array_set_complement1();
    test_unordered_array_set_complement2();
    test_unordered_array_set_complement3();
}

void test() {
    test_unordered_array_set_in();
    test_unordered_array_set_insert();
    test_unordered_array_set_deleteElement();
    test_unordered_array_set_union();
    test_unordered_array_set_intersection();
    test_unordered_array_set_difference();
    test_unordered_array_set_complement();
}

int main() {
    test();

    return 0;
}