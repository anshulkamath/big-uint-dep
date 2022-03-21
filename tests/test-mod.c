#include "mod.h"

#include <stdlib.h>
#include <stdio.h>
#include "testing-logger.h"

void test_mod_big_uint() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t n1[] = { 0xc386bbc4 };
	const uint32_t p1[] = { 0x0000000d };
	const uint32_t expected1[] = { 0x00000006 };

	mod_big_uint(result, n1, p1, 1);

	expect(tester, big_uint_equals(expected1, result, 1));

	// Test 2
	const uint32_t n2[] = { 0x1e2feb89, 0x414c343c };
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const uint32_t expected2[] = { 0x00000000, 0x00000008 };

	mod_big_uint(result, n2, p2, 2);

	expect(tester, big_uint_equals(expected2, result, 2));

	// Test 3
	const uint32_t n3[] = { 0x35bf992d, 0xc9e9c616, 0x612e7696 };
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const uint32_t expected3[] = { 0x00000000, 0x00000000, 0x0000000c };

	mod_big_uint(result, n3, p3, 3);

	expect(tester, big_uint_equals(expected3, result, 3));

	// Test 4
	const uint32_t n4[] = { 0x63ca828d, 0xd5f4b3b2 };
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected4[] = { 0x26cf9152, 0x89b5ff93 };

	mod_big_uint(result, n4, p4, 2);

	expect(tester, big_uint_equals(expected4, result, 2));

	// Test 5
	const uint32_t n5[] = { 0xc4647159, 0xc324c985, 0x9b810e76 };
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected5[] = { 0x00000000, 0x07881c97, 0x401b0619 };

	mod_big_uint(result, n5, p5, 3);

	expect(tester, big_uint_equals(expected5, result, 3));

	// Test 6
	const uint32_t n6[] = { 0x51431193, 0xe6c3f339, 0x1a2b8f1f };
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected6[] = { 0x00000000, 0x30be2a1b, 0x5e721204 };

	mod_big_uint(result, n6, p6, 3);

	expect(tester, big_uint_equals(expected6, result, 3));

	// Test 7
	const uint32_t n7[] = { 0x8a9a021e, 0xa648a7dd, 0x06839eb9, 0x05b6e6e3 };
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected7[] = { 0x00000000, 0x00000000, 0x0ee451e6, 0x7971d668 };

	mod_big_uint(result, n7, p7, 4);

	expect(tester, big_uint_equals(expected7, result, 4));

	// Test 8
	const uint32_t n8[] = { 0xe1988ad9, 0xf06c144a };
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected8[] = { 0x6e995ed1, 0xa8491965 };

	mod_big_uint(result, n8, p8, 2);

	expect(tester, big_uint_equals(expected8, result, 2));

	// Test 9
	const uint32_t n9[] = { 0xf8130c42, 0x37730edf, 0xafbd67f9 };
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected9[] = { 0x00000000, 0x49802c63, 0x62b9fd71 };

	mod_big_uint(result, n9, p9, 3);

	expect(tester, big_uint_equals(expected9, result, 3));

	// Test 10
	const uint32_t n10[] = { 0x8712b8bc, 0x076f3787, 0xb9d179e0 };
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected10[] = { 0x00000000, 0x5c43303f, 0xa8844e23 };

	mod_big_uint(result, n10, p10, 3);

	expect(tester, big_uint_equals(expected10, result, 3));

	// Test 11
	const uint32_t n11[] = { 0xad45f23d, 0x3b1a11df, 0x587fd280, 0x3bab6c39 };
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected11[] = { 0x00000000, 0x00000000, 0x419a03ab, 0x2c50ed86 };

	mod_big_uint(result, n11, p11, 4);

	expect(tester, big_uint_equals(expected11, result, 4));

	log_tests(tester);
}

void test_mod_add() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t m1[] = { 0x00000008 };
	const uint32_t n1[] = { 0x00000002 };
	const uint32_t p1[] = { 0x0000000d };
	const uint32_t expected1[] = { 0x0000000a };

	mod_add(result, m1, n1, p1, 1);

	expect(tester, big_uint_equals(expected1, result, 1));

	// Test 2
	const uint32_t m2[] = { 0x00000000, 0x00000009 };
	const uint32_t n2[] = { 0x00000000, 0x00000006 };
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const uint32_t expected2[] = { 0x00000000, 0x00000002 };

	mod_add(result, m2, n2, p2, 2);

	expect(tester, big_uint_equals(expected2, result, 2));

	// Test 3
	const uint32_t m3[] = { 0x00000000, 0x00000000, 0x0000000b };
	const uint32_t n3[] = { 0x00000000, 0x00000000, 0x00000003 };
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const uint32_t expected3[] = { 0x00000000, 0x00000000, 0x00000001 };

	mod_add(result, m3, n3, p3, 3);

	expect(tester, big_uint_equals(expected3, result, 3));

	// Test 4
	const uint32_t m4[] = { 0x1531dba6, 0xd9a9056f };
	const uint32_t n4[] = { 0x00fa4545, 0x70594719 };
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected4[] = { 0x162c20ec, 0x4a024c88 };

	mod_add(result, m4, n4, p4, 2);

	expect(tester, big_uint_equals(expected4, result, 2));

	// Test 5
	const uint32_t m5[] = { 0x00000000, 0x1761d93a, 0x15aca0a2 };
	const uint32_t n5[] = { 0x00000000, 0x23c88a71, 0x587d96ff };
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected5[] = { 0x00000000, 0x3b2a63ab, 0x6e2a37a1 };

	mod_add(result, m5, n5, p5, 3);

	expect(tester, big_uint_equals(expected5, result, 3));

	// Test 6
	const uint32_t m6[] = { 0x00000000, 0x24489e86, 0xb96a983e };
	const uint32_t n6[] = { 0x00000000, 0x1ba0bdd3, 0xf70fa630 };
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected6[] = { 0x00000000, 0x02ee6b1f, 0x643b8a4f };

	mod_add(result, m6, n6, p6, 3);

	expect(tester, big_uint_equals(expected6, result, 3));

	// Test 7
	const uint32_t m7[] = { 0x00000000, 0x00000000, 0x377a29a2, 0xcccaa39b };
	const uint32_t n7[] = { 0x00000000, 0x00000000, 0x0e7d83b5, 0xb7ca57e2 };
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected7[] = { 0x00000000, 0x00000000, 0x08fcbc1d, 0x3856475e };

	mod_add(result, m7, n7, p7, 4);

	expect(tester, big_uint_equals(expected7, result, 4));

	// Test 8
	const uint32_t m8[] = { 0x1aee108e, 0x49c87f15 };
	const uint32_t n8[] = { 0x6bb9d044, 0x33068226 };
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected8[] = { 0x13a8b4ca, 0x34ac0656 };

	mod_add(result, m8, n8, p8, 2);

	expect(tester, big_uint_equals(expected8, result, 2));

	// Test 9
	const uint32_t m9[] = { 0x00000000, 0x28d8c9e3, 0x5c8117b3 };
	const uint32_t n9[] = { 0x00000000, 0x054a42fe, 0xfb12c0f0 };
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected9[] = { 0x00000000, 0x2e230ce2, 0x5793d8a3 };

	mod_add(result, m9, n9, p9, 3);

	expect(tester, big_uint_equals(expected9, result, 3));

	// Test 10
	const uint32_t m10[] = { 0x00000000, 0x3008c6e5, 0x3287b533 };
	const uint32_t n10[] = { 0x00000000, 0x48874bdd, 0xd0f7ba17 };
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected10[] = { 0x00000000, 0x0590e6ba, 0xbb5c7465 };

	mod_add(result, m10, n10, p10, 3);

	expect(tester, big_uint_equals(expected10, result, 3));

	// Test 11
	const uint32_t m11[] = { 0x00000000, 0x00000000, 0x53585734, 0xe6df845a };
	const uint32_t n11[] = { 0x00000000, 0x00000000, 0x0e56e9db, 0x03e8846e };
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected11[] = { 0x00000000, 0x00000000, 0x61af410f, 0xeac808c8 };

	mod_add(result, m11, n11, p11, 4);

	expect(tester, big_uint_equals(expected11, result, 4));

	log_tests(tester);
}

