#include "ec.h"

#include <stdint.h>
#include "big-uint.h"
#include "testing-logger.h"

// import secp256k1 constants
#include "secp256k1.c"

#define N_MAX 8

void test_point_init() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    const uint32_t x1[N_MAX] = { 0 };
    const uint32_t y1[N_MAX] = { 0 };
    point_t  p1;

    point_init(&p1, x1, y1);

    expect(tester, big_uint_equals(x1, p1.x, N_MAX));
    expect(tester, big_uint_equals(y1, p1.y, N_MAX));

    const uint32_t *x2 = X;
    const uint32_t *y2 = Y;
    point_t  p2;

    point_init(&p2, x2, y2);

    expect(tester, big_uint_equals(x2, p2.x, N_MAX));
    expect(tester, big_uint_equals(y2, p2.y, N_MAX));

    log_tests(tester);
}

void test_get_identity() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    const uint32_t ZERO[N_MAX] = { 0 };
    const point_t *identity = get_identity();

    expect(tester, big_uint_equals(identity->x, ZERO, N_MAX));
    expect(tester, big_uint_equals(identity->y, ZERO, N_MAX));

    log_tests(tester);
}

void test_point_equals() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    // test same point
    const point_t *identity1 = get_identity();
    const point_t *identity2 = get_identity();

    expect(tester, point_equals(identity1, identity2) == 1);

    // test identical points
    const point_t g_cpy = { .x = {
            0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07,
            0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
        }, .y = {
            0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8,
            0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8
        }
    };

    expect(tester, point_equals(&g_cpy, &G) == 1);

    // test different points    
    expect(tester, point_equals(identity1, &G) == 0);

    // test same x-coord, diff y-coord
    const point_t p1 = { .x = { 0 }, .y = {
            0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8,
            0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8
        }
    };

    expect(tester, point_equals(&p1, &G) == 0);

    // test same y-coord, diff x-coord
    const point_t p2 = { .x = {
            0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07,
            0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
        }, .y = { 0 }
    };

    expect(tester, point_equals(&p2, &G) == 0);

    log_tests(tester);
}

void test_point_is_identity() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    const uint32_t x1[N_MAX] = { 0 };
    const uint32_t y1[N_MAX] = { 0 };
    point_t  p1;

    point_init(&p1, x1, y1);

    expect(tester, point_is_identity(&p1));

    const uint32_t *x2 = X;
    const uint32_t *y2 = Y;
    point_t  p2;

    point_init(&p2, x2, y2);

    expect(tester, !point_is_identity(&p2));

    expect(tester, point_is_identity(get_identity()));

    log_tests(tester);
}

void test_ec_init() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    ec_t ec1;
    mod_t mod_p_exp = mod_init(P, N_MAX);
    mod_t mod_n_exp = mod_init(N, N_MAX);

    uint8_t res1 = ec_init(&ec1, A, B, P, N, &G);

    // curve should have been made properly
    expect(tester, res1 == 0);

    // check curve parameters
    expect(tester, big_uint_equals(ec1.a, A, N_MAX));
    expect(tester, big_uint_equals(ec1.b, B, N_MAX));
    expect(tester, big_uint_equals(ec1.p, P, N_MAX));
    expect(tester, big_uint_equals(ec1.n, N, N_MAX));

    // check barrett reduction precomputation factorrs
    expect(tester, big_uint_equals(ec1.mod_p.p, mod_p_exp.p, N_MAX));
    expect(tester, big_uint_equals(ec1.mod_p.r, mod_p_exp.r, N_MAX));
    expect(tester, ec1.mod_p.k == mod_p_exp.k);
    expect(tester, ec1.mod_p.len == mod_p_exp.len);
    
    expect(tester, big_uint_equals(ec1.mod_n.p, mod_n_exp.p, N_MAX));
    expect(tester, big_uint_equals(ec1.mod_n.r, mod_n_exp.r, N_MAX));
    expect(tester, ec1.mod_n.k == mod_n_exp.k);
    expect(tester, ec1.mod_n.len == mod_n_exp.len);

    // check generator point
    expect(tester, point_equals(&ec1.g, &G));

    ec_t ec2;

    const uint32_t ZERO[N_MAX] = { 0 };
    uint8_t res2 = ec_init(&ec2, ZERO, ZERO, ZERO, ZERO, get_identity());

    expect(tester, res2 == 1);

    log_tests(tester);
}

int main() {
    test_point_init();
    test_get_identity();
    test_point_equals();
    test_point_is_identity();
    test_ec_init();

    return 1;
}
