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

uint8_t point_is_inverse(const point_t *p1, const point_t *p2, const ec_t *ec) {
    uint32_t inv[N_MAX];
    mod_neg(inv, p1->y, ec->p, N_MAX);

    point_t inv_point;
    point_copy(&inv_point, p1);
    memcpy(inv_point.y, inv, N_MAX * UINT_BYTES);

    return point_equals(p2, &inv_point);
}

void point_copy(point_t *dest, const point_t *src) {
    memcpy(dest->x, src->x, N_MAX * UINT_BYTES);
    memcpy(dest->y, src->y, N_MAX * UINT_BYTES);
}

const point_t *get_identity() {
    return &identity;
}

uint8_t ec_init(ec_t *ec, const uint32_t *a, const uint32_t *b, const uint32_t *p, const uint32_t *n, const point_t *g) {
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
    
    mod_t_copy(&ec->mod_p, &mod_p);
    mod_t_copy(&ec->mod_n, &mod_n);

    return 0;
}

void ec_add(point_t *res, const point_t *p1, const point_t *p2, const ec_t *ec) {
    if (point_is_identity(p1)) {
        point_copy(res, p2);
        return;
    }

    if (point_is_identity(p2)) {
        point_copy(res, p1);
        return;
    }

    if (point_is_inverse(p1, p2, ec)) {
        point_copy(res, get_identity());
        return;
    }

    // calculate lambda
    uint32_t lambda[N_MAX];
    uint32_t temp1[N_MAX];
    uint32_t temp2[N_MAX];

    // if the points are equal, then use the tangent line
    if (point_equals(p1, p2)) {
        big_uint_load(lambda, 3, N_MAX);
        mod_mult(lambda, lambda, p1->x, &ec->mod_p, N_MAX);
        mod_mult(lambda, lambda, p1->x, &ec->mod_p, N_MAX);
        mod_add(lambda, lambda, ec->a, ec->p, N_MAX);

        big_uint_load(temp1, 2, N_MAX);
        mod_mult(temp1, temp1, p1->y, &ec->mod_p, N_MAX);
        mod_inv(temp1, temp1, &ec->mod_p, N_MAX);

        mod_mult(lambda, lambda, temp1, &ec->mod_p, N_MAX);
    } else {
        mod_sub(lambda, p2->y, p1->y, ec->p, N_MAX);
        mod_sub(temp1, p2->x, p1->x, ec->p, N_MAX);
        mod_inv(temp2, temp1, &ec->mod_p, N_MAX);
        mod_mult(lambda, lambda, temp2, &ec->mod_p, N_MAX);
    }

    uint32_t x3[N_MAX];
    uint32_t y3[N_MAX];

    // calculate x3
    mod_mult(x3, lambda, lambda, &ec->mod_p, N_MAX);
    mod_sub(x3, x3, p1->x, ec->p, N_MAX);
    mod_sub(x3, x3, p2->x, ec->p, N_MAX);

    // calculate y3
    mod_sub(y3, p1->x, x3, ec->p, N_MAX);
    mod_mult(y3, lambda, y3, &ec->mod_p, N_MAX);
    mod_sub(y3, y3, p1->y, ec->p, N_MAX);

    point_init(res, x3, y3);
}

#undef N_MAX
#undef UINT_BYTES
