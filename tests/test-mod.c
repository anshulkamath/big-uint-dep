#include <stdlib.h>
#include "testing-logger.h"
#include "mod.h"

void test_mod_big_uint() {
	testing_logger_t *tester = create_tester();
	uint32_t result[5] = { 0 };

	// Test 1
	const uint32_t n1[] = { 0xad890c22 };
	const uint32_t p1[] = { 0x0000000d };
	const uint32_t expected1[] = { 0x0000000b };

	mod_big_uint(result, n1, p1, 1);

	expect(tester, big_uint_equals(expected1, result, 1));

	// Test 2
	const uint32_t n2[] = { 0x400aae41, 0x973d88d8 };
	const uint32_t p2[] = { 0x00000000, 0x0000000d };
	const uint32_t expected2[] = { 0x00000000, 0x00000009 };

	mod_big_uint(result, n2, p2, 2);

	expect(tester, big_uint_equals(expected2, result, 2));

	// Test 3
	const uint32_t n3[] = { 0xe2d2f4db, 0xec0b99df, 0xa6f5cb80 };
	const uint32_t p3[] = { 0x00000000, 0x00000000, 0x0000000d };
	const uint32_t expected3[] = { 0x00000000, 0x00000000, 0x00000006 };

	mod_big_uint(result, n3, p3, 3);

	expect(tester, big_uint_equals(expected3, result, 3));

	// Test 4
	const uint32_t n4[] = { 0x4b834fce, 0x21113da9 };
	const uint32_t p4[] = { 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected4[] = { 0x0e885e92, 0xd4d2898a };

	mod_big_uint(result, n4, p4, 2);

	expect(tester, big_uint_equals(expected4, result, 2));

	// Test 5
	const uint32_t n5[] = { 0x1fe27507, 0x4b2d3757, 0xaab439a0 };
	const uint32_t p5[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected5[] = { 0x00000000, 0x008b29e1, 0x4dcb9ef5 };

	mod_big_uint(result, n5, p5, 3);

	expect(tester, big_uint_equals(expected5, result, 3));

	// Test 6
	const uint32_t n6[] = { 0x51671c51, 0xeca82fca, 0xc664fb8c };
	const uint32_t p6[] = { 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected6[] = { 0x00000000, 0x11426b17, 0xef0c956e };

	mod_big_uint(result, n6, p6, 3);

	expect(tester, big_uint_equals(expected6, result, 3));

	// Test 7
	const uint32_t n7[] = { 0xd925a2a9, 0xeb9698be, 0x1df39055, 0x33b7d72a };
	const uint32_t p7[] = { 0x00000000, 0x00000000, 0x3cfaf13b, 0x4c3eb41f };
	const uint32_t expected7[] = { 0x00000000, 0x00000000, 0x03607ddb, 0x0141c982 };

	mod_big_uint(result, n7, p7, 4);

	expect(tester, big_uint_equals(expected7, result, 4));

	// Test 8
	const uint32_t n8[] = { 0x5320ff88, 0x9d12578c };
	const uint32_t p8[] = { 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected8[] = { 0x5320ff88, 0x9d12578c };

	mod_big_uint(result, n8, p8, 2);

	expect(tester, big_uint_equals(expected8, result, 2));

	// Test 9
	const uint32_t n9[] = { 0x8853aef1, 0x5944b1fb, 0x81aa2685 };
	const uint32_t p9[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected9[] = { 0x00000000, 0x4bdc6646, 0x78d5110f };

	mod_big_uint(result, n9, p9, 3);

	expect(tester, big_uint_equals(expected9, result, 3));

	// Test 10
	const uint32_t n10[] = { 0x1db64884, 0x0d478d60, 0x448ff29e };
	const uint32_t p10[] = { 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected10[] = { 0x00000000, 0x67053468, 0x7d62742a };

	mod_big_uint(result, n10, p10, 3);

	expect(tester, big_uint_equals(expected10, result, 3));

	// Test 11
	const uint32_t n11[] = { 0xd70d82b8, 0x616e9bf7, 0xc50f822a, 0x79aeb507 };
	const uint32_t p11[] = { 0x00000000, 0x00000000, 0x72ff2c08, 0x4822fae5 };
	const uint32_t expected11[] = { 0x00000000, 0x00000000, 0x18695bd7, 0x11482afd };

	mod_big_uint(result, n11, p11, 4);

	expect(tester, big_uint_equals(expected11, result, 4));

	log_tests(tester);
}

int main() {
    test_mod_big_uint();
    
    return 0;
}
