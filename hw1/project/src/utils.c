#include <string.h>

#include "utils.h"

size_t custom_strlen(const char* str) {
    return strlen(str);
}

int custom_pow(int base, int power) {
    int res = base;
    if (power == 0)
        return res = 1;
    for (int i = 1; i < power; i++)
        res *= base;
    return res;
}

