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

int main() {
	// Calling all tests:
	test_mod_big_uint();
	test_mod_add();
	test_mod_sub();

	return 1;
}
