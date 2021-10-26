#include "big-uint.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BITS_32 32

// ---------------------------- //
//       Helper Functions       //
// ---------------------------- //
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

// ---------------------------- //
//     Comparison Functions     //
// ---------------------------- //

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

// ----------------------------- //
//       Memory Management       //
// ----------------------------- //

void big_uint_cpy(uint32_t *dest, uint32_t *src, size_t len) {
    memcpy(dest, src, len * sizeof(uint32_t));
}

void big_uint_swap(uint32_t *a, uint32_t *b, size_t len) {
    uint32_t temp[len];
    memcpy(temp, a, len * sizeof(uint32_t));
    memcpy(a, b, len * sizeof(uint32_t));
    memcpy(b, temp, len * sizeof(uint32_t));
}

// ------------------------------ //
//       Exporting Big Ints       //
// ------------------------------ //

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

// -------------------------------- //
//        Bit-wise operations       //
// -------------------------------- //

void big_uint_shl(uint32_t *result, const uint32_t *a, size_t n, size_t len) {
    // if n >= len, we are overshifting, and result should be 0
    if (n >= len) {
        memset(result, 0, sizeof(uint32_t) * len);
        return;
    }

    // if we are not shifting, then return the same element
    if (n == 0) {
        memcpy(result, a, len * sizeof(uint32_t));
        return;
    }

    // do not need to work in temporary variable r[i] depends on a[i + k],
    // so we are not corrupting data that we need
    for (size_t i = 0; i < len; i++)
        result[i] = (i + n) < len ? a[i + n] : 0;
}

void big_uint_shr(uint32_t *result, const uint32_t *a, size_t n, size_t len) {    
    // if n >= len, we are overshifting, and result should be 0
    if (n >= len) {
        memset(result, 0, sizeof(uint32_t) * len);
        return;
    }

    // return the same number if we are not shifting
    if (n == 0) {
        memcpy(result, a, len * sizeof(uint32_t));
        return;
    }

    // work in temporary variable to allow for operator assignment
    // this is because r[i] depends on a[i - k], which will have already changed
    uint32_t a_cpy[len];
    memcpy(a_cpy, a, sizeof(uint32_t) * len);

    for (size_t i = 0; i < len; i++)
        result[i] = ((int) i - (int) n) >=  0 ? a_cpy[i - n] : 0;
}

void big_uint_shl2(uint32_t *result, const uint32_t *a, size_t n, size_t len) {
    // if we are overshifting the result should be 0
    if (n >= len * BITS_32) {
        memset(result, 0, sizeof(uint32_t) * len);
        return;
    }

    // first we shift left the number of digits possible
    big_uint_shl(result, a, n / BITS_32, len);

    // if we shift by a multiple of 32, we are done after the digit shift
    if (n % BITS_32 == 0) return;

    size_t shift = n % BITS_32;
    uint32_t shifted = 0;

    for (int i = len - 1; i >= 0; i--) {
        uint32_t temp = shifted;
        shifted = result[i] >> (BITS_32 - shift);
        result[i] = temp | (result[i] << shift);
    }
}

void big_uint_shr2(uint32_t *result, const uint32_t *a, size_t n, size_t len) {
    // if we are overshifting the result should be 0
    if (n >= len * BITS_32) {
        memset(result, 0, sizeof(uint32_t) * len);
        return;
    }

    // first we shift right the number of digits possible
    big_uint_shr(result, a, n / BITS_32, len);

    // if we shift by a multiple of 32, we are done after the digit shift
    if (n % BITS_32 == 0) return;

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

// -------------------------------- //
//     Mathematical Operations      //
// -------------------------------- //

void big_uint_add(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len) {
    // work in temporary variable to allow for operator assignment
    uint32_t a_cpy[len];
    memcpy(a_cpy, a, sizeof(uint32_t) * len);

    uint8_t carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        result[i] = a_cpy[i] + b[i] + carry;
        carry = (uint64_t) a_cpy[i] + b[i] + carry > UINT32_MAX; // determine if overflow occurred
    }
}

void big_uint_sub(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len) {
    // work in temporary variable to allow for operator assignment
    uint32_t a_cpy[len];
    memcpy(a_cpy, a, sizeof(uint32_t) * len);

    size_t carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        result[i] = a_cpy[i] - b[i] - carry;
        carry = (uint64_t) a_cpy[i] - b[i] - carry > UINT32_MAX; // determine if underflow occurred
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

void big_uint_div(uint32_t *q, uint32_t *r, const uint32_t *u, const uint32_t *v, size_t len) {
    // Handling divide by 0
    if (v[len - 1] == 0) return;

    uint32_t temp[len];
    uint32_t one[len];

    memset(q, 0, len * sizeof(uint32_t));
    memset(r, 0, len * sizeof(uint32_t));
    memset(temp, 0, len * sizeof(uint32_t));
    memset(one, 0, len * sizeof(uint32_t));

    one[len - 1] = 1;

    for (int i = len * sizeof(uint32_t) * 8 - 1; i >= 0; i--) {
        // q <<= 1
        big_uint_shl2(q, q, 1, len);

        // (r <<= 1) |= ((u >> i) & 0b1)
        big_uint_shr2(temp, u, i, len);
        big_uint_shl2(r, r, 1, len);
        r[len - 1] |= (temp[len - 1] & 1);

        // if the divisor > remainder, shift another element
        if (big_uint_cmp(v, r, len) > 0) continue;
        
        // q |= 1
        q[len - 1] |= 1;

        // r -= v
        big_uint_sub(r, r, v, len);
    }
}

// -------------------------------- //
//         Number Theory Ops        //
// -------------------------------- //

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
