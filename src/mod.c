#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod.h"
#include "big-uint.h"

#define NUM_BITS_32 32

/**
 * @brief Returns the (truncated) log_2 of x 
 * 
 * @param x The biguint to find the number of bits of
 * @param len The number of digits in len
 * @return size_t 
 */
static size_t big_uint_log_2(const uint32_t *x, size_t len) {
    uint8_t bit = 0;
    uint8_t bit_val = 0;
    const size_t TOTAL_BITS = len * NUM_BITS_32;

    while (!bit_val && bit < TOTAL_BITS) {
        uint8_t bit_ind = NUM_BITS_32 - ((++bit) % NUM_BITS_32);
        bit_val = (x[bit / NUM_BITS_32] >> bit_ind) & 1;
    }

    return TOTAL_BITS - bit;
}

/**
 * @brief Extends a big integer x by padding the MSDs with 0s
 * 
 * @param new_x Where to place the new big integer
 * @param new_len The length of the new big integer
 * @param old_x The old big integer
 * @param old_len The length of the old big integer
 */
void big_uint_extend(uint32_t *new_x, size_t new_len, const uint32_t *old_x, size_t old_len) {
    for (size_t digit = 0; digit < new_len; digit++) {
        new_x[new_len - 1 - digit] = digit < old_len ? old_x[digit] : 0;
    }
}

void mod_big_uint(uint32_t *result, const uint32_t *n, const uint32_t *p, size_t len) {
    uint32_t quotient[len];

    big_uint_div(quotient, result, n, p, len);
}

void mod_add(uint32_t *result, const uint32_t *a, const uint32_t *b, const uint32_t *p, size_t len) {
    big_uint_add(result, a, b, len);

    // if result > p, then subtract p
    if (big_uint_cmp(result, p, len) > 0)
        big_uint_sub(result, result, p, len);
}

void mod_sub(uint32_t *result, const uint32_t *a, const uint32_t *b, const uint32_t *p, size_t len) {
    big_uint_sub(result, a, b, len);

    // if result > p, then subtract p
    if (big_uint_cmp(result, p, len) > 0)
        big_uint_add(result, result, p, len);
}
