#include "big-uint.h"

#include <stdio.h>
#include <string.h>
#include "testing.h"

void test_big_uint_equals() {
    // Define variables to be tested with
    testing_logger_t *tester = init_tester();

    const uint32_t a1[] = { 0x10 };
    const uint32_t b1[] = { 0x10 };

    expect(tester, big_uint_equals(a1, b1, 1));

    const uint32_t a2[] = { 0x10, 0x20, 0xff03abcd };
    const uint32_t b2[] = { 0x10, 0x20, 0xff03abcd };

    expect(tester, big_uint_equals(a2, b2, 1));

    const uint32_t a3[] = { 0x10, 0x20, 0xff03abce };
    const uint32_t b3[] = { 0x10, 0x20, 0xff03abcd };

    expect(tester, !big_uint_equals(a3, b3, 3));

    log_tests(tester);
}

void test_big_uint_cmp() {
    // Define variables to be tested with
    testing_logger_t *tester = init_tester();

    const uint32_t a1[] = { 0x00000010 };
    const uint32_t b1[] = { 0x00000010 };

    expect(tester, big_uint_cmp(a1, b1, 1) == 0);

    const uint32_t a2[] = { 0x00000011, 0x00000020, 0xff03abcd };
    const uint32_t b2[] = { 0x00000010, 0x00000020, 0xff03abcd };

    expect(tester, big_uint_cmp(a2, b2, 3) == 1);

    const uint32_t a3[] = { 0x00000000, 0x00000000, 0x00000000 };
    const uint32_t b3[] = { 0x00000010, 0x00000020, 0xff03abce };

    expect(tester, big_uint_cmp(a3, b3, 3) == -1);

    const uint32_t a4[] = { 0x0, 0x2 };
    const uint32_t b4[] = { 0x1, 0x0 };

    expect(tester, big_uint_cmp(a4, b4, 2) == -1);

    log_tests(tester);
}

void test_big_uint_sprint() {
    // Define variables to be tested with
    testing_logger_t *tester = init_tester();

    // 0 digit number
    const uint32_t *a1;
    char str1[1];
    big_uint_sprint(str1, a1, 0);

    expect(tester, !strcmp(str1, ""));

    // 1 digit number
    const uint32_t a2[] = { 0x12345678 };
    char str2[9];
    big_uint_sprint(str2, a2, 1);

    expect(tester, !strcmp(str2, "12345678"));

    // 2 digit number
    const uint32_t a3[] = { 0x12345678, 0x87654321 };
    char str3[17];
    big_uint_sprint(str3, a3, 2);

    expect(tester, !strcmp(str3, "12345678 87654321"));

    // all 0s
    const uint32_t a4[] = { 0x00000000, 0x00000000 };
    char str4[17];
    big_uint_sprint(str4, a4, 2);

    expect(tester, !strcmp(str4, "00000000 00000000"));

    log_tests(tester);
}

