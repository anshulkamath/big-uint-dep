#include "big-uint.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// helper function
/* static void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        if (i % 4 == 3) printf(" ");
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

static void print_hex(uint32_t num) {
    printf("%08x\n", num);
} */

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

uint32_t* big_uint_max(uint32_t *a, size_t len_a, uint32_t *b, size_t len_b) {
    size_t offset_a = 0;
    size_t offset_b = 0;

    if (len_a > len_b) {
        // if any digit of a is nonzero before a digit of b, return a
        while (offset_a < len_b)
            if (a[offset_a++]) return a;
    } else if (len_b > len_a) {
        // if any digit of b is nonzero beforee a digit of a, return b
        while (offset_b < len_a)
            if (b[offset_b++]) return b;
    }

    // check each corresponding digit to see if either is bigger
    while (offset_a < len_a) {
        if (a[offset_a] > b[offset_b]) return a;
        if (b[offset_b] > a[offset_a]) return b;

        ++offset_a;
        ++offset_b;
    }

    return a;
}

uint32_t* big_uint_min(uint32_t *a, size_t len_a, uint32_t *b, size_t len_b) {
    size_t offset_a = 0;
    size_t offset_b = 0;

    if (len_a > len_b) {
        // if any digit of a is nonzero before a digit of b, return b
        while (offset_a < len_b)
            if (a[offset_a++]) return b;
    } else if (len_b > len_a) {
        // if any digit of b is nonzero beforee a digit of a, return a
        while (offset_b < len_a)
            if (b[offset_b++]) return a;
    }

    // check each corresponding digit to see if either is smaller
    while (offset_a < len_a) {
        if (a[offset_a] > b[offset_b]) return b;
        if (b[offset_b] > a[offset_a]) return a;

        ++offset_a;
        ++offset_b;
    }

    return a;
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

void big_uint_shl2(uint32_t *result, const uint32_t *a, size_t len, size_t n) {
    // if we are overshifting the result should be 0
    const uint8_t BITS_32 = 8 * sizeof(uint32_t);
    if (n >= len * BITS_32) {
        memset(result, 0, sizeof(uint32_t) * len);
        return;
    }

    // first we shift left the number of digits possible
    big_uint_shl(result, a, len, n / BITS_32);

    size_t shift = n % BITS_32;
    uint32_t shifted = 0;

    for (int i = len - 1; i >= 0; i--) {
        uint32_t temp = shifted;
        shifted = result[i] >> (BITS_32 - shift);
        result[i] = temp | (result[i] << shift);
    }
}

void big_uint_shr2(uint32_t *result, const uint32_t *a, size_t len, size_t n) {
    // if we are overshifting the result should be 0
    const uint8_t BITS_32 = 8 * sizeof(uint32_t);
    if (n >= len * BITS_32) {
        memset(result, 0, sizeof(uint32_t) * len);
        return;
    }

    // first we shift right the number of digits possible
    big_uint_shr(result, a, len, n / BITS_32);

    size_t shift = n % BITS_32;
    uint32_t shifted = 0;

    for (size_t i = 0; i < len; i++) {
        uint32_t temp = shifted;
        shifted = result[i] << (BITS_32 - shift);
        result[i] = (result[i] >> shift) | temp;
    }
}

void big_uint_or(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len) {
    for (size_t i = 0; i < len; i++)
        result[i] = a[i] | b[i];
}

void big_uint_and(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len) {
    for (size_t i = 0; i < len; i++)
        result[i] = a[i] & b[i];
}

void big_uint_xor(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len) {
    for (size_t i = 0; i < len; i++)
        result[i] = a[i] ^ b[i];
}

void big_uint_add(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len) {
    uint8_t carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        result[i] = a[i] + b[i] + carry;
        carry = (uint64_t) a[i] + b[i] + carry > UINT32_MAX; // determine if overflow occurred
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

// helper function for the recursive gcd algorithm
static void big_uint_gcd_helper(uint32_t *d, const uint32_t *a, const uint32_t *b, const uint32_t *zero, size_t len) {
    uint32_t quotient[len], remainder[len];
    big_uint_div(quotient, remainder, a, b, len);

    // if the remainder is 0, then we are at the bottom of euclid's algorithm.
    // write this gcd to d and return
    if (big_uint_equals(remainder, zero, len)) {
        memcpy(d, b, len * sizeof(uint32_t));
        return;
    }
    
    big_uint_gcd_helper(d, b, remainder, zero, len);
}

void big_uint_gcd(uint32_t *d, const uint32_t *a_init, const uint32_t *b_init, size_t len) {
    // making a > b for the algorithm
    uint32_t a[len], b[len];
    int a_is_bigger = big_uint_cmp(a_init, b_init, len) >= 0;

    memcpy(a, a_is_bigger ? a_init : b_init, len * sizeof(uint32_t));
    memcpy(b, !a_is_bigger ? a_init : b_init, len * sizeof(uint32_t));

    uint32_t zero[len];
    memset(zero, 0, len * sizeof(uint32_t));
    
    big_uint_gcd_helper(d, a, b, zero, len);
}

// swaps the big uint pointed to by a with the big uint pointed to by b
static void big_uint_swap(uint32_t *a, uint32_t *b, size_t len) {
    uint32_t temp[len];
    memcpy(temp, a, len * sizeof(uint32_t));
    memcpy(a, b, len * sizeof(uint32_t));
    memcpy(b, temp, len * sizeof(uint32_t));
}

static void big_uint_gcd_extended_helper(uint32_t* x, uint32_t *y, const uint32_t *a, const uint32_t *b, const uint32_t *zero, size_t len) {
    uint32_t quotient[len], remainder[len];
    big_uint_div(quotient, remainder, a, b, len);

    // base case: if the remainder is 0, initialize x = 0 and y = 1
    if (big_uint_equals(remainder, zero, len)) {
        memset(x, 0, len * sizeof(uint32_t));
        memset(y, 0, len * sizeof(uint32_t));

        y[len - 1] = 1; // initialize y for recursive backtrace
        return;
    }

    // recurse downwards to get the x and y values of the preceding equation in euclid's algorithm
    big_uint_gcd_extended_helper(x, y, b, remainder, zero, len);
    
    // apply x -= y * quotient
    uint32_t y_times_quotient[len], x_subtracted[len];
    
    memset(y_times_quotient, 0, len * sizeof(uint32_t));
    memset(x_subtracted, 0, len * sizeof(uint32_t));

    big_uint_mult(y_times_quotient, y, quotient, len);
    big_uint_sub(x_subtracted, x, y_times_quotient, len);

    memcpy(x, x_subtracted, len * sizeof(uint32_t));

    // swap x and y
    big_uint_swap(x, y, len);
}

void big_uint_gcd_extended(uint32_t* x, uint32_t *y, const uint32_t *a_init, const uint32_t *b_init, size_t len) {
    // making a > b for the algorithm
    uint32_t a[len], b[len];
    int a_is_bigger = big_uint_cmp(a_init, b_init, len) >= 0;

    memcpy(a, a_is_bigger ? a_init : b_init, len * sizeof(uint32_t));
    memcpy(b, !a_is_bigger ? a_init : b_init, len * sizeof(uint32_t));
    
    uint32_t zero[len];
    memset(zero, 0, len * sizeof(uint32_t));

    big_uint_gcd_extended_helper(x, y, a, b, zero, len);
}
