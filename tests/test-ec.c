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

void test_ec_add() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t x1a[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const uint32_t y1a[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const point_t p1a;
	point_init(&p1a, x1a, y1a);

	const uint32_t x1b[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const uint32_t y1b[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const point_t p1b;
	point_init(&p1b, x1b, y1b);

	const uint32_t expected_x1[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const uint32_t expected_y1[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const point_t expected_p1;
	point_init(&expected_p1, &expected_x1, &expected_y1);

	ec_add(&result, &p1a, &p1b, &EC);

	expect(tester, point_equals(&expected_p1, &result));

	// Test 2
	const uint32_t x2a[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const uint32_t y2a[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const point_t p2a;
	point_init(&p2a, x2a, y2a);

	const uint32_t x2b[] = {
		0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 
		0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
	};
	const uint32_t y2b[] = {
		0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 
		0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8
	};
	const point_t p2b;
	point_init(&p2b, x2b, y2b);

	const uint32_t expected_x2[] = {
		0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 
		0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
	};
	const uint32_t expected_y2[] = {
		0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 
		0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8
	};
	const point_t expected_p2;
	point_init(&expected_p2, &expected_x2, &expected_y2);

	ec_add(&result, &p2a, &p2b, &EC);

	expect(tester, point_equals(&expected_p2, &result));

	// Test 3
	const uint32_t x3a[] = {
		0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 
		0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
	};
	const uint32_t y3a[] = {
		0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 
		0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8
	};
	const point_t p3a;
	point_init(&p3a, x3a, y3a);

	const uint32_t x3b[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const uint32_t y3b[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const point_t p3b;
	point_init(&p3b, x3b, y3b);

	const uint32_t expected_x3[] = {
		0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 
		0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
	};
	const uint32_t expected_y3[] = {
		0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 
		0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8
	};
	const point_t expected_p3;
	point_init(&expected_p3, &expected_x3, &expected_y3);

	ec_add(&result, &p3a, &p3b, &EC);

	expect(tester, point_equals(&expected_p3, &result));

	// Test 4
	const uint32_t x4a[] = {
		0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 
		0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
	};
	const uint32_t y4a[] = {
		0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 
		0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8
	};
	const point_t p4a;
	point_init(&p4a, x4a, y4a);

	const uint32_t x4b[] = {
		0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 
		0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
	};
	const uint32_t y4b[] = {
		0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 
		0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8
	};
	const point_t p4b;
	point_init(&p4b, x4b, y4b);

	const uint32_t expected_x4[] = {
		0xc6047f94, 0x41ed7d6d, 0x3045406e, 0x95c07cd8, 
		0x5c778e4b, 0x8cef3ca7, 0xabac09b9, 0x5c709ee5
	};
	const uint32_t expected_y4[] = {
		0x1ae168fe, 0xa63dc339, 0xa3c58419, 0x466ceaee, 
		0xf7f63265, 0x3266d0e1, 0x236431a9, 0x50cfe52a
	};
	const point_t expected_p4;
	point_init(&expected_p4, &expected_x4, &expected_y4);

	ec_add(&result, &p4a, &p4b, &EC);

	expect(tester, point_equals(&expected_p4, &result));

	// Test 5
	const uint32_t x5a[] = {
		0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 
		0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
	};
	const uint32_t y5a[] = {
		0x483ada77, 0x26a3c465, 0x5da4fbfc, 0x0e1108a8, 
		0xfd17b448, 0xa6855419, 0x9c47d08f, 0xfb10d4b8
	};
	const point_t p5a;
	point_init(&p5a, x5a, y5a);

	const uint32_t x5b[] = {
		0x79be667e, 0xf9dcbbac, 0x55a06295, 0xce870b07, 
		0x029bfcdb, 0x2dce28d9, 0x59f2815b, 0x16f81798
	};
	const uint32_t y5b[] = {
		0xb7c52588, 0xd95c3b9a, 0xa25b0403, 0xf1eef757, 
		0x02e84bb7, 0x597aabe6, 0x63b82f6f, 0x04ef2777
	};
	const point_t p5b;
	point_init(&p5b, x5b, y5b);

	const uint32_t expected_x5[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const uint32_t expected_y5[] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const point_t expected_p5;
	point_init(&expected_p5, &expected_x5, &expected_y5);

	ec_add(&result, &p5a, &p5b, &EC);

	expect(tester, point_equals(&expected_p5, &result));

	// Test 6
	const uint32_t x6a[] = {
		0x1e2feb89, 0x414c343c, 0x1027c4d1, 0xc386bbc4, 
		0xcd613e30, 0xd8f16adf, 0x91b7584a, 0x2265b1f6
	};
	const uint32_t y6a[] = {
		0x2762a80b, 0xaa354f16, 0x98a6101f, 0x5fb8f56f, 
		0xd2524af4, 0xe2f05b67, 0xae8fab0e, 0x01783e35
	};
	const point_t p6a;
	point_init(&p6a, x6a, y6a);

	const uint32_t x6b[] = {
		0x35bf992d, 0xc9e9c616, 0x612e7696, 0xa6cecc1b, 
		0x78e51061, 0x7311d8a3, 0xc2ce6f44, 0x7ed4d57c
	};
	const uint32_t y6b[] = {
		0x8cc5702d, 0x1ca20bee, 0x3c959f22, 0x2a0b77a6, 
		0xb70fbb4c, 0x9939bf2c, 0x82fdd6ff, 0x7d35968a
	};
	const point_t p6b;
	point_init(&p6b, x6b, y6b);

	const uint32_t expected_x6[] = {
		0xb36ee8be, 0x2ba41f2a, 0x4ef77910, 0x5bd0600b, 
		0x3d44eca3, 0xf91108dd, 0xcfb39ab9, 0x73de23c8
	};
	const uint32_t expected_y6[] = {
		0xb6f95431, 0x2093ab84, 0xdc25fcbe, 0x681086fd, 
		0x8cd430e9, 0xb87ecf5b, 0x0c5154e8, 0x59d228b9
	};
	const point_t expected_p6;
	point_init(&expected_p6, &expected_x6, &expected_y6);

	ec_add(&result, &p6a, &p6b, &EC);

	expect(tester, point_equals(&expected_p6, &result));

	// Test 7
	const uint32_t x7a[] = {
		0xafbd67f9, 0x619699cf, 0xe1988ad9, 0xf06c144a, 
		0x025b413f, 0x8a9a021e, 0xa648a7dd, 0x06839eba
	};
	const uint32_t y7a[] = {
		0x33763125, 0x87a62b63, 0xc23e8235, 0x4e287e44, 
		0x972ff92f, 0x036cc3c1, 0x553e3c04, 0x95ce144f
	};
	const point_t p7a;
	point_init(&p7a, x7a, y7a);

	const uint32_t x7b[] = {
		0xc381e88f, 0x38c0c8fd, 0x8712b8bc, 0x076f3787, 
		0xb9d179e0, 0x6c0fd4f5, 0xf8130c42, 0x37730ee0
	};
	const uint32_t y7b[] = {
		0xea038ddd, 0x39b4aecd, 0xd41e8c29, 0xa56e1b3f, 
		0x8acf73eb, 0x671f9625, 0xb1b08aa5, 0x0e8ed417
	};
	const point_t p7b;
	point_init(&p7b, x7b, y7b);

	const uint32_t expected_x7[] = {
		0x5976f03e, 0xc483f3fe, 0x7a18da55, 0xd317f55c, 
		0xe1ccc3be, 0x17b01328, 0x50341f92, 0xb2e62e65
	};
	const uint32_t expected_y7[] = {
		0x42394ccc, 0x4816362a, 0x33178773, 0x32f111ae, 
		0x765546b7, 0xf4e5af84, 0xd24461a3, 0x8250f2d6
	};
	const point_t expected_p7;
	point_init(&expected_p7, &expected_x7, &expected_y7);

	ec_add(&result, &p7a, &p7b, &EC);

	expect(tester, point_equals(&expected_p7, &result));

	// Test 8
	const uint32_t x8a[] = {
		0x6a8ac4ba, 0x05805975, 0xed2f89d9, 0x4a2f20aa, 
		0xf3c64af7, 0x75a89294, 0xc2cd789a, 0x380208aa
	};
	const uint32_t y8a[] = {
		0xccc8d8fb, 0xd6ea4202, 0xd10c61f3, 0xad00acba, 
		0x4b18fd47, 0xe3122430, 0xaddc21ad, 0x0804c289
	};
	const point_t p8a;
	point_init(&p8a, x8a, y8a);

	const uint32_t x8b[] = {
		0x81f9c1f6, 0x6c0f3459, 0xf79b17ae, 0xefba91fc, 
		0x803468b6, 0xb610a9f7, 0xf9270f4e, 0xb8b333a9
	};
	const uint32_t y8b[] = {
		0xb7923630, 0x24c4d3da, 0x65eea057, 0xf1d21f73, 
		0xef2e6d66, 0x891def91, 0xee77b919, 0x1feb9512
	};
	const point_t p8b;
	point_init(&p8b, x8b, y8b);

	const uint32_t expected_x8[] = {
		0xc8b579c7, 0xe24056af, 0xa1e3d356, 0xb297973a, 
		0xb279fade, 0xf3ba69e7, 0xffc5124e, 0xd52e9361
	};
	const uint32_t expected_y8[] = {
		0x6333213c, 0x7425c76c, 0xf50a820b, 0x8dcee734, 
		0xa82f1fea, 0x7855ea97, 0x3daecce0, 0xf63edfb0
	};
	const point_t expected_p8;
	point_init(&expected_p8, &expected_x8, &expected_y8);

	ec_add(&result, &p8a, &p8b, &EC);

	expect(tester, point_equals(&expected_p8, &result));

	// Test 9
	const uint32_t x9a[] = {
		0x29e821a4, 0xc74803e3, 0x1ba16215, 0x82283d15, 
		0xa9ec0806, 0x705fca16, 0x1622bd79, 0x5fec8990
	};
	const uint32_t y9a[] = {
		0x13eabece, 0x392fa99b, 0x45b1460e, 0xea15ed96, 
		0xc23ef81f, 0x5cda751b, 0x7ad1f35e, 0x2a922ead
	};
	const point_t p9a;
	point_init(&p9a, x9a, y9a);

	const uint32_t x9b[] = {
		0x678a5aa3, 0x3b6fe507, 0x8c5fe8f8, 0xdc3bf364, 
		0xeb8ac8ce, 0x8a245e6b, 0x33138131, 0xc541013e
	};
	const uint32_t y9b[] = {
		0x1f9b3eaa, 0xb829ed4c, 0x4853f26c, 0xf8f92591, 
		0x2d293dca, 0x74888cb8, 0xd3244fd3, 0xc31c3050
	};
	const point_t p9b;
	point_init(&p9b, x9b, y9b);

	const uint32_t expected_x9[] = {
		0x6acd33ff, 0x7dc76532, 0x464f5991, 0x73cf6ca1, 
		0xc33e63b3, 0x7fa0d2e1, 0xf9c76fc3, 0x5e3df4d1
	};
	const uint32_t expected_y9[] = {
		0xb6aa2428, 0x96011c85, 0x37fbfbd3, 0x07da39e8, 
		0x0a740213, 0xa95d66bb, 0xc70f2511, 0x5f9768bb
	};
	const point_t expected_p9;
	point_init(&expected_p9, &expected_x9, &expected_y9);

	ec_add(&result, &p9a, &p9b, &EC);

	expect(tester, point_equals(&expected_p9, &result));

	// Test 10
	const uint32_t x10a[] = {
		0xf320cd57, 0x6d14475b, 0x349aae90, 0x8fb5262c, 
		0xc7038069, 0x84c81999, 0x21167d8f, 0xcf23cae9
	};
	const uint32_t y10a[] = {
		0x151c6f56, 0xa5864f06, 0xa2c7749f, 0x0468e9e3, 
		0x887a34d0, 0x87e6d38c, 0x996baedd, 0x8b9c9ed3
	};
	const point_t p10a;
	point_init(&p10a, x10a, y10a);

	const uint32_t x10b[] = {
		0x99901c04, 0x75491bc3, 0x54c56c9a, 0x9cc9af4e, 
		0xc9546b43, 0x9f9d0129, 0x8a449ebe, 0x89d9bf03
	};
	const uint32_t y10b[] = {
		0x3a641141, 0x514c6b7b, 0x1cd7f671, 0xac2e39e5, 
		0xa32e3837, 0xbe34be70, 0x0835ad12, 0x799ad7a4
	};
	const point_t p10b;
	point_init(&p10b, x10b, y10b);

	const uint32_t expected_x10[] = {
		0xb555c0c7, 0x675446f6, 0xf264d16e, 0x21f8402f, 
		0xda41d8e2, 0xdf54ecea, 0xceb80683, 0xcafebd79
	};
	const uint32_t expected_y10[] = {
		0xfd3b53a9, 0x54f442b2, 0xd8703af7, 0xac7eadcf, 
		0x8b242d88, 0xd7413a58, 0x6e855de8, 0x8dd5f491
	};
	const point_t expected_p10;
	point_init(&expected_p10, &expected_x10, &expected_y10);

	ec_add(&result, &p10a, &p10b, &EC);

	expect(tester, point_equals(&expected_p10, &result));

	// Test 11
	const uint32_t x11a[] = {
		0x2e47dc0e, 0x959f3a51, 0x8cfe5cd1, 0x2d5db79b, 
		0xa2a7ae1f, 0x3ac7652c, 0xcdf84404, 0x07295e43
	};
	const uint32_t y11a[] = {
		0x948623ae, 0xfa399e2d, 0x2514e9bc, 0xdc8748a8, 
		0x68ddc416, 0x96bc3b5a, 0xaef7a97b, 0x992126e7
	};
	const point_t p11a;
	point_init(&p11a, x11a, y11a);

	const uint32_t x11b[] = {
		0xee52bdb6, 0xd1020a15, 0xd9ed17e3, 0xcc0e95ee, 
		0x8d103ed3, 0xcc667e97, 0x1773308c, 0xdc6b13ac
	};
	const uint32_t y11b[] = {
		0x11b463cd, 0xf7914171, 0xd3def30e, 0x5523d137, 
		0xfe30ced9, 0x11895699, 0xde0c8851, 0xbf33ab24
	};
	const point_t p11b;
	point_init(&p11b, x11b, y11b);

	const uint32_t expected_x11[] = {
		0x5c05ab7d, 0xb135f95e, 0xf07185f7, 0x5d4b0cfd, 
		0xd30e8200, 0x720b47da, 0x246f6480, 0x622a8ab0
	};
	const uint32_t expected_y11[] = {
		0xeea3819a, 0x7ee66d85, 0x90e20ec3, 0x9db16cd2, 
		0xab6bdf8f, 0x697eee59, 0x9ad211f9, 0xe1071f32
	};
	const point_t expected_p11;
	point_init(&expected_p11, &expected_x11, &expected_y11);

	ec_add(&result, &p11a, &p11b, &EC);

	expect(tester, point_equals(&expected_p11, &result));

	// Test 12
	const uint32_t x12a[] = {
		0x2adf559a, 0x11cbc288, 0x4a5012dc, 0x582c18c9, 
		0x2f429ce5, 0x9ff3078f, 0xcc1b0c3e, 0x1c07724f
	};
	const uint32_t y12a[] = {
		0x07d006c1, 0xaa99c36f, 0xd669f3a5, 0xa9130e46, 
		0x65b590aa, 0xc7cb8bd7, 0x13445d87, 0x374dbd5e
	};
	const point_t p12a;
	point_init(&p12a, x12a, y12a);

	const uint32_t x12b[] = {
		0xa5f09e63, 0x45ddb87d, 0xa81aa40a, 0x2b0b8c12, 
		0xf3b37f32, 0x870266c4, 0x4155d7ef, 0x28dd37ec
	};
	const uint32_t y12b[] = {
		0xf2a30d5b, 0x67839dae, 0xeab9356a, 0x0769bd56, 
		0x88ef1052, 0x5392ae7e, 0x6bd58c95, 0xbd133a7f
	};
	const point_t p12b;
	point_init(&p12b, x12b, y12b);

	const uint32_t expected_x12[] = {
		0x20547da7, 0x3328fe5c, 0x983a5e48, 0x353cf14a, 
		0xae31770f, 0xdbb8ba35, 0xa3c950cb, 0xd99e0c75
	};
	const uint32_t expected_y12[] = {
		0x4e355f99, 0x7bf0751c, 0x962cfd82, 0x08107719, 
		0xed783adc, 0x7aa458b9, 0xac1f8c75, 0x086be8dd
	};
	const point_t expected_p12;
	point_init(&expected_p12, &expected_x12, &expected_y12);

	ec_add(&result, &p12a, &p12b, &EC);

	expect(tester, point_equals(&expected_p12, &result));

	log_tests(tester);
}

int main() {
    test_point_init();
    test_get_identity();
    test_point_equals();
    test_point_is_identity();
    test_ec_init();

    ec_init(&EC, A, B, P, N, &G);

    test_ec_add();

    return 1;
}
