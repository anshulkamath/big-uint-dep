#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mod.h"
#include "big-uint.h"

#define NUM_BITS_32 32
#define UINT_BYTES sizeof(uint32_t)

/**
 * @brief Extends a big integer x by padding the MSDs with 0s
 * 
 * @param new_x Where to place the new big integer
 * @param new_len The length of the new big integer
 * @param old_x The old big integer
 * @param old_len The length of the old big integer
 */
void big_uint_extend(uint32_t *new_x, size_t new_len, const uint32_t *old_x, size_t old_len) {
    memset(new_x, 0, new_len * UINT_BYTES);
    memcpy(&new_x[new_len - old_len], old_x, old_len * UINT_BYTES);
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

// private function to calculate barrett reduction
void barret_r(uint32_t *r, const uint32_t *p, size_t k, size_t len) {
    const size_t NEW_LEN = 2 * len + 1;
    uint32_t temp[NEW_LEN];
    memset(temp, 0, NEW_LEN * UINT_BYTES);
    
    // k is defined to be ceil(log_(2^32) p)
    // let temp = 4^k
    // NOTE: 1 must be added to offset k wrt NEW_LEN
    temp[NEW_LEN - (2 * k + 1)] = 1;

    // make mutable copy of p with right size
    uint32_t p_cpy[NEW_LEN];
    big_uint_extend(p_cpy, NEW_LEN, p, len);

    // find floor(4^k/p)
    uint32_t quo[NEW_LEN];
    uint32_t rem[NEW_LEN];
    memset(quo, 0, NEW_LEN * UINT_BYTES);
    memset(rem, 0, NEW_LEN * UINT_BYTES);

    big_uint_div(quo, rem, temp, p_cpy, NEW_LEN);
    
    // set r to integer quotient
    memcpy(r, quo, NEW_LEN * UINT_BYTES);
}

mod_t mod_init(const uint32_t *p, size_t len) {
    mod_t res;
    uint32_t k = 0;

    uint32_t ZERO[len];
    memset(ZERO, 0, len * UINT_BYTES);

    uint32_t b[len];
    memcpy(b, p, len * UINT_BYTES);

    // calculate ceil(log_(2^32) p)
    while(big_uint_cmp(b, ZERO, len) > 0) {
        big_uint_shr(b, b, 1, len);
        ++k;
    }

    // set result
    res.k = k;
    res.len = len;

    // copy p and r into struct
    big_uint_extend(res.p, 2 * len + 1, p, len);
    barret_r(res.r, p, k, len);

    return res;
}