void test_mod_sub() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t m1[] = { 0x00000000 };
	const uint32_t n1[] = { 0x0000000a };
	const uint32_t p1[] = { 0x0000000d };
	const uint32_t expected1[] = { 0x00000003 };

	mod_sub(result, m1, n1, p1, 1);

	expect(tester, big_uint_equals(expected1, result, 1));

	// Test 2
	const uint32_t m2[] = { 0x00000000, 0x00000006 };
	const uint32_t n2[] = { 0x00000000, 0x0000000c };
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const uint32_t expected2[] = { 0x00000000, 0x00000007 };

	mod_sub(result, m2, n2, p2, 2);

	expect(tester, big_uint_equals(expected2, result, 2));

	// Test 3
	const uint32_t m3[] = { 0x00000000, 0x00000000, 0x00000007 };
	const uint32_t n3[] = { 0x00000000, 0x00000000, 0x00000001 };
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const uint32_t expected3[] = { 0x00000000, 0x00000000, 0x00000006 };

	mod_sub(result, m3, n3, p3, 3);

	expect(tester, big_uint_equals(expected3, result, 3));

	// Test 4
	const uint32_t m4[] = { 0x3c4e1d70, 0x32db813f };
	const uint32_t n4[] = { 0x39e9622d, 0xdbe9eb3c };
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected4[] = { 0x0264bb42, 0x56f19603 };

	mod_sub(result, m4, n4, p4, 2);

	expect(tester, big_uint_equals(expected4, result, 2));

	// Test 5
	const uint32_t m5[] = { 0x00000000, 0x06137097, 0x6d354a3a };
	const uint32_t n5[] = { 0x00000000, 0x15300f57, 0x0fedb4d8 };
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected5[] = { 0x00000000, 0x2dde527b, 0xa9864981 };

	mod_sub(result, m5, n5, p5, 3);

	expect(tester, big_uint_equals(expected5, result, 3));

	// Test 6
	const uint32_t m6[] = { 0x00000000, 0x2a2cf1bc, 0x037bfc22 };
	const uint32_t n6[] = { 0x00000000, 0x1d4a0f70, 0x594b4417 };
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected6[] = { 0x00000000, 0x0ce2e24b, 0xaa30b80b };

	mod_sub(result, m6, n6, p6, 3);

	expect(tester, big_uint_equals(expected6, result, 3));

	// Test 7
	const uint32_t m7[] = { 0x00000000, 0x00000000, 0x1206ec84, 0x55bcab48 };
	const uint32_t n7[] = { 0x00000000, 0x00000000, 0x1facb676, 0x08fc35fe };
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected7[] = { 0x00000000, 0x00000000, 0x2f552749, 0x98ff2969 };

	mod_sub(result, m7, n7, p7, 4);

	expect(tester, big_uint_equals(expected7, result, 4));

	// Test 8
	const uint32_t m8[] = { 0x0c250a03, 0xe023033d };
	const uint32_t n8[] = { 0x11ca2ae3, 0x8fe6d25e };
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected8[] = { 0x6d5a0b28, 0x985f2bc4 };

	mod_sub(result, m8, n8, p8, 2);

	expect(tester, big_uint_equals(expected8, result, 2));

	// Test 9
	const uint32_t m9[] = { 0x00000000, 0x2dfbfdb1, 0xdefa5f21 };
	const uint32_t n9[] = { 0x00000000, 0x6c61d9a6, 0xfc8a0649 };
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected9[] = { 0x00000000, 0x34995013, 0x2a9353bd };

	mod_sub(result, m9, n9, p9, 3);

	expect(tester, big_uint_equals(expected9, result, 3));

	// Test 10
	const uint32_t m10[] = { 0x00000000, 0x04f06966, 0x95e5722f };
	const uint32_t n10[] = { 0x00000000, 0x4c8f6d94, 0x2aad363b };
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected10[] = { 0x00000000, 0x2b6027da, 0xb35b36d9 };

	mod_sub(result, m10, n10, p10, 3);

	expect(tester, big_uint_equals(expected10, result, 3));

	// Test 11
	const uint32_t m11[] = { 0x00000000, 0x00000000, 0x5ffbbd9a, 0xbedc204c };
	const uint32_t n11[] = { 0x00000000, 0x00000000, 0x2006cc6a, 0xc1230093 };
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected11[] = { 0x00000000, 0x00000000, 0x3ff4f12f, 0xfdb91fb9 };

	mod_sub(result, m11, n11, p11, 4);

	expect(tester, big_uint_equals(expected11, result, 4));

	log_tests(tester);
}