void test_big_uint_shl() {
    // Define variables to be tested with
    testing_logger_t *tester = init_tester();
    uint32_t result[5] = { 0 };

    // no shift
    const uint32_t a1[] = { 0x00000001 };
    const uint32_t expected1[] = { 0x00000001 };
    big_uint_shl(result, a1, 1, 0);

    expect(tester, big_uint_equals(result, expected1, 1));

    // shift over length
    const uint32_t a2[] = { 0x00000001 };
    const uint32_t expected2[] = { 0x00000000 };
    big_uint_shl(result, a2, 1, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    // shift by 1
    const uint32_t a3[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected3[] = { 0xeeeeeeee, 0x00000000 };
    big_uint_shl(result, a3, 2, 1);

    expect(tester, big_uint_equals(result, expected3, 2));

    // shift by 1
    const uint32_t a4[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected4[] = { 0x00000000, 0x00000000 };
    big_uint_shl(result, a4, 2, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

    log_tests(tester);
}

void test_big_uint_shr() {
    // Define variables to be tested with
    testing_logger_t *tester = init_tester();
    uint32_t result[5] = { 0 };

    // no shift
    const uint32_t a1[] = { 0x00000001 };
    const uint32_t expected1[] = { 0x00000001 };
    big_uint_shr(result, a1, 1, 0);

    expect(tester, big_uint_equals(result, expected1, 1));

    // shift over length
    const uint32_t a2[] = { 0x00000001 };
    const uint32_t expected2[] = { 0x00000000 };
    big_uint_shr(result, a2, 1, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    // shift by 1
    const uint32_t a3[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected3[] = { 0x00000000, 0xffffffff };
    big_uint_shr(result, a3, 2, 1);

    expect(tester, big_uint_equals(result, expected3, 2));

    // shift by 1
    const uint32_t a4[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected4[] = { 0x00000000, 0x00000000 };
    big_uint_shr(result, a4, 2, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

    log_tests(tester);
}

void test_big_uint_add() {
    // Define variables to be tested with
    testing_logger_t *tester = init_tester();
    uint32_t result[5] = { 0 };

    // Single digit test (no carry, no overflow)
    const uint32_t a1[] = { 0x00000010 };
    const uint32_t b1[] = { 0x00000020 };
    const uint32_t expected1[] = { 0x00000030 };
    big_uint_add(result, a1, b1, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    // Multiple digit test (no carry, no overflow)
    const uint32_t a2[] = { 0x00000025, 0x00000012 };
    const uint32_t b2[] = { 0x00000030, 0x00000015 };
    const uint32_t expected2[] = { 0x00000055, 0x00000027 };
    big_uint_add(result, a2, b2, 2);

    expect(tester, big_uint_equals(result, expected2, 2));

    // Multiple digit test (no carry, no overflow)
    const uint32_t a3[] = { 0x00000025, 0x000000ff };
    const uint32_t b3[] = { 0x00000030, 0x00000015 };
    const uint32_t expected3[] = { 0x00000055, 0x00000114 };
    big_uint_add(result, a3, b3, 2);

    expect(tester, big_uint_equals(result, expected3, 2));

    // Multiple digit test (carry, no overflow)
    const uint32_t a4[] = { 0x00000025, 0xff000000 };
    const uint32_t b4[] = { 0x00000030, 0x15000000 };
    const uint32_t expected4[] = { 0x00000056, 0x14000000 };
    big_uint_add(result, a4, b4, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

     // Multiple digit test (carry, overflow)
    const uint32_t a5[] = { 0x00000000, 0xffff0000, 0xffffffff };
    const uint32_t b5[] = { 0x00000000, 0x0000ffff, 0x00000001 };
    const uint32_t expected5[] = { 0x1, 0x00000000, 0x00000000 };
    big_uint_add(result, a5, b5, 3);

    expect(tester, big_uint_equals(result, expected5, 3));

    // Multiple digit test (no carry, overflow)
    const uint32_t a6[] = { 0xf0000000, 0x00000000 };
    const uint32_t b6[] = { 0x10000000, 0x00000000 };
    const uint32_t expected6[] = { 0x00000000, 0x00000000 };
    big_uint_add(result, a6, b6, 2);

    expect(tester, big_uint_equals(result, expected6, 2));

    // Multiple digit test (carry, overflow)
    const uint32_t a7[] = { 0xf0000000, 0xf0000000 };
    const uint32_t b7[] = { 0x10000000, 0xf0000000 };
    const uint32_t expected7[] = { 0x00000001, 0xe0000000 };
    big_uint_add(result, a7, b7, 2);

    expect(tester, big_uint_equals(result, expected7, 2));

    const uint32_t a8[] = { 0x000031bc, 0x9abbed10 };
    const uint32_t b8[] = { 0x00000000, 0x00000000 };
    const uint32_t expected8[] = { 0x000031bc, 0x9abbed10 };
    big_uint_add(result, a8, b8, 2);

    expect(tester, big_uint_equals(result, expected8, 2));

    // Misc.
    const uint32_t a9[] = { 0x00000000, 0x00000000, 0x000031bc, 0x9abbed10 };
    const uint32_t b9[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
    const uint32_t expected9[] = { 0x00000000, 0x00000000, 0x000031bc, 0x9abbed10 };
    big_uint_add(result, a9, b9, 4);

    expect(tester, big_uint_equals(result, expected9, 4));

    // Doubling variable by adding itself
    const uint32_t a10[] = { 0x000031bc, 0x9abbed10 };
    const uint32_t expected10[] = { 0x6379, 0x3577da20 };
    big_uint_add(result, a10, a10, 2);

    expect(tester, big_uint_equals(result, expected10, 2));
    
    log_tests(tester);
}

void test_big_uint_sub() {
    // Define variables to be tested with
    testing_logger_t *tester = init_tester();
    uint32_t result[5] = { 0 };

    // Single digit test (no carry, no underflow)
    const uint32_t a1[] = { 0x00000020 };
    const uint32_t b1[] = { 0x00000005 };
    const uint32_t expected1[] = { 0x0000001b };
    big_uint_sub(result, a1, b1, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    // Single digit test (no carry, underflow)
    const uint32_t a2[] = { 0x00000012 };
    const uint32_t b2[] = { 0x00000015 };
    const uint32_t expected2[] = { 0xfffffffd };
    big_uint_sub(result, a2, b2, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    // Multiple digit test (no carry, no underflow)
    const uint32_t a3[] = { 0x00000030, 0x00000025 };
    const uint32_t b3[] = { 0x00000025, 0x00000015 };
    const uint32_t expected3[] = { 0x0000000b, 0x00000010 };
    big_uint_sub(result, a3, b3, 2);

    expect(tester, big_uint_equals(result, expected3, 2));

    // Multiple digit test (carry, no underflow)
    const uint32_t a4[] = { 0x30000006, 0x10000000 };
    const uint32_t b4[] = { 0x20000005, 0x50000000 };
    const uint32_t expected4[] = { 0x10000000, 0xc0000000 };
    big_uint_sub(result, a4, b4, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

     // Multiple digit test (no carry, underflow)
    const uint32_t a5[] = { 0x00000000, 0x00000000 };
    const uint32_t b5[] = { 0x00000000, 0x00000001 };
    const uint32_t expected5[] = { 0xffffffff, 0xffffffff };
    big_uint_sub(result, a5, b5, 2);

    expect(tester, big_uint_equals(result, expected5, 2));

    // Multiple digit test (no carry, underflow)
    const uint32_t a6[] = { 0x00000001, 0x00000000 };
    const uint32_t b6[] = { 0x00000050, 0x00000000 };
    const uint32_t expected6[] = { 0xffffffb1, 0x000000000 };
    big_uint_sub(result, a6, b6, 2);

    expect(tester, big_uint_equals(result, expected6, 2));

    // Multiple digit test (carry, underflow)
    const uint32_t a7[] = { 0x0000001, 0x10000000 };
    const uint32_t b7[] = { 0x00000000, 0xf0000000 };
    const uint32_t expected7[] = { 0x00000000, 0x20000000 };
    big_uint_sub(result, a7, b7, 2);

    expect(tester, big_uint_equals(result, expected7, 2));

    log_tests(tester);
}

void test_big_uint_mult() {
    // Define variables to be tested with
    testing_logger_t *tester = init_tester();
    uint32_t result[5];

    // Single digit test (no carry, no overflow)
    const uint32_t a1[] = { 0x00000020 };
    const uint32_t b1[] = { 0x00000005 };
    const uint32_t expected1[] = { 0x000000a0 };
    big_uint_mult(result, a1, b1, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    // Single digit test (no carry, no overflow)
    const uint32_t a2[] = { 0x00000012 };
    const uint32_t b2[] = { 0x00000015 };
    const uint32_t expected2[] = { 0x0000017a };
    big_uint_mult(result, a2, b2, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    // Multiple digit test (no carry, no overflow)
    const uint32_t a3[] = { 0x00000030, 0x00000025 };
    const uint32_t b3[] = { 0x00000000, 0x00000015 };
    const uint32_t expected3[] = { 0x000003f0, 0x00000309 };
    big_uint_mult(result, a3, b3, 2);

    expect(tester, big_uint_equals(result, expected3, 2));

    // Multiple digit test (carry, no overflow)
    const uint32_t a4[] = { 0x00000000, 0x10000000 };
    const uint32_t b4[] = { 0x00000000, 0x00000050 };
    const uint32_t expected4[] = { 0x00000005, 0x00000000 };
    big_uint_mult(result, a4, b4, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

     // Multiple digit test (no carry, overflow)
    const uint32_t a5[] = { 0x00020000, 0x00000000 };
    const uint32_t b5[] = { 0x00000000, 0x00021112 };
    const uint32_t expected5[] = { 0x22240000, 0x00000000 };
    big_uint_mult(result, a5, b5, 2);

    expect(tester, big_uint_equals(result, expected5, 2));

    // Multiple digit test (no carry, overflow)
    const uint32_t a6[] = { 0x00000025, 0x00000000 };
    const uint32_t b6[] = { 0x00000013, 0x11000000 };
    const uint32_t expected6[] = { 0x75000000, 0x00000000 };
    big_uint_mult(result, a6, b6, 2);

    expect(tester, big_uint_equals(result, expected6, 2));

    // Multiple digit test (carry, overflow)
    const uint32_t a7[] = { 0x00000000, 0x10000000 };
    const uint32_t b7[] = { 0x00001100, 0xf0025000 };
    const uint32_t expected7[] = { 0x0f002500, 0x00000000 };
    big_uint_mult(result, a7, b7, 2);

    expect(tester, big_uint_equals(result, expected7, 2));

    // Misc. tests
    const uint32_t a8[] = { 0x00000000, 0x31f596dc };
    const uint32_t b8[] = { 0x00000000, 0x0000fedc };
    const uint32_t expected8[] = { 0x000031bc, 0x9abbed10 };
    big_uint_mult(result, a8, b8, 2);

    expect(tester, big_uint_equals(result, expected8, 2));

    log_tests(tester);
}

void test_big_uint_div() {
    testing_logger_t *tester = init_tester();
    uint32_t quotients[5] = { 0 };
    uint32_t remainders[5] = { 0 };

    // Divide by 0
    const uint32_t a1[] = { 0x00000001 };
    const uint32_t b1[] = { 0x00000000 };
    const uint32_t expected_quotient1[] = { 0 };
    const uint32_t expected_remainder1[] = { 0 };
    big_uint_div(quotients, remainders, a1, b1, 1);

    expect(tester, big_uint_equals(quotients, expected_quotient1, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder1, 1));

    // 1 digit division (no truncation)
    const uint32_t a2[] = { 0x00000010 };
    const uint32_t b2[] = { 0x00000002 };
    const uint32_t expected_quotient2[] = { 0x00000008 };
    const uint32_t expected_remainder2[] = { 0x00000000 };
    big_uint_div(quotients, remainders, a2, b2, 1);

    expect(tester, big_uint_equals(quotients, expected_quotient2, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder2, 1));

    // padded 1 digit division (no truncation)
    const uint32_t a3[] = { 0x0, 0x00000010 };
    const uint32_t b3[] = { 0x0, 0x00000002 };
    const uint32_t expected_quotient3[] = { 0x00000000, 0x00000008 };
    const uint32_t expected_remainder3[] = { 0x00000000, 0x00000000 };
    big_uint_div(quotients, remainders, a3, b3, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient3, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder3, 1));

    // 1 digit division (truncation)
    const uint32_t a4[] = { 0x00000009 };
    const uint32_t b4[] = { 0x00000002 };
    const uint32_t expected_quotient4[] = { 0x00000004 };
    const uint32_t expected_remainder4[] = { 0x00000001 };
    big_uint_div(quotients, remainders, a4, b4, 1);

    expect(tester, big_uint_equals(quotients, expected_quotient4, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder4, 1));

    // 2 digit division (no truncation)
    const uint32_t a5[] = { 0x00000009, 0x00000000 };
    const uint32_t b5[] = { 0x00000000, 0x00000002 };
    const uint32_t expected_quotient5[] = { 0x00000004, 0x80000000 };
    const uint32_t expected_remainder5[] = { 0x00000000, 0x00000000 };
    big_uint_div(quotients, remainders, a5, b5, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient5, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder5, 1));

    // 2 digit division (no truncation)
    const uint32_t a6[] = { 0x00000009, 0x00000000 };
    const uint32_t b6[] = { 0x00000000, 0x00000020 };
    const uint32_t expected_quotient6[] = { 0x00000000, 0x48000000 };
    const uint32_t expected_remainder6[] = { 0x00000000, 0x00000000 };
    big_uint_div(quotients, remainders, a6, b6, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient6, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder6, 1));

    // large number over itself + 1
    const uint32_t a7[] = { 0xffffffff, 0xfffffffe };
    const uint32_t b7[] = { 0xffffffff, 0xffffffff };
    const uint32_t expected_quotient7[] = { 0x00000000, 0x00000000 };
    const uint32_t expected_remainder7[] = { 0xffffffff, 0xfffffffe };
    big_uint_div(quotients, remainders, a7, b7, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient7, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder7, 1));

    // large number over itself - 1
    const uint32_t a8[] = { 0xffffffff, 0xffffffff };
    const uint32_t b8[] = { 0xffffffff, 0xfffffffe };
    const uint32_t expected_quotient8[] = { 0x00000000, 0x00000001 };
    const uint32_t expected_remainder8[] = { 0x00000000, 0x00000001 };
    big_uint_div(quotients, remainders, a8, b8, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient8, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder8, 1));

    // 3 digit number divided by 1 digit number
    const uint32_t a9[] = { 0x12345678, 0x9abcdeff, 0xffffffff };
    const uint32_t b9[] = { 0x00000000, 0x0000000, 0x0000fedc };
    const uint32_t expected_quotient9[] = { 0x00001249, 0x31f596dc, 0xf30531ec };
    const uint32_t expected_remainder9[] = { 0x00000000, 0x0000000, 0x0000f12f };
    big_uint_div(quotients, remainders, a9, b9, 3);

    expect(tester, big_uint_equals(quotients, expected_quotient9, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder9, 1));

    // random number
    const uint32_t a10[] = { 0x00efa9af, 0x3619a918 };
    const uint32_t b10[] = { 0x00000ee1, 0xa8138dfe };
    const uint32_t expected_quotient10[] = { 0x00000000, 0x0000101a };
    const uint32_t expected_remainder10[] = { 0x00000c42, 0xeb3d5d4c };
    big_uint_div(quotients, remainders, a10, b10, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient10, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder10, 1));

    // forced 1 by 2
    const uint32_t a11[] = { 0x000100000, 0x00000000 };
    const uint32_t b11[] = { 0x000000000, 0xf0000000 };
    const uint32_t expected_quotient11[] = { 0x000000000, 0x00111111 };
    const uint32_t expected_remainder11[] = { 0x00000000, 0x10000000 };
    big_uint_div(quotients, remainders, a11, b11, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient11, 1));
    expect(tester, big_uint_equals(remainders, expected_remainder11, 1));

    log_tests(tester);
}

int main() {
    test_big_uint_equals();
    test_big_uint_cmp();
    test_big_uint_sprint();
    test_big_uint_shl();
    test_big_uint_shr();
    test_big_uint_add();
    test_big_uint_sub();
    test_big_uint_mult();
    test_big_uint_div();

    return 0;
}
