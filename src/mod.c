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

// function to calculate barrett reduction
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

void mod_mult(uint32_t* result, const uint32_t* a, const uint32_t* b, const mod_t *mod, size_t len) {
    size_t x_len = 2 * len;
    uint32_t x[x_len];
    memset(x, 0, x_len * UINT_BYTES);

    uint32_t a_cpy[x_len];
    uint32_t b_cpy[x_len];

    big_uint_extend(a_cpy, x_len, a, len);
    big_uint_extend(b_cpy, x_len, b, len);

    // compute x = a * b
    big_uint_mult(x, a_cpy, b_cpy, x_len);

    // extend x to fit r
    size_t x_len_p = x_len + 1;
    uint32_t x_p[x_len];
    big_uint_extend(x_p, x_len_p, x, x_len);

    // compute t = x - floor(x * r / 4^k) * p
    size_t t_len = 2 * ((2 * mod->len) + 1);
    uint32_t t[t_len];
    memset(t, 0, t_len * UINT_BYTES);

    uint32_t x_ext[t_len];
    uint32_t p_ext[t_len];
    uint32_t r_ext[t_len];
    big_uint_extend(x_ext, t_len, x, x_len);
    big_uint_extend(p_ext, t_len, mod->p, x_len_p);
    big_uint_extend(r_ext, t_len, mod->r, x_len_p);

    big_uint_mult(t, x_ext, r_ext, t_len);  // compute x * r
    big_uint_shr(t, t, 2 * mod->k, t_len);  // compute floor(x * r / 4^k)
    big_uint_mult(t, t, p_ext, t_len);      // compute floor(x * r / 4^k) * p
    big_uint_sub(t, x_ext, t, t_len);       // compute x - floor(x * r / 4^k) * p

    if (big_uint_cmp(t, p_ext, t_len) > 0)
        big_uint_sub(t, t, p_ext, t_len);

    // copy t into the result
    size_t elem_no = t_len - len;
    memcpy(result, t + elem_no, len * UINT_BYTES);
}