void test_mod_init() {
	testing_logger_t *tester = create_tester();

	// Test 1
	const uint32_t p1[] = { 0x0000000d };
	const uint32_t expected_k1 = 1;
	const size_t expected_digits1 = 1;
	const uint32_t expected_p1[] = { 0x00000000, 0x00000000, 0x0000000d };
	const uint32_t expected_r1[] = { 0x00000000, 0x13b13b13, 0xb13b13b1 };

	const mod_t result_mod1 = mod_init(p1, 1);

	expect(tester, 
		expected_k1 == result_mod1.k &&
		expected_digits1 == result_mod1.len &&
		big_uint_equals(expected_p1, result_mod1.p, 3) &&
		big_uint_equals(expected_r1, result_mod1.r, 3)
	);

	// Test 2
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const uint32_t expected_k2 = 1;
	const size_t expected_digits2 = 2;
	const uint32_t expected_p2[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000000d };
	const uint32_t expected_r2[] = { 0x00000000, 0x00000000, 0x00000000, 0x13b13b13, 0xb13b13b1 };

	const mod_t result_mod2 = mod_init(p2, 2);

	expect(tester, 
		expected_k2 == result_mod2.k &&
		expected_digits2 == result_mod2.len &&
		big_uint_equals(expected_p2, result_mod2.p, 5) &&
		big_uint_equals(expected_r2, result_mod2.r, 5)
	);

	// Test 3
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const uint32_t expected_k3 = 1;
	const size_t expected_digits3 = 3;
	const uint32_t expected_p3[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000000d };
	const uint32_t expected_r3[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x13b13b13, 0xb13b13b1 };

	const mod_t result_mod3 = mod_init(p3, 3);

	expect(tester, 
		expected_k3 == result_mod3.k &&
		expected_digits3 == result_mod3.len &&
		big_uint_equals(expected_p3, result_mod3.p, 7) &&
		big_uint_equals(expected_r3, result_mod3.r, 7)
	);

	// Test 4
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected_k4 = 2;
	const size_t expected_digits4 = 2;
	const uint32_t expected_p4[] = { 0x00000000, 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected_r4[] = { 0x00000000, 0x00000000, 0x00000004, 0x32b56f64, 0x2c6cf995 };

	const mod_t result_mod4 = mod_init(p4, 2);

	expect(tester, 
		expected_k4 == result_mod4.k &&
		expected_digits4 == result_mod4.len &&
		big_uint_equals(expected_p4, result_mod4.p, 5) &&
		big_uint_equals(expected_r4, result_mod4.r, 5)
	);

	// Test 5
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected_k5 = 2;
	const size_t expected_digits5 = 3;
	const uint32_t expected_p5[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected_r5[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000004, 0x32b56f64, 0x2c6cf995 };

	const mod_t result_mod5 = mod_init(p5, 3);

	expect(tester, 
		expected_k5 == result_mod5.k &&
		expected_digits5 == result_mod5.len &&
		big_uint_equals(expected_p5, result_mod5.p, 7) &&
		big_uint_equals(expected_r5, result_mod5.r, 7)
	);

	// Test 6
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected_k6 = 2;
	const size_t expected_digits6 = 3;
	const uint32_t expected_p6[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected_r6[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000004, 0x32b56f64, 0x2c6cf995 };

	const mod_t result_mod6 = mod_init(p6, 3);

	expect(tester, 
		expected_k6 == result_mod6.k &&
		expected_digits6 == result_mod6.len &&
		big_uint_equals(expected_p6, result_mod6.p, 7) &&
		big_uint_equals(expected_r6, result_mod6.r, 7)
	);

	// Test 7
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected_k7 = 2;
	const size_t expected_digits7 = 4;
	const uint32_t expected_p7[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected_r7[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000004, 0x32b56f64, 0x2c6cf995 };

	const mod_t result_mod7 = mod_init(p7, 4);

	expect(tester, 
		expected_k7 == result_mod7.k &&
		expected_digits7 == result_mod7.len &&
		big_uint_equals(expected_p7, result_mod7.p, 9) &&
		big_uint_equals(expected_r7, result_mod7.r, 9)
	);

	// Test 8
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected_k8 = 2;
	const size_t expected_digits8 = 2;
	const uint32_t expected_p8[] = { 0x00000000, 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected_r8[] = { 0x00000000, 0x00000000, 0x00000002, 0x39e4f021, 0xbb40ef66 };

	const mod_t result_mod8 = mod_init(p8, 2);

	expect(tester, 
		expected_k8 == result_mod8.k &&
		expected_digits8 == result_mod8.len &&
		big_uint_equals(expected_p8, result_mod8.p, 5) &&
		big_uint_equals(expected_r8, result_mod8.r, 5)
	);

	// Test 9
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected_k9 = 2;
	const size_t expected_digits9 = 3;
	const uint32_t expected_p9[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected_r9[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x39e4f021, 0xbb40ef66 };

	const mod_t result_mod9 = mod_init(p9, 3);

	expect(tester, 
		expected_k9 == result_mod9.k &&
		expected_digits9 == result_mod9.len &&
		big_uint_equals(expected_p9, result_mod9.p, 7) &&
		big_uint_equals(expected_r9, result_mod9.r, 7)
	);

	// Test 10
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected_k10 = 2;
	const size_t expected_digits10 = 3;
	const uint32_t expected_p10[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected_r10[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x39e4f021, 0xbb40ef66 };

	const mod_t result_mod10 = mod_init(p10, 3);

	expect(tester, 
		expected_k10 == result_mod10.k &&
		expected_digits10 == result_mod10.len &&
		big_uint_equals(expected_p10, result_mod10.p, 7) &&
		big_uint_equals(expected_r10, result_mod10.r, 7)
	);

	// Test 11
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected_k11 = 2;
	const size_t expected_digits11 = 4;
	const uint32_t expected_p11[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected_r11[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x39e4f021, 0xbb40ef66 };

	const mod_t result_mod11 = mod_init(p11, 4);

	expect(tester, 
		expected_k11 == result_mod11.k &&
		expected_digits11 == result_mod11.len &&
		big_uint_equals(expected_p11, result_mod11.p, 9) &&
		big_uint_equals(expected_r11, result_mod11.r, 9)
	);

	log_tests(tester);
}

void test_mod_mult() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t m1[] = { 0x00000003 };
	const uint32_t n1[] = { 0x0000000a };
	const uint32_t p1[] = { 0x0000000d };
	const mod_t    mod1 = mod_init(p1, 1);
	const uint32_t expected1[] = { 0x00000004 };

	mod_mult(result, m1, n1, &mod1, 1);

	expect(tester, big_uint_equals(expected1, result, 1));

	// Test 2
	const uint32_t m2[] = { 0x00000000, 0x00000007 };
	const uint32_t n2[] = { 0x00000000, 0x00000003 };
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const mod_t    mod2 = mod_init(p2, 2);
	const uint32_t expected2[] = { 0x00000000, 0x00000008 };

	mod_mult(result, m2, n2, &mod2, 2);

	expect(tester, big_uint_equals(expected2, result, 2));

	// Test 3
	const uint32_t m3[] = { 0x00000000, 0x00000000, 0x00000005 };
	const uint32_t n3[] = { 0x00000000, 0x00000000, 0x00000009 };
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const mod_t    mod3 = mod_init(p3, 3);
	const uint32_t expected3[] = { 0x00000000, 0x00000000, 0x00000006 };

	mod_mult(result, m3, n3, &mod3, 3);

	expect(tester, big_uint_equals(expected3, result, 3));

	// Test 4
	const uint32_t m4[] = { 0x0fd229d7, 0x50b9169b };
	const uint32_t n4[] = { 0x2b711343, 0x220d672b };
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod4 = mod_init(p4, 2);
	const uint32_t expected4[] = { 0x2bfea46b, 0x2a04608d };

	mod_mult(result, m4, n4, &mod4, 2);

	expect(tester, big_uint_equals(expected4, result, 2));

	// Test 5
	const uint32_t m5[] = { 0x00000000, 0x085d8597, 0x859937c4 };
	const uint32_t n5[] = { 0x00000000, 0x0252c228, 0x2e6c6735 };
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod5 = mod_init(p5, 3);
	const uint32_t expected5[] = { 0x00000000, 0x008e862f, 0x9dc7fe4b };

	mod_mult(result, m5, n5, &mod5, 3);

	expect(tester, big_uint_equals(expected5, result, 3));

	// Test 6
	const uint32_t m6[] = { 0x00000000, 0x04d7ee10, 0x885d26e6 };
	const uint32_t n6[] = { 0x00000000, 0x2e3afc03, 0xb27c3735 };
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod6 = mod_init(p6, 3);
	const uint32_t expected6[] = { 0x00000000, 0x0e4e6cb3, 0xfb58d6ed };

	mod_mult(result, m6, n6, &mod6, 3);

	expect(tester, big_uint_equals(expected6, result, 3));

	// Test 7
	const uint32_t m7[] = { 0x00000000, 0x00000000, 0x069b0316, 0x81d24604 };
	const uint32_t n7[] = { 0x00000000, 0x00000000, 0x2086ccd2, 0x9f820d6b };
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod7 = mod_init(p7, 4);
	const uint32_t expected7[] = { 0x00000000, 0x00000000, 0x177590f0, 0x22d2fd5c };

	mod_mult(result, m7, n7, &mod7, 4);

	expect(tester, big_uint_equals(expected7, result, 4));

	// Test 8
	const uint32_t m8[] = { 0x297a21d7, 0x6bc78bf5 };
	const uint32_t n8[] = { 0x301ba988, 0x0a3efb80 };
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod8 = mod_init(p8, 2);
	const uint32_t expected8[] = { 0x4cceb8e3, 0xa2cd6fc9 };

	mod_mult(result, m8, n8, &mod8, 2);

	expect(tester, big_uint_equals(expected8, result, 2));

	// Test 9
	const uint32_t m9[] = { 0x00000000, 0x67dd4e30, 0xe02acd3b };
	const uint32_t n9[] = { 0x00000000, 0x3e859b93, 0xa2743a06 };
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod9 = mod_init(p9, 3);
	const uint32_t expected9[] = { 0x00000000, 0x46163aa6, 0x7cc90739 };

	mod_mult(result, m9, n9, &mod9, 3);

	expect(tester, big_uint_equals(expected9, result, 3));

	// Test 10
	const uint32_t m10[] = { 0x00000000, 0x69ccbf03, 0xe15253e0 };
	const uint32_t n10[] = { 0x00000000, 0x4393b6e9, 0x368d7999 };
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod10 = mod_init(p10, 3);
	const uint32_t expected10[] = { 0x00000000, 0x199c211a, 0x9a6a8d05 };

	mod_mult(result, m10, n10, &mod10, 3);

	expect(tester, big_uint_equals(expected10, result, 3));

	// Test 11
	const uint32_t m11[] = { 0x00000000, 0x00000000, 0x185ce898, 0x5d508b67 };
	const uint32_t n11[] = { 0x00000000, 0x00000000, 0x05bc51e1, 0x4cbe9d72 };
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod11 = mod_init(p11, 4);
	const uint32_t expected11[] = { 0x00000000, 0x00000000, 0x0385a208, 0x13d42405 };

	mod_mult(result, m11, n11, &mod11, 4);

	expect(tester, big_uint_equals(expected11, result, 4));

	// Test 12a
	// Operator assignment
	uint32_t m12a[] = { 0x0000000c };
	const uint32_t n12a[] = { 0x0000000a };
	const uint32_t p12a[] = { 0x0000000d };
	const mod_t    mod12a = mod_init(p12a, 1);
	const uint32_t expected12a[] = { 0x00000003 };

	mod_mult(m12a, m12a, n12a, &mod12a, 1);

	expect(tester, big_uint_equals(expected12a, m12a, 1));

	// Test 13b
	// Operator assignment
	uint32_t m13b[] = { 0x00000001 };
	const uint32_t n13b[] = { 0x00000008 };
	const uint32_t p13b[] = { 0x0000000d };
	const mod_t    mod13b = mod_init(p13b, 1);
	const uint32_t expected13b[] = { 0x00000008 };

	mod_mult(m13b, n13b, m13b, &mod13b, 1);

	expect(tester, big_uint_equals(expected13b, m13b, 1));

	// Test 14a
	// Operator assignment
	uint32_t m14a[] = { 0x1c823d9e, 0x74b31bfb };
	const uint32_t n14a[] = { 0x32e33b79, 0x2bb2c64e };
	const uint32_t p14a[] = { 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod14a = mod_init(p14a, 2);
	const uint32_t expected14a[] = { 0x2681f5e3, 0x3a046890 };

	mod_mult(m14a, m14a, n14a, &mod14a, 2);

	expect(tester, big_uint_equals(expected14a, m14a, 2));

	// Test 15b
	// Operator assignment
	uint32_t m15b[] = { 0x11b1a79a, 0xe8f6188f };
	const uint32_t n15b[] = { 0x2f7818b5, 0xdf8dbd9b };
	const uint32_t p15b[] = { 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod15b = mod_init(p15b, 2);
	const uint32_t expected15b[] = { 0x37c03da0, 0xc4fcf0bb };

	mod_mult(m15b, n15b, m15b, &mod15b, 2);

	expect(tester, big_uint_equals(expected15b, m15b, 2));

	// Test 16a
	// Operator assignment
	uint32_t m16a[] = { 0x47e1a38b, 0xd1ea0418 };
	const uint32_t n16a[] = { 0x5c47577b, 0x3f12d68e };
	const uint32_t p16a[] = { 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod16a = mod_init(p16a, 2);
	const uint32_t expected16a[] = { 0x2eab600b, 0x49a1380f };

	mod_mult(m16a, m16a, n16a, &mod16a, 2);

	expect(tester, big_uint_equals(expected16a, m16a, 2));

	// Test 17b
	// Operator assignment
	uint32_t m17b[] = { 0x0a826695, 0x4e896a65 };
	const uint32_t n17b[] = { 0x4dd83958, 0xb39b989c };
	const uint32_t p17b[] = { 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod17b = mod_init(p17b, 2);
	const uint32_t expected17b[] = { 0x3acfbfda, 0x1e039f78 };

	mod_mult(m17b, n17b, m17b, &mod17b, 2);

	expect(tester, big_uint_equals(expected17b, m17b, 2));

	log_tests(tester);
}

void test_mod_exp() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t m1[] = { 0x00000008 };
	const uint32_t n1[] = { 0x00000004 };
	const uint32_t p1[] = { 0x0000000d };
	const mod_t    mod1 = mod_init(p1, 1);
	const uint32_t expected1[] = { 0x00000001 };

	mod_exp(result, m1, n1, &mod1, 1);

	expect(tester, big_uint_equals(expected1, result, 1));

	// Test 2
	const uint32_t m2[] = { 0x00000000, 0x00000004 };
	const uint32_t n2[] = { 0x00000000, 0x00000005 };
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const mod_t    mod2 = mod_init(p2, 2);
	const uint32_t expected2[] = { 0x00000000, 0x0000000a };

	mod_exp(result, m2, n2, &mod2, 2);

	expect(tester, big_uint_equals(expected2, result, 2));

	// Test 3
	const uint32_t m3[] = { 0x00000000, 0x00000000, 0x0000000a };
	const uint32_t n3[] = { 0x00000000, 0x00000000, 0x0000000c };
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const mod_t    mod3 = mod_init(p3, 3);
	const uint32_t expected3[] = { 0x00000000, 0x00000000, 0x00000001 };

	mod_exp(result, m3, n3, &mod3, 3);

	expect(tester, big_uint_equals(expected3, result, 3));

	// Test 4
	const uint32_t m4[] = { 0x24fe23c8, 0xf81a73cc };
	const uint32_t n4[] = { 0x045078a2, 0xc3768f0f };
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod4 = mod_init(p4, 2);
	const uint32_t expected4[] = { 0x377d3ae1, 0xf6fd591f };

	mod_exp(result, m4, n4, &mod4, 2);

	expect(tester, big_uint_equals(expected4, result, 2));

	// Test 5
	const uint32_t m5[] = { 0x00000000, 0x0b720033, 0x239f108c };
	const uint32_t n5[] = { 0x00000000, 0x39ef56ad, 0x1cd40184 };
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod5 = mod_init(p5, 3);
	const uint32_t expected5[] = { 0x00000000, 0x068ef9a6, 0x2de39238 };

	mod_exp(result, m5, n5, &mod5, 3);

	expect(tester, big_uint_equals(expected5, result, 3));

	// Test 6
	const uint32_t m6[] = { 0x00000000, 0x0108031f, 0x03f161e2 };
	const uint32_t n6[] = { 0x00000000, 0x238ef8a0, 0x0719d671 };
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod6 = mod_init(p6, 3);
	const uint32_t expected6[] = { 0x00000000, 0x2024305e, 0x9e503fec };

	mod_exp(result, m6, n6, &mod6, 3);

	expect(tester, big_uint_equals(expected6, result, 3));

	// Test 7
	const uint32_t m7[] = { 0x00000000, 0x00000000, 0x33850486, 0x0efd220e };
	const uint32_t n7[] = { 0x00000000, 0x00000000, 0x1ac678d8, 0xea1695ce };
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod7 = mod_init(p7, 4);
	const uint32_t expected7[] = { 0x00000000, 0x00000000, 0x25c0b21b, 0x33565359 };

	mod_exp(result, m7, n7, &mod7, 4);

	expect(tester, big_uint_equals(expected7, result, 4));

	// Test 8
	const uint32_t m8[] = { 0x420a4323, 0x2be893f4 };
	const uint32_t n8[] = { 0x6317fed7, 0x1d2a4cb5 };
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod8 = mod_init(p8, 2);
	const uint32_t expected8[] = { 0x2eab9d7b, 0xf7c19af2 };

	mod_exp(result, m8, n8, &mod8, 2);

	expect(tester, big_uint_equals(expected8, result, 2));

	// Test 9
	const uint32_t m9[] = { 0x00000000, 0x6ab76b1e, 0x0cd311de };
	const uint32_t n9[] = { 0x00000000, 0x6b8fdf15, 0x60f89a06 };
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod9 = mod_init(p9, 3);
	const uint32_t expected9[] = { 0x00000000, 0x075de947, 0x90c3bf40 };

	mod_exp(result, m9, n9, &mod9, 3);

	expect(tester, big_uint_equals(expected9, result, 3));

	// Test 10
	const uint32_t m10[] = { 0x00000000, 0x47eaf205, 0xf1c31001 };
	const uint32_t n10[] = { 0x00000000, 0x52ddbb24, 0x8c35ddd6 };
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod10 = mod_init(p10, 3);
	const uint32_t expected10[] = { 0x00000000, 0x6cf558eb, 0x482ee859 };

	mod_exp(result, m10, n10, &mod10, 3);

	expect(tester, big_uint_equals(expected10, result, 3));

	// Test 11
	const uint32_t m11[] = { 0x00000000, 0x00000000, 0x2142fbbd, 0x64a1f040 };
	const uint32_t n11[] = { 0x00000000, 0x00000000, 0x4f093df5, 0xaf3e5dbf };
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod11 = mod_init(p11, 4);
	const uint32_t expected11[] = { 0x00000000, 0x00000000, 0x6ab002dc, 0xd6250eed };

	mod_exp(result, m11, n11, &mod11, 4);

	expect(tester, big_uint_equals(expected11, result, 4));

	// Test 12a
	// Operator assignment
	uint32_t m12a[] = { 0x00000006 };
	const uint32_t n12a[] = { 0x0000000a };
	const uint32_t p12a[] = { 0x0000000d };
	const mod_t    mod12a = mod_init(p12a, 1);
	const uint32_t expected12a[] = { 0x00000004 };

	mod_exp(m12a, m12a, n12a, &mod12a, 1);

	expect(tester, big_uint_equals(expected12a, m12a, 1));

	// Test 13a
	// Operator assignment
	uint32_t m13a[] = { 0x216788a0, 0x9460293b };
	const uint32_t n13a[] = { 0x34fd616f, 0x279a8cd0 };
	const uint32_t p13a[] = { 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod13a = mod_init(p13a, 2);
	const uint32_t expected13a[] = { 0x15aa555c, 0x36e2df4f };

	mod_exp(m13a, m13a, n13a, &mod13a, 2);

	expect(tester, big_uint_equals(expected13a, m13a, 2));

	// Test 14a
	// Operator assignment
	uint32_t m14a[] = { 0x3e4c3dd4, 0x0455ccc6 };
	const uint32_t n14a[] = { 0x342f22ba, 0xe20cea4a };
	const uint32_t p14a[] = { 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod14a = mod_init(p14a, 2);
	const uint32_t expected14a[] = { 0x67a065fa, 0xa8c5d5a3 };

	mod_exp(m14a, m14a, n14a, &mod14a, 2);

	expect(tester, big_uint_equals(expected14a, m14a, 2));

	log_tests(tester);
}

void test_mod_inv() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t x1[] = { 0x00000008 };
	const uint32_t p1[] = { 0x0000000d };
	const mod_t    mod1 = mod_init(p1, 1);
	const uint32_t expected1[] = { 0x00000005 };

	mod_inv(result, x1, &mod1, 1);

	expect(tester, big_uint_equals(expected1, result, 1));

	// Test 2
	const uint32_t x2[] = { 0x00000000, 0x00000004 };
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const mod_t    mod2 = mod_init(p2, 2);
	const uint32_t expected2[] = { 0x00000000, 0x0000000a };

	mod_inv(result, x2, &mod2, 2);

	expect(tester, big_uint_equals(expected2, result, 2));

	// Test 3
	const uint32_t x3[] = { 0x00000000, 0x00000000, 0x00000009 };
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const mod_t    mod3 = mod_init(p3, 3);
	const uint32_t expected3[] = { 0x00000000, 0x00000000, 0x00000003 };

	mod_inv(result, x3, &mod3, 3);

	expect(tester, big_uint_equals(expected3, result, 3));

	// Test 4
	const uint32_t x4[] = { 0x1151ede8, 0xdd3fccef };
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod4 = mod_init(p4, 2);
	const uint32_t expected4[] = { 0x18ccb6b8, 0x220d84b3 };

	mod_inv(result, x4, &mod4, 2);

	expect(tester, big_uint_equals(expected4, result, 2));

	// Test 5
	const uint32_t x5[] = { 0x00000000, 0x35c832db, 0xe4da6f81 };
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod5 = mod_init(p5, 3);
	const uint32_t expected5[] = { 0x00000000, 0x3784c062, 0x22093e71 };

	mod_inv(result, x5, &mod5, 3);

	expect(tester, big_uint_equals(expected5, result, 3));

	// Test 6
	const uint32_t x6[] = { 0x00000000, 0x3ad812cb, 0x5b3a2a6e };
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod6 = mod_init(p6, 3);
	const uint32_t expected6[] = { 0x00000000, 0x259c8967, 0x614846e7 };

	mod_inv(result, x6, &mod6, 3);

	expect(tester, big_uint_equals(expected6, result, 3));

	// Test 7
	const uint32_t x7[] = { 0x00000000, 0x00000000, 0x22705a48, 0x86ee8c1b };
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod7 = mod_init(p7, 4);
	const uint32_t expected7[] = { 0x00000000, 0x00000000, 0x0cc27c7d, 0x8fc86ec0 };

	mod_inv(result, x7, &mod7, 4);

	expect(tester, big_uint_equals(expected7, result, 4));

	// Test 8
	const uint32_t x8[] = { 0x02fceea4, 0x99e75f55 };
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod8 = mod_init(p8, 2);
	const uint32_t expected8[] = { 0x514fe566, 0x655409fd };

	mod_inv(result, x8, &mod8, 2);

	expect(tester, big_uint_equals(expected8, result, 2));

	// Test 9
	const uint32_t x9[] = { 0x00000000, 0x5931cc1b, 0xde2bacb0 };
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod9 = mod_init(p9, 3);
	const uint32_t expected9[] = { 0x00000000, 0x54d79891, 0x05010fe8 };

	mod_inv(result, x9, &mod9, 3);

	expect(tester, big_uint_equals(expected9, result, 3));

	// Test 10
	const uint32_t x10[] = { 0x00000000, 0x3edecd5b, 0xb0a7c881 };
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod10 = mod_init(p10, 3);
	const uint32_t expected10[] = { 0x00000000, 0x2bdcbd40, 0xf5d145e1 };

	mod_inv(result, x10, &mod10, 3);

	expect(tester, big_uint_equals(expected10, result, 3));

	// Test 11
	const uint32_t x11[] = { 0x00000000, 0x00000000, 0x5395d075, 0x9c0531cd };
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod11 = mod_init(p11, 4);
	const uint32_t expected11[] = { 0x00000000, 0x00000000, 0x348e3193, 0x5fb0a534 };

	mod_inv(result, x11, &mod11, 4);

	expect(tester, big_uint_equals(expected11, result, 4));

	log_tests(tester);
}

void test_mod_div() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t m1[] = { 0x00000008 };
	const uint32_t n1[] = { 0x00000009 };
	const uint32_t p1[] = { 0x0000000d };
	const mod_t    mod1 = mod_init(p1, 1);
	const uint32_t expected1[] = { 0x0000000b };

	mod_div(result, m1, n1, &mod1, 1);

	expect(tester, big_uint_equals(expected1, result, 1));

	// Test 2
	const uint32_t m2[] = { 0x00000000, 0x00000009 };
	const uint32_t n2[] = { 0x00000000, 0x00000006 };
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const mod_t    mod2 = mod_init(p2, 2);
	const uint32_t expected2[] = { 0x00000000, 0x00000008 };

	mod_div(result, m2, n2, &mod2, 2);

	expect(tester, big_uint_equals(expected2, result, 2));

	// Test 3
	const uint32_t m3[] = { 0x00000000, 0x00000000, 0x00000001 };
	const uint32_t n3[] = { 0x00000000, 0x00000000, 0x00000002 };
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const mod_t    mod3 = mod_init(p3, 3);
	const uint32_t expected3[] = { 0x00000000, 0x00000000, 0x00000007 };

	mod_div(result, m3, n3, &mod3, 3);

	expect(tester, big_uint_equals(expected3, result, 3));

	// Test 4
	const uint32_t m4[] = { 0x2a10b913, 0xad531a06 };
	const uint32_t n4[] = { 0x0df0c5ef, 0x3a722caf };
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod4 = mod_init(p4, 2);
	const uint32_t expected4[] = { 0x321346f4, 0x80a508d8 };

	mod_div(result, m4, n4, &mod4, 2);

	expect(tester, big_uint_equals(expected4, result, 2));

	// Test 5
	const uint32_t m5[] = { 0x00000000, 0x37c981e9, 0x8f9f936a };
	const uint32_t n5[] = { 0x00000000, 0x3c4dbe96, 0xffffd33e };
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod5 = mod_init(p5, 3);
	const uint32_t expected5[] = { 0x00000000, 0x21ae9b1d, 0xd285b4e1 };

	mod_div(result, m5, n5, &mod5, 3);

	expect(tester, big_uint_equals(expected5, result, 3));

	// Test 6
	const uint32_t m6[] = { 0x00000000, 0x01f93c7f, 0xab869c28 };
	const uint32_t n6[] = { 0x00000000, 0x1a32616b, 0x3959cf9c };
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod6 = mod_init(p6, 3);
	const uint32_t expected6[] = { 0x00000000, 0x006743cb, 0xc4e2f8e3 };

	mod_div(result, m6, n6, &mod6, 3);

	expect(tester, big_uint_equals(expected6, result, 3));

	// Test 7
	const uint32_t m7[] = { 0x00000000, 0x00000000, 0x28edcbba, 0x8b4e8d08 };
	const uint32_t n7[] = { 0x00000000, 0x00000000, 0x0e1d2b49, 0xcadff7d3 };
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod7 = mod_init(p7, 4);
	const uint32_t expected7[] = { 0x00000000, 0x00000000, 0x20168a82, 0xf251b6e6 };

	mod_div(result, m7, n7, &mod7, 4);

	expect(tester, big_uint_equals(expected7, result, 4));

	// Test 8
	const uint32_t m8[] = { 0x4beb808f, 0xb4b2912a };
	const uint32_t n8[] = { 0x1157c8b3, 0xbfaf9e2f };
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod8 = mod_init(p8, 2);
	const uint32_t expected8[] = { 0x10247680, 0x152b0c45 };

	mod_div(result, m8, n8, &mod8, 2);

	expect(tester, big_uint_equals(expected8, result, 2));

	// Test 9
	const uint32_t m9[] = { 0x00000000, 0x1d3eef4e, 0x09dc121e };
	const uint32_t n9[] = { 0x00000000, 0x39cd6b06, 0x9b458658 };
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod9 = mod_init(p9, 3);
	const uint32_t expected9[] = { 0x00000000, 0x6361a347, 0x7aedbf26 };

	mod_div(result, m9, n9, &mod9, 3);

	expect(tester, big_uint_equals(expected9, result, 3));

	// Test 10
	const uint32_t m10[] = { 0x00000000, 0x65e9c6ab, 0x87b774b8 };
	const uint32_t n10[] = { 0x00000000, 0x56b4e413, 0x067c0290 };
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod10 = mod_init(p10, 3);
	const uint32_t expected10[] = { 0x00000000, 0x15084e1c, 0x4c36b37b };

	mod_div(result, m10, n10, &mod10, 3);

	expect(tester, big_uint_equals(expected10, result, 3));

	// Test 11
	const uint32_t m11[] = { 0x00000000, 0x00000000, 0x1b5bef0c, 0xcfe0a55c };
	const uint32_t n11[] = { 0x00000000, 0x00000000, 0x4603fc66, 0xdc027d1d };
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod11 = mod_init(p11, 4);
	const uint32_t expected11[] = { 0x00000000, 0x00000000, 0x2e294437, 0x31752e7b };

	mod_div(result, m11, n11, &mod11, 4);

	expect(tester, big_uint_equals(expected11, result, 4));

	// Test 12a
	// Operator assignment
	uint32_t m12a[] = { 0x00000004 };
	const uint32_t n12a[] = { 0x00000001 };
	const uint32_t p12a[] = { 0x0000000d };
	const mod_t    mod12a = mod_init(p12a, 1);
	const uint32_t expected12a[] = { 0x00000004 };

	mod_div(m12a, m12a, n12a, &mod12a, 1);

	expect(tester, big_uint_equals(expected12a, m12a, 1));

	// Test 13b
	// Operator assignment
	uint32_t m13b[] = { 0x00000004 };
	const uint32_t n13b[] = { 0x00000002 };
	const uint32_t p13b[] = { 0x0000000d };
	const mod_t    mod13b = mod_init(p13b, 1);
	const uint32_t expected13b[] = { 0x00000007 };

	mod_div(m13b, n13b, m13b, &mod13b, 1);

	expect(tester, big_uint_equals(expected13b, m13b, 1));

	// Test 14a
	// Operator assignment
	uint32_t m14a[] = { 0x05a93a5a, 0xaa0619b8 };
	const uint32_t n14a[] = { 0x07e6c71b, 0x093ebe6d };
	const uint32_t p14a[] = { 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod14a = mod_init(p14a, 2);
	const uint32_t expected14a[] = { 0x2e63b9d8, 0x1692f052 };

	mod_div(m14a, m14a, n14a, &mod14a, 2);

	expect(tester, big_uint_equals(expected14a, m14a, 2));

	// Test 15b
	// Operator assignment
	uint32_t m15b[] = { 0x2c1ffacc, 0x6653c3b7 };
	const uint32_t n15b[] = { 0x14700259, 0x3826a89c };
	const uint32_t p15b[] = { 0x3cfaf13b, 0x4c3eb41f };
	const mod_t    mod15b = mod_init(p15b, 2);
	const uint32_t expected15b[] = { 0x21843122, 0xf592d8cc };

	mod_div(m15b, n15b, m15b, &mod15b, 2);

	expect(tester, big_uint_equals(expected15b, m15b, 2));

	// Test 16a
	// Operator assignment
	uint32_t m16a[] = { 0x362da6d6, 0x8fdfd023 };
	const uint32_t n16a[] = { 0x41ea7bfe, 0x5402b7f6 };
	const uint32_t p16a[] = { 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod16a = mod_init(p16a, 2);
	const uint32_t expected16a[] = { 0x04ac296e, 0x3ebf2df1 };

	mod_div(m16a, m16a, n16a, &mod16a, 2);

	expect(tester, big_uint_equals(expected16a, m16a, 2));

	// Test 17b
	// Operator assignment
	uint32_t m17b[] = { 0x309d57ed, 0x44e32dbd };
	const uint32_t n17b[] = { 0x6710b0e7, 0x9f5904a6 };
	const uint32_t p17b[] = { 0x72ff2c08, 0x4822fae5 };
	const mod_t    mod17b = mod_init(p17b, 2);
	const uint32_t expected17b[] = { 0x71b2ac29, 0x56aa1d11 };

	mod_div(m17b, n17b, m17b, &mod17b, 2);

	expect(tester, big_uint_equals(expected17b, m17b, 2));

	log_tests(tester);
}

void test_mod_neg() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t n1[] = { 0x00000008 };
	const uint32_t p1[] = { 0x0000000d };
	const uint32_t expected1[] = { 0x00000005 };

	mod_neg(result, n1, p1, 1);

	expect(tester, big_uint_equals(expected1, result, 1));

	// Test 2
	const uint32_t n2[] = { 0x00000000, 0x00000006 };
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const uint32_t expected2[] = { 0x00000000, 0x00000007 };

	mod_neg(result, n2, p2, 2);

	expect(tester, big_uint_equals(expected2, result, 2));

	// Test 3
	const uint32_t n3[] = { 0x00000000, 0x00000000, 0x00000007 };
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const uint32_t expected3[] = { 0x00000000, 0x00000000, 0x00000006 };

	mod_neg(result, n3, p3, 3);

	expect(tester, big_uint_equals(expected3, result, 3));

	// Test 4
	const uint32_t n4[] = { 0x33d58d7f, 0x6afcac43 };
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected4[] = { 0x092563bb, 0xe14207dc };

	mod_neg(result, n4, p4, 2);

	expect(tester, big_uint_equals(expected4, result, 2));

	// Test 5
	const uint32_t n5[] = { 0x00000000, 0x0dc84de2, 0x6ed412ad };
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected5[] = { 0x00000000, 0x2f32a358, 0xdd6aa172 };

	mod_neg(result, n5, p5, 3);

	expect(tester, big_uint_equals(expected5, result, 3));

	// Test 6
	const uint32_t n6[] = { 0x00000000, 0x04d60b58, 0xe4e649ed };
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected6[] = { 0x00000000, 0x3824e5e2, 0x67586a32 };

	mod_neg(result, n6, p6, 3);

	expect(tester, big_uint_equals(expected6, result, 3));

	// Test 7
	const uint32_t n7[] = { 0x00000000, 0x00000000, 0x3a51855b, 0xc17a6311 };
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected7[] = { 0x00000000, 0x00000000, 0x02a96bdf, 0x8ac4510e };

	mod_neg(result, n7, p7, 4);

	expect(tester, big_uint_equals(expected7, result, 4));

	// Test 8
	const uint32_t n8[] = { 0x25f77a3c, 0x8716f4f2 };
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected8[] = { 0x4d07b1cb, 0xc10c05f3 };

	mod_neg(result, n8, p8, 2);

	expect(tester, big_uint_equals(expected8, result, 2));

	// Test 9
	const uint32_t n9[] = { 0x00000000, 0x19b19c2e, 0x5bc02e26 };
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected9[] = { 0x00000000, 0x594d8fd9, 0xec62ccbf };

	mod_neg(result, n9, p9, 3);

	expect(tester, big_uint_equals(expected9, result, 3));

	// Test 10
	const uint32_t n10[] = { 0x00000000, 0x5ae5e79f, 0xe1bd8ae0 };
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected10[] = { 0x00000000, 0x18194468, 0x66657005 };

	mod_neg(result, n10, p10, 3);

	expect(tester, big_uint_equals(expected10, result, 3));

	// Test 11
	const uint32_t n11[] = { 0x00000000, 0x00000000, 0x32865929, 0x1575c0a9 };
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected11[] = { 0x00000000, 0x00000000, 0x4078d2df, 0x32ad3a3c };

	mod_neg(result, n11, p11, 4);

	expect(tester, big_uint_equals(expected11, result, 4));

	log_tests(tester);
}

int main() {
	// Calling all tests:
	test_mod_big_uint();
	test_mod_add();
	test_mod_sub();
	test_mod_init();
	test_mod_mult();
	test_mod_exp();
	test_mod_inv();
	test_mod_div();
	test_mod_neg();

	return 1;
}
