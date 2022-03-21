#include "ec.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "big-uint.h"
#include "mod.h"

#define N_MAX 8
#define UINT_BYTES sizeof(uint32_t)

const static uint32_t ZERO[N_MAX] = { 0 };
const static point_t identity = { .x = { 0 }, .y = { 0 } };

void point_print(const point_t *p) {
    printf("Point located at %p\n:", (void *) p);
    printf("\tx = ");
    big_uint_print(p->x, N_MAX);
    printf("\ty = ");
    big_uint_print(p->y, N_MAX);
}

void point_init(point_t *res, const uint32_t *x, const uint32_t *y) {
    memcpy(res->x, x, N_MAX * UINT_BYTES);
    memcpy(res->y, y, N_MAX * UINT_BYTES);
}

uint8_t point_is_identity(const point_t *pt) {
    uint32_t ZERO[N_MAX];
    memset(ZERO, 0, N_MAX * UINT_BYTES);

    uint8_t x_is_zero = big_uint_cmp(pt->x, ZERO, N_MAX) == 0;
    uint8_t y_is_zero = big_uint_cmp(pt->y, ZERO, N_MAX) == 0;

    return x_is_zero && y_is_zero;
}

uint8_t point_equals(const point_t *p1, const point_t *p2) {
    if (p1 == p2) return 1;

    uint8_t x_eq = big_uint_equals(p1->x, p2->x, N_MAX);
    uint8_t y_eq = big_uint_equals(p1->y, p2->y, N_MAX);

    return x_eq && y_eq;
}

const point_t *get_identity() {
    return &identity;
}

uint8_t ec_init(ec_t *ec, const uint32_t *a, const uint32_t *b, const uint32_t *p, const uint32_t *n, const point_t *g) {
    // 1. calculate mod_p
    // 2. verify 4a^2 + 27b^3 != 0
    // 3. verify point on curve (later)
    // 4. calculate mod_n
    // 5. assign variables
    mod_t mod_p = mod_init(p, N_MAX);

    uint32_t temp1[N_MAX] = { 0 };
    uint32_t temp2[N_MAX] = { 0 };
    temp2[N_MAX - 1] = 4;

    mod_mult(temp1, temp2, a, &mod_p, N_MAX);
    mod_mult(temp1, temp1, a, &mod_p, N_MAX);
    mod_mult(temp1, temp1, a, &mod_p, N_MAX);

    temp2[N_MAX - 1] = 27;
    mod_mult(temp2, temp2, b, &mod_p, N_MAX);
    mod_mult(temp2, temp2, b, &mod_p, N_MAX);

    mod_add(temp1, temp1, temp2, p, N_MAX);

    // if 4a^3 + 27b^2 = 0, return 1 (fail to create ec)
    if (big_uint_cmp(temp1, ZERO, N_MAX) == 0) {
        return 1;
    }

    const size_t NUM_BYTES = N_MAX * UINT_BYTES;

    mod_t mod_n = mod_init(n, N_MAX);

    memcpy(ec->a, a, NUM_BYTES);
    memcpy(ec->b, b, NUM_BYTES);
    memcpy(ec->p, p, NUM_BYTES);
    memcpy(ec->n, n, NUM_BYTES);

    memcpy(ec->g.x, g->x, NUM_BYTES);
    memcpy(ec->g.y, g->y, NUM_BYTES);
    
    memcpy(ec->mod_p.p, mod_p.p, NUM_BYTES);
    memcpy(ec->mod_p.r, mod_p.r, NUM_BYTES);
    ec->mod_p.k = mod_p.k;
    ec->mod_p.len = mod_p.len;
    
    memcpy(ec->mod_n.p, mod_n.p, NUM_BYTES);
    memcpy(ec->mod_n.r, mod_n.r, NUM_BYTES);
    ec->mod_n.k = mod_n.k;
    ec->mod_n.len = mod_n.len;

    return 0;
}

#undef N_MAX
#undef UINT_BYTES
