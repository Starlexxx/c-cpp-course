#include "is_prime.h"

#define NOT_PRIME 0
#define IS_PRIME 1

int is_prime(int num) {
    if (num <= 1) {
        return NOT_PRIME;
    }
        for (int i = 2; i * i <= num; ++i) {
            if (num % i == 0) {
                return NOT_PRIME;
            }
        }
    return IS_PRIME;
}
