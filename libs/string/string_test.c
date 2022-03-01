#include "string_test.h"
#include "string_.h"
#include <assert.h>

void test_findNonSpace_CommonCase() {
    char* c = "  rth";

    assert(c + 2 == findNonSpace(c));
}

void test_findNonSpace_AllSpace() {
    char* c = "   ";

    assert(c + 3 == findNonSpace(c));
}

void test_findNonSpace_AllSymbol() {
    char* c = "ethy";

    assert(c == findNonSpace(c));
}

void test_findSpace_CommonCase() {
    char* c = "re ty";

    assert(c + 2 == findSpace(c));
}

void test_findSpace_NonSpace() {
    char* c = "rety";

    assert(c + 4 == findSpace(c));
}

void test_findNonSpaceReverse_CommonCase() {
    char* c = "re ty66 7";

    assert(c + 7 == findNonSpaceReverse(c + 9, c));
}

void test_findNonSpaceReverse_NonSpace() {
    char* c = "reyty66k7";

    assert(c == findNonSpaceReverse(c + 9, c));
}

void test_strcmp_CommonCase() {
    char* a = "1234";
    char* b = "1233";
    int res = strcmp(a, b);

    assert(1 == res);
}

void test_strcmp_StrEqual() {
    char* a = "1234";
    char* b = "1234";
    int res = strcmp(a, b);

    assert(0 == res);
}

void test_copy_CommonCase() {
    char* a = "1234";
    char b[4];

    assert(copy(a, a + 3, b) == b + 3);
}

int isEven(int a) {
    return a % 2 == 0;
}

void test_copyIf_CommonCase() {
    char* a = "1224";
    char b[4];

    assert(copyIf(a, a + 3, b, isEven) == b + 2);
}

void test_copyIf_NoEven() {
    char* a = "1532";
    char b[4];

    assert(copyIf(a, a + 3, b, isEven) == b);
}

void test_copyIfReverse_CommonCase() {
    char* a = "2221";
    char b[4];

    assert(copyIfReverse(a + 3, a, b, isEven) == b + 2);
}

void test_copyIfReverse_NoEven() {
    char* a = "2537";
    char b[4];

    assert(copyIfReverse(a + 3, a, b, isEven) == b);
}

void test_string() {
    test_findNonSpace_CommonCase();
    test_findNonSpace_AllSpace();
    test_findNonSpace_AllSymbol();
    test_findSpace_CommonCase();
    test_findSpace_NonSpace();
    test_findNonSpaceReverse_CommonCase();
    test_findNonSpaceReverse_NonSpace();
    test_strcmp_CommonCase();
    test_strcmp_StrEqual();
    test_copy_CommonCase();
    test_copyIf_CommonCase();
    test_copyIf_NoEven();
    test_copyIfReverse_CommonCase();
    test_copyIfReverse_NoEven();
}