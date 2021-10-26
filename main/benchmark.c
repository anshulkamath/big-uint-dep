#include <time.h>
#include <stdio.h>
#include <string.h>

#include "big-uint.h"

void benchmark_biguint_add(void) {
    clock_t start = clock();
    int count = 0;
    uint32_t a[8] = {
        0x12341234, 0x12341234, 0x12341234, 0x12341234,
        0x12341234, 0x12341234, 0x12341234, 0x12341234
    };
    uint32_t b[8] = {
        0x56785678, 0x56785678, 0x56785678, 0x56785678,
        0x56785678, 0x56785678, 0x56785678, 0x56785678
    };
    uint32_t c[8] = {0};

    while (clock() - start < CLOCKS_PER_SEC) {
        big_uint_add(c, a, b, 8);
        count += 1;
    }
    printf("biguint_add: %d\n", count);
}


void benchmark_biguint_sub(void) {
    clock_t start = clock();
    int count = 0;
    uint32_t a[8] = {
        0x12341234, 0x12341234, 0x12341234, 0x12341234,
        0x12341234, 0x12341234, 0x12341234, 0x12341234
    };
    uint32_t b[8] = {
        0x56785678, 0x56785678, 0x56785678, 0x56785678,
        0x56785678, 0x56785678, 0x56785678, 0x56785678
    };
    uint32_t c[8] = {0};

    while (clock() - start < CLOCKS_PER_SEC) {
        big_uint_sub(c, a, b, 8);
        count += 1;
    }
    printf("biguint_sub: %d\n", count);
}

void benchmark_biguint_mul(void) {
    clock_t start = clock();
    int count = 0;
    uint32_t a[8] = {
        0x12341234, 0x12341234, 0x12341234, 0x12341234,
        0x12341234, 0x12341234, 0x12341234, 0x12341234
    };
    uint32_t b[8] = {
        0x56785678, 0x56785678, 0x56785678, 0x56785678,
        0x56785678, 0x56785678, 0x56785678, 0x56785678
    };
    uint32_t c[16] = {0};

    while (clock() - start < CLOCKS_PER_SEC) {
        big_uint_mult(c, a, b, 8);
        count += 1;
    }
    printf("biguint_mul: %d\n", count);
}


void benchmark_biguint_div(void) {
    clock_t start = clock();
    int count = 0;
    uint32_t a[8] = {
        0x12341234, 0x12341234, 0x12341234, 0x12341234,
        0x12341234, 0x12341234, 0x12341234, 0x12341234
    };
    uint32_t b[8] = {
        0x56785678, 0x56785678, 0x56785678, 0x56785678,
        0x56785678, 0x56785678, 0x56785678, 0x56785678
    };
    uint32_t q[8] = {0};
    uint32_t r[8] = {0};

    while (clock() - start < CLOCKS_PER_SEC) {
        big_uint_div(q, r, a, b, 8);
        count += 1;
    }
    printf("biguint_div: %d\n", count);
}

int main(void) {
    printf("biguint:\n");
    benchmark_biguint_add();
    benchmark_biguint_sub();
    benchmark_biguint_mul();
    benchmark_biguint_div();
    printf("\n");
}
