#include "big-uint.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int big_uint_equals(const uint32_t *a, const uint32_t *b, size_t len) {
    for (size_t i = 0; i < len; i++)
        if (a[i] != b[i]) return 0;
    
    return 1;
}

int big_uint_cmp(const uint32_t *a, const uint32_t *b, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i]) return a[i] > b[i] ? 1 : -1;
    }

    return 0;
}

void big_uint_sprint(char *dest, const uint32_t *value, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (i == 0) sprintf(&dest[0], "%08x", value[i]);
        else        sprintf(&dest[9 * i - 1], " %08x", value[i]);
    }
}

void big_uint_print(const uint32_t *value, size_t len) {
    char str[9 * len];
    big_uint_sprint(str, value, len);
    printf("%s\n", str);
}

void big_uint_shl(uint32_t *result, const uint32_t *a, size_t len, size_t n) {
    // if n >= len, we are overshifting, and result should be 0
    if (n >= len) {
        memset(result, 0, sizeof(uint32_t) * len);
        return;
    }

    for (size_t i = 0; i < len; i++)
        result[i] = (i + n) < len ? a[i + n] : 0;
}

void big_uint_shr(uint32_t *result, const uint32_t *a, size_t len, size_t n) {
    // if n >= len, we are overshifting, and result should be 0
    if (n >= len) {
        memset(result, 0, sizeof(uint32_t) * len);
        return;
    }

    for (size_t i = 0; i < len; i++)
        result[i] = ((int) i - (int) n) >=  0 ? a[i - n] : 0;
}

void big_uint_add(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len) {
    uint8_t carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        // printf("i: %d, a: %u, b: %u, a + b: %u, > max: %d, carry: %u\n", i, a[i], b[i], a[i] + b[i], a[i] + b[i] + carry > UINT32_MAX, carry);
        result[i] = a[i] + b[i] + carry;
        // printf("ba: %08x, bb: %016llx, sum: %016llx\n", a[i], big_b, big_a + big_b);
        carry = (uint64_t) a[i] + b[i] + carry > UINT32_MAX; // determine if overflow occurred
        // printf("sum: %u, casted sum: %llu, carry: %d\n\n", a[i] + b[i] + carry, (uint64_t) a[i] + b[i] + carry, carry);
    }
}

void big_uint_sub(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len) {
    size_t carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        result[i] = a[i] - b[i] - carry;
        carry = (uint64_t) a[i] - b[i] - carry > UINT32_MAX; // determine if underflow occurred
    }
}

void big_uint_mult(uint32_t* result, const uint32_t *a, const uint32_t *b, size_t len) {
    uint32_t product[len * 2];
    uint32_t partial_product[len * 2];
    uint32_t temp_product[len * 2];

    memset(product, 0, len * 2 * sizeof(uint32_t));
    memset(partial_product, 0, len * 2 * sizeof(uint32_t));
    memset(temp_product, 0, len * 2 * sizeof(uint32_t));

    for (int i = len - 1; i >= 0; i--) {
        uint64_t bi = b[i];

        for (int j = len - 1; j >= 0; j--) {
            uint64_t aj = a[j];
            uint64_t mini_product = aj * bi;

            // low
            partial_product[i + j + 1] = (uint32_t) (mini_product % (1ull << 32));

            // high
            partial_product[i + j] = (uint32_t) (mini_product / (1ull << 32));

            memcpy(temp_product, product, len * 2 * sizeof(uint32_t));
            big_uint_add(temp_product, product, partial_product, len * 2);
            memcpy(product, temp_product, len * 2 * sizeof(uint32_t));

            partial_product[i + j + 1] = 0;
            partial_product[i + j] = 0;
        }
    }

    memcpy(result, (product + len), len * sizeof(uint32_t));
}

static uint32_t big_uint_div_helper(uint32_t *a, const uint32_t *b, uint32_t *r, size_t len) {
    size_t start_a = (size_t) -1;

    // resetting output vars
    memset(r, 0, len * sizeof(uint32_t));
    
    // calculate the start indexes
    while (!a[++start_a]);

    // 1x1 case
    if (start_a == len - 1) {
        r[len - 1] = a[start_a] % b[start_a];
        return a[start_a] / b[start_a];
    }

    // get the approximation
    uint64_t curr_dividend = ((uint64_t) a[start_a] << 32) + a[start_a + 1];
    uint64_t curr_divisor = ((uint64_t) b[start_a] << 32) + b[start_a + 1];
    uint32_t estimate[len];

    uint32_t approx[len];
    memset(approx, 0, len * sizeof(uint32_t));

    // upper bound on a/b
    uint64_t quotient = curr_dividend / curr_divisor;
    approx[len - 2] = quotient >> 32;
    approx[len - 1] = (uint32_t) quotient;

    // get an estimate on quotient * divisor < dividend
    big_uint_mult(estimate, approx, b, len);

    // should only happen twice
    while (big_uint_cmp(estimate, a, len) > 0) {
        big_uint_sub(estimate, estimate, b, len);

        --quotient;
    }

    // can only get one digit out of quotient.
    // if two digits were possible, could have divided earlier
    big_uint_sub(r, a, estimate, len);

    return quotient;
}

void big_uint_div(uint32_t *q, uint32_t *r, const uint32_t *u, const uint32_t *v, size_t len) {
    // Handling divide by 0
    if (v[len - 1] == 0) return;

    uint32_t temp[len];

    memset(q, 0, len * sizeof(uint32_t));
    memset(r, 0, len * sizeof(uint32_t));

    for (size_t i = 0; i < len; i++) {
        // printf("%zu\n", i);
        big_uint_shl(q, q, len, 1);
        big_uint_shl(r, r, len, 1);
        r[len - 1] = u[i];

        // if the divisor is greater than the current remainder, shift another element
        if (big_uint_cmp(v, r, len) > 0) continue;

        // divide temp by q (helper function)
        memset(temp, 0, len * sizeof(uint32_t));
        q[len - 1] = big_uint_div_helper(r, v, temp, len);
        memcpy(r, temp, len * sizeof(uint32_t));
    }
}
