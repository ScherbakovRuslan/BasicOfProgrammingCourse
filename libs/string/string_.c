#include "string.h"
#include <ctype.h>

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0') {
        end++;
    }

    return end - begin;
}

char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch) {
        begin++;
    }

    return begin;
}

char* findNonSpace(char *begin) {
    char *firstSymbol = begin;
    while(isspace(*firstSymbol)) {
        firstSymbol++;
    }

    return firstSymbol;
}

char* findSpace(char *begin) {
    char *firstSpace = begin;
    while(*firstSpace != '\0' && !isspace(*firstSpace)) {
        firstSpace++;
    }

    return firstSpace;
}

char* findNonSpaceReverse(char *rbegin, const char *rend) {
    char *firstSpace = rbegin;
    while(firstSpace != rend && !isspace(*firstSpace)) {
        firstSpace--;
    }

    return firstSpace;
}

int strcmp(const char *lhs, const char *rhs) {
    while(*lhs == *rhs && *lhs != '\0') {
        lhs++;
        rhs++;
    }

    return *lhs - *rhs;
}

char* copy(const char *beginSource, const char *endSource,
           char *beginDestination) {
    long long size = endSource - beginSource;
    memcpy(beginDestination, beginSource,sizeof(char) * size);

    return beginDestination + size;
}

char* copyIf(char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int)) {
    while(beginSource < endSource) {
        if(f(*beginSource)) {
            memcpy(beginDestination, beginSource, sizeof(char));
            beginDestination++;
        }
        beginSource++;
    }

    return beginDestination;
}

char* copyIfReverse(char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int)) {
    while(rbeginSource > rendSource) {
        if(f(*rbeginSource)) {
            memcpy(beginDestination, rbeginSource, sizeof(char));
            beginDestination++;
        }
        rbeginSource--;
    }

    return beginDestination;
}