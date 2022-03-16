#include "big-uint.h"

#include <stdio.h>
#include <string.h>
#include "testing-logger.h"

void test_big_uint_equals() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

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
    testing_logger_t *tester = create_tester();

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

void test_big_uint_cpy() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    uint32_t result[5];

    uint32_t a1[] = { 0x12345678 };
    big_uint_cpy(result, a1, 1);

    expect(tester, big_uint_equals(a1, result, 1));

    uint32_t a2[] = { 0x12345678, 0x87654321 };
    big_uint_cpy(result, a2, 2);

    expect(tester, big_uint_equals(a2, result, 2));

    log_tests(tester);
}

void test_big_uint_load() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    uint32_t result[5];

    uint32_t a1[] = { 0x00000000 };
    big_uint_load(result, 0, 1);

    expect(tester, big_uint_equals(a1, result, 1));

    uint32_t a2[] = { 0x00000000, 0x00000000 };
    big_uint_load(result, 0, 2);

    expect(tester, big_uint_equals(a2, result, 2));

    uint32_t a3[] = { 0x00000000, 0x00000005 };
    big_uint_load(result, 5, 2);

    expect(tester, big_uint_equals(a3, result, 2));

    uint32_t a4[] = { 0x00000000, 0x00000000, 0x12345678 };
    big_uint_load(result, 0x12345678, 3);

    expect(tester, big_uint_equals(a4, result, 3));

    log_tests(tester);
}

void test_big_uint_sprint() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    // 0 digit number
    const uint32_t *a1;
    char str1[1] = { 0 };
    big_uint_sprint(str1, a1, 0);

    expect(tester, !strcmp(str1, ""));

    // 1 digit number
    const uint32_t a2[] = { 0x12345678 };
    char str2[9] = { 0 };
    big_uint_sprint(str2, a2, 1);

    expect(tester, !strcmp(str2, "12345678"));

    // 2 digit number
    const uint32_t a3[] = { 0x12345678, 0x87654321 };
    char str3[18] = { 0 };
    big_uint_sprint(str3, a3, 2);

    expect(tester, !strcmp(str3, "12345678 87654321"));

    // all 0s
    const uint32_t a4[] = { 0x00000000, 0x00000000 };
    char str4[18] = { 0 };
    big_uint_sprint(str4, a4, 2);

    expect(tester, !strcmp(str4, "00000000 00000000"));

    log_tests(tester);
}

void test_big_uint_max() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    uint32_t a1[] = { 0x00000000 };
    uint32_t b1[] = { 0x00000000 };

    expect(tester, a1 == big_uint_max(a1, 1, b1, 1));

    uint32_t a2[] = { 0x12345678 };
    uint32_t b2[] = { 0xffffffff };

    expect(tester, b2 == big_uint_max(a2, 1, b2, 1));

    uint32_t a3[] = { 0xffffffff };
    uint32_t b3[] = { 0xfffffffe };

    expect(tester, a3 == big_uint_max(a3, 1, b3, 1));

    uint32_t a4[] = { 0x00000000, 0x12345678 };
    uint32_t b4[] = { 0x00000000, 0xffffffff };

    expect(tester, b4 == big_uint_max(a4, 2, b4, 2));

    uint32_t a5[] = { 0x00000000, 0x12345678 };
    uint32_t b5[] = { 0xffffffff };

    expect(tester, b5 == big_uint_max(a5, 1, b5, 2));

    uint32_t a6[] = { 0xffffffff, 0xfffffffe };
    uint32_t b6[] = { 0xffffffff, 0xffffffff };

    expect(tester, b6 == big_uint_max(a6, 2, b6, 2));

    uint32_t a7[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffe };
    uint32_t b7[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff };

    expect(tester, b7 == big_uint_max(a7, 4, b7, 4));

    uint32_t a8[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffe };
    uint32_t b8[] = { 0x00000000, 0x00000000, 0x00000000, 0xffffffff };

    expect(tester, a8 == big_uint_max(a8, 4, b8, 4));

    uint32_t a9[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000002 };
    uint32_t b9[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000001 };

    expect(tester, a9 == big_uint_max(a9, 4, b9, 4));

    log_tests(tester);
}

void test_big_uint_min() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();

    uint32_t a1[] = { 0x00000000 };
    uint32_t b1[] = { 0x00000000 };

    expect(tester, a1 == big_uint_max(a1, 1, b1, 1));

    uint32_t a2[] = { 0x12345678 };
    uint32_t b2[] = { 0xffffffff };

    expect(tester, a2 == big_uint_min(a2, 1, b2, 1));

    uint32_t a3[] = { 0xffffffff };
    uint32_t b3[] = { 0xfffffffe };

    expect(tester, b3 == big_uint_min(a3, 1, b3, 1));

    uint32_t a4[] = { 0x00000000, 0x12345678 };
    uint32_t b4[] = { 0x00000000, 0xffffffff };

    expect(tester, a4 == big_uint_min(a4, 2, b4, 2));

    uint32_t a5[] = { 0x00000000, 0x12345678 };
    uint32_t b5[] = { 0xffffffff };

    expect(tester, a5 == big_uint_min(a5, 1, b5, 2));

    uint32_t a6[] = { 0xffffffff, 0xfffffffe };
    uint32_t b6[] = { 0xffffffff, 0xffffffff };

    expect(tester, a6 == big_uint_min(a6, 2, b6, 2));

    uint32_t a7[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffe };
    uint32_t b7[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff };

    expect(tester, a7 == big_uint_min(a7, 4, b7, 4));

    uint32_t a8[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffe };
    uint32_t b8[] = { 0x00000000, 0x00000000, 0x00000000, 0xffffffff };

    expect(tester, b8 == big_uint_min(a8, 4, b8, 4));

    uint32_t a9[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000002 };
    uint32_t b9[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000001 };

    expect(tester, b9 == big_uint_min(a9, 4, b9, 4));

    log_tests(tester);
}

void test_big_uint_shl() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    uint32_t result[5] = { 0 };

    // no shift
    const uint32_t a1[] = { 0x00000001 };
    const uint32_t expected1[] = { 0x00000001 };
    big_uint_shl(result, a1, 0, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    // shift over length
    const uint32_t a2[] = { 0x00000001 };
    const uint32_t expected2[] = { 0x00000000 };
    big_uint_shl(result, a2, 1, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    // shift by 1
    const uint32_t a3[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected3[] = { 0xeeeeeeee, 0x00000000 };
    big_uint_shl(result, a3, 1, 2);

    expect(tester, big_uint_equals(result, expected3, 2));

    // shift by 1
    const uint32_t a4[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected4[] = { 0x00000000, 0x00000000 };
    big_uint_shl(result, a4, 2, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

    // random shift
    const uint32_t a5[] = { 0x00abcdef, 0x12345678 };
    const uint32_t expected5[] = { 0x12345678, 0x00000000 };
    big_uint_shl(result, a5, 1, 2);

    expect(tester, big_uint_equals(result, expected5, 2));

    // operator assignment
    uint32_t a6[] = { 0x00abcdef, 0x12345678 };
    const uint32_t expected6[] = { 0x12345678, 0x00000000 };
    big_uint_shl(a6, a6, 1, 2);

    expect(tester, big_uint_equals(a6, expected6, 2));

    // no shift
    const uint32_t a7[] = { 0xffffffff, 0xfffffffe };
    const uint32_t expected7[] = { 0xffffffff, 0xfffffffe};
    big_uint_shl(result, a7, 0, 2);

    expect(tester, big_uint_equals(result, expected7, 2));

    log_tests(tester);
}

void test_big_uint_shr() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    uint32_t result[5] = { 0 };

    // no shift
    const uint32_t a1[] = { 0x00000001 };
    const uint32_t expected1[] = { 0x00000001 };
    big_uint_shr(result, a1, 0, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    // shift over length
    const uint32_t a2[] = { 0x00000001 };
    const uint32_t expected2[] = { 0x00000000 };
    big_uint_shr(result, a2, 1, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    // shift by 1
    const uint32_t a3[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected3[] = { 0x00000000, 0xffffffff };
    big_uint_shr(result, a3, 1, 2);

    expect(tester, big_uint_equals(result, expected3, 2));

    // shift by 1
    const uint32_t a4[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected4[] = { 0x00000000, 0x00000000 };
    big_uint_shr(result, a4, 2, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

    // operator assignment
    uint32_t a5[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected5[] = { 0x00000000, 0xffffffff };
    big_uint_shr(a5, a5, 1, 2);

    expect(tester, big_uint_equals(a5, expected5, 2));

    // no shift
    const uint32_t a6[] = { 0xffffffff, 0xfffffffe };
    const uint32_t expected6[] = { 0xffffffff, 0xfffffffe};
    big_uint_shr(result, a6, 0, 2);

    expect(tester, big_uint_equals(result, expected6, 2));

    log_tests(tester);
}

void test_big_uint_shl2() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    uint32_t result[5] = { 0 };

    // no shift
    const uint32_t a1[] = { 0x00000001 };
    const uint32_t expected1[] = { 0x00000001 };
    big_uint_shl2(result, a1, 0, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    // shift over length
    const uint32_t a2[] = { 0x00000001 };
    const uint32_t expected2[] = { 0x00000000 };
    big_uint_shl2(result, a2, 32, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    // shift by 1
    const uint32_t a3[] = { 0x00000001 };
    const uint32_t expected3[] = { 0x00000002 };
    big_uint_shl2(result, a3, 1, 1);

    expect(tester, big_uint_equals(result, expected3, 1));

    // shift by 1 carry
    uint32_t a4[] = { 0x00000001, 0xffffffff };
    const uint32_t expected4[] = { 0x00000003, 0xfffffffe };
    big_uint_shl2(result, a4, 1, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

    // shift by 1 overflow
    const uint32_t a5[] = { 0xffffffff, 0xffffffff };
    const uint32_t expected5[] = { 0xffffffff, 0xfffffffe };
    big_uint_shl2(result, a5, 1, 2);

    expect(tester, big_uint_equals(result, expected5, 2));

    // random shift
    const uint32_t a6[] = { 0x00abcdef, 0x12345678 };
    const uint32_t expected6[] = { 0x8d159e00, 0x00000000 };
    big_uint_shl2(result, a6, 38, 2);

    expect(tester, big_uint_equals(result, expected6, 2));

    // operator assignment
    uint32_t a7[] = { 0x00abcdef, 0x12345678 };
    const uint32_t expected7[] = { 0x8d159e00, 0x00000000 };
    big_uint_shl2(a7, a7, 38, 2);

    expect(tester, big_uint_equals(a7, expected7, 2));

    // no shift
    const uint32_t a8[] = { 0xffffffff, 0xfffffffe };
    const uint32_t expected8[] = { 0xffffffff, 0xfffffffe};
    big_uint_shl2(result, a8, 0, 2);

    expect(tester, big_uint_equals(result, expected8, 2));

    const uint32_t a9[] = { 0x41763a5f, 0x991b4b60, 0x84285b8e };
    const uint32_t expected9[] = { 0x991b4b60, 0x84285b8e, 0x00000000 };
    big_uint_shl2(result, a9, 32, 3);

    expect(tester, big_uint_equals(result, expected9, 3));

    log_tests(tester);
}

void test_big_uint_shr2() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    uint32_t result[5] = { 0 };

    // no shift
    const uint32_t a1[] = { 0x00000001 };
    const uint32_t expected1[] = { 0x00000001 };
    big_uint_shr2(result, a1, 0, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    // shift over length
    const uint32_t a2[] = { 0x00000001 };
    const uint32_t expected2[] = { 0x00000000 };
    big_uint_shr2(result, a2, 1, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    // shift by 1 carry
    const uint32_t a3[] = { 0xffffffff, 0xeeeeeeee };
    const uint32_t expected3[] = { 0x7fffffff, 0xf7777777 };
    big_uint_shr2(result, a3, 1, 2);

    expect(tester, big_uint_equals(result, expected3, 2));

    // random shift
    const uint32_t a4[] = { 0x00abcdef, 0x12345678 };
    const uint32_t expected4[] = { 0x00000000, 0x00002af37 };
    big_uint_shr2(result, a4, 38, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

    // operator assignment
    uint32_t a5[] = { 0x00abcdef, 0x12345678 };
    const uint32_t expected5[] = { 0x00000000, 0x00002af37 };
    big_uint_shr2(a5, a5, 38, 2);

    expect(tester, big_uint_equals(a5, expected5, 2));

    // no shift
    const uint32_t a6[] = { 0xffffffff, 0xfffffffe };
    const uint32_t expected6[] = { 0xffffffff, 0xfffffffe};
    big_uint_shr2(result, a6, 0, 2);

    expect(tester, big_uint_equals(result, expected6, 2));

    const uint32_t a7[] = { 0x41763a5f, 0x991b4b60, 0x84285b8e };
    const uint32_t expected7[] = { 0x00000000, 0x41763a5f, 0x991b4b60 };
    big_uint_shr2(result, a7, 32, 3);

    expect(tester, big_uint_equals(result, expected7, 3));

    log_tests(tester);
}

void test_big_uint_or() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    uint32_t result[5] = { 0 };

    // Single digit test (no carry, no underflow)
    const uint32_t a1[] = { 0x11110000 };
    const uint32_t b1[] = { 0x00002222 };
    const uint32_t expected1[] = { 0x11112222 };
    big_uint_or(result, a1, b1, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    const uint32_t a2[] = { 0xffffffff };
    const uint32_t b2[] = { 0x00000000 };
    const uint32_t expected2[] = { 0xffffffff };
    big_uint_or(result, a2, b2, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    const uint32_t a3[] = { 0x00000000 };
    const uint32_t b3[] = { 0xffffffff };
    const uint32_t expected3[] = { 0xffffffff };
    big_uint_or(result, a3, b3, 1);

    expect(tester, big_uint_equals(result, expected3, 1));

    const uint32_t a4[] = { 0xffffffff, 0x00000000 };
    const uint32_t b4[] = { 0x00000000, 0xffffffff };
    const uint32_t expected4[] = { 0xffffffff, 0xffffffff };
    big_uint_or(result, a4, b4, 1);

    expect(tester, big_uint_equals(result, expected4, 1));

    const uint32_t a5[] = { 0xffff0000, 0xffff0000 };
    const uint32_t b5[] = { 0x0000ffff, 0x0000ffff };
    const uint32_t expected5[] = { 0xffffffff, 0xffffffff };
    big_uint_or(result, a5, b5, 1);

    expect(tester, big_uint_equals(result, expected5, 1));

    const uint32_t a6[] = { 0x12345678, 0x12345678 };
    const uint32_t b6[] = { 0x12345678, 0x12345678 };
    const uint32_t expected6[] = { 0x12345678, 0x12345678 };
    big_uint_or(result, a6, b6, 1);

    expect(tester, big_uint_equals(result, expected6, 1));

    const uint32_t a7[] = { 0x87654321, 0x12345678 };
    big_uint_or(result, a7, a7, 1);

    expect(tester, big_uint_equals(result, a7, 1));

    // or-equals
    uint32_t a8[] = { 0xffff0000, 0xffff0000 };
    const uint32_t b8[] = { 0x0000ffff, 0x0000ffff };
    const uint32_t expected8[] = { 0xffffffff, 0xffffffff };
    big_uint_or(a8, a8, b8, 1);

    expect(tester, big_uint_equals(a8, expected8, 1));

    // or-equals
    uint32_t a9[] = {0x00000000, 0x00000000 };
    const uint32_t b9[] = { 0x00000000, 0x00000001 };
    const uint32_t expected9[] = { 0x00000000, 0x000000001 };
    big_uint_or(a9, a9, b9, 1);

    expect(tester, big_uint_equals(a9, expected9, 1));

    log_tests(tester);
}

void test_big_uint_and() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    uint32_t result[5] = { 0 };

    // Single digit test (no carry, no underflow)
    const uint32_t a1[] = { 0x11110000 };
    const uint32_t b1[] = { 0x00002222 };
    const uint32_t expected1[] = { 0x00000000 };
    big_uint_and(result, a1, b1, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    const uint32_t a2[] = { 0xffffffff };
    const uint32_t b2[] = { 0x12345678 };
    const uint32_t expected2[] = { 0x12345678 };
    big_uint_and(result, a2, b2, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    const uint32_t a3[] = { 0x12345678 };
    const uint32_t b3[] = { 0xffffffff };
    const uint32_t expected3[] = { 0x12345678 };
    big_uint_and(result, a3, b3, 1);

    expect(tester, big_uint_equals(result, expected3, 1));

    const uint32_t a4[] = { 0xffffffff, 0x87654321 };
    const uint32_t b4[] = { 0x12345678, 0xffffffff };
    const uint32_t expected4[] = { 0x12345678, 0x87654321 };
    big_uint_and(result, a4, b4, 1);

    expect(tester, big_uint_equals(result, expected4, 1));

    const uint32_t a5[] = { 0xffff0000, 0xffff0000 };
    const uint32_t b5[] = { 0x0000ffff, 0x0000ffff };
    const uint32_t expected5[] = { 0x00000000, 0x00000000 };
    big_uint_and(result, a5, b5, 1);

    expect(tester, big_uint_equals(result, expected5, 1));

    const uint32_t a6[] = { 0x12345678, 0x12345678 };
    const uint32_t b6[] = { 0x12345678, 0x12345678 };
    const uint32_t expected6[] = { 0x12345678, 0x12345678 };
    big_uint_and(result, a6, b6, 1);

    expect(tester, big_uint_equals(result, expected6, 1));

    const uint32_t a7[] = { 0x87654321, 0x12345678 };
    big_uint_and(result, a7, a7, 1);

    expect(tester, big_uint_equals(result, a7, 1));

    // and-equals
    uint32_t a8[] = { 0xffffffff, 0x87654321 };
    const uint32_t b8[] = { 0x12345678, 0xffffffff };
    const uint32_t expected8[] = { 0x12345678, 0x87654321 };
    big_uint_and(a8, a8, b8, 1);

    expect(tester, big_uint_equals(a8, expected8, 1));

    log_tests(tester);
}

void test_big_uint_xor() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
    uint32_t result[5] = { 0 };

    // Single digit test (no carry, no underflow)
    const uint32_t a1[] = { 0xffff0000 };
    const uint32_t b1[] = { 0x0000ffff };
    const uint32_t expected1[] = { 0xffffffff };
    big_uint_xor(result, a1, b1, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    const uint32_t a2[] = { 0xffffffff };
    const uint32_t b2[] = { 0x00000000 };
    const uint32_t expected2[] = { 0xffffffff };
    big_uint_xor(result, a2, b2, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    const uint32_t a3[] = { 0x00000000 };
    const uint32_t b3[] = { 0x00000000 };
    const uint32_t expected3[] = { 0x00000000 };
    big_uint_xor(result, a3, b3, 1);

    expect(tester, big_uint_equals(result, expected3, 1));

    const uint32_t a4[] = { 0xffffffff, 0x00000000 };
    const uint32_t b4[] = { 0x00000000, 0xffffffff };
    const uint32_t expected4[] = { 0xffffffff, 0xffffffff };
    big_uint_xor(result, a4, b4, 1);

    expect(tester, big_uint_equals(result, expected4, 1));

    const uint32_t a5[] = { 0xffff0000, 0xffffffff };
    const uint32_t b5[] = { 0xffffffff, 0x0000ffff };
    const uint32_t expected5[] = { 0x0000ffff, 0xffff0000 };
    big_uint_xor(result, a5, b5, 1);

    expect(tester, big_uint_equals(result, expected5, 1));

    const uint32_t a6[] = { 0x12345678, 0x12345678 };
    const uint32_t b6[] = { 0x12345678, 0x12345678 };
    const uint32_t expected6[] = { 0x00000000, 0x00000000 };
    big_uint_xor(result, a6, b6, 1);

    expect(tester, big_uint_equals(result, expected6, 1));

    const uint32_t a7[] = { 0x87654321, 0x12345678 };
    const uint32_t expected7[] = { 0x00000000, 0x00000000 };
    big_uint_xor(result, a7, a7, 1);

    expect(tester, big_uint_equals(result, expected7, 1));

    // xor-equals
    uint32_t a8[] = { 0xffff0000, 0xffffffff };
    const uint32_t b8[] = { 0xffffffff, 0x0000ffff };
    const uint32_t expected8[] = { 0x0000ffff, 0xffff0000 };
    big_uint_xor(a8, a8, b8, 1);

    expect(tester, big_uint_equals(a8, expected8, 1));

    log_tests(tester);
}

void test_big_uint_add() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
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

    // operator assignment
    uint32_t a11[] = { 0x00000000, 0xffff0000, 0xffffffff };
    const uint32_t b11[] = { 0x00000000, 0x0000ffff, 0x00000001 };
    const uint32_t expected11[] = { 0x1, 0x00000000, 0x00000000 };
    big_uint_add(a11, a11, b11, 3);

    expect(tester, big_uint_equals(a11, expected11, 3));
    
    log_tests(tester);
}

void test_big_uint_sub() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
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

    // operator assignment
    uint32_t a8[] = { 0x00000000, 0x00000000 };
    const uint32_t b8[] = { 0x00000000, 0x00000001 };
    const uint32_t expected8[] = { 0xffffffff, 0xffffffff };
    big_uint_sub(a8, a8, b8, 2);

    expect(tester, big_uint_equals(a8, expected8, 2));

    log_tests(tester);
}

void test_big_uint_mult() {
    // Define variables to be tested with
    testing_logger_t *tester = create_tester();
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

    // operator assignment
    uint32_t a9[] = { 0x00000000, 0x31f596dc };
    const uint32_t b9[] = { 0x00000000, 0x0000fedc };
    const uint32_t expected9[] = { 0x000031bc, 0x9abbed10 };
    big_uint_mult(a9, a9, b9, 2);

    expect(tester, big_uint_equals(a9, expected9, 2));

    log_tests(tester);
}

void test_big_uint_div() {
    testing_logger_t *tester = create_tester();
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
    const uint32_t a3[] = { 0x0000000, 0x00000010 };
    const uint32_t b3[] = { 0x0000000, 0x00000002 };
    const uint32_t expected_quotient3[] = { 0x00000000, 0x00000008 };
    const uint32_t expected_remainder3[] = { 0x00000000, 0x00000000 };
    big_uint_div(quotients, remainders, a3, b3, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient3, 2));
    expect(tester, big_uint_equals(remainders, expected_remainder3, 2));

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

    expect(tester, big_uint_equals(quotients, expected_quotient5, 2));
    expect(tester, big_uint_equals(remainders, expected_remainder5, 2));

    // 2 digit division (no truncation)
    const uint32_t a6[] = { 0x00000009, 0x00000000 };
    const uint32_t b6[] = { 0x00000000, 0x00000020 };
    const uint32_t expected_quotient6[] = { 0x00000000, 0x48000000 };
    const uint32_t expected_remainder6[] = { 0x00000000, 0x00000000 };
    big_uint_div(quotients, remainders, a6, b6, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient6, 2));
    expect(tester, big_uint_equals(remainders, expected_remainder6, 2));

    // large number over itself + 1
    const uint32_t a7[] = { 0xffffffff, 0xfffffffe };
    const uint32_t b7[] = { 0xffffffff, 0xffffffff };
    const uint32_t expected_quotient7[] = { 0x00000000, 0x00000000 };
    const uint32_t expected_remainder7[] = { 0xffffffff, 0xfffffffe };
    big_uint_div(quotients, remainders, a7, b7, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient7, 2));
    expect(tester, big_uint_equals(remainders, expected_remainder7, 2));

    // large number over itself - 1
    const uint32_t a8[] = { 0xffffffff, 0xffffffff };
    const uint32_t b8[] = { 0xffffffff, 0xfffffffe };
    const uint32_t expected_quotient8[] = { 0x00000000, 0x00000001 };
    const uint32_t expected_remainder8[] = { 0x00000000, 0x00000001 };
    big_uint_div(quotients, remainders, a8, b8, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient8, 2));
    expect(tester, big_uint_equals(remainders, expected_remainder8, 2));

    // 3 digit number divided by 1 digit number
    const uint32_t a9[] = { 0x12345678, 0x9abcdeff, 0xffffffff };
    const uint32_t b9[] = { 0x00000000, 0x0000000, 0x0000fedc };
    const uint32_t expected_quotient9[] = { 0x00001249, 0x31f596dc, 0xf30531ec };
    const uint32_t expected_remainder9[] = { 0x00000000, 0x0000000, 0x0000f12f };
    big_uint_div(quotients, remainders, a9, b9, 3);

    expect(tester, big_uint_equals(quotients, expected_quotient9, 3));
    expect(tester, big_uint_equals(remainders, expected_remainder9, 3));

    // random number
    const uint32_t a10[] = { 0x00efa9af, 0x3619a918 };
    const uint32_t b10[] = { 0x00000ee1, 0xa8138dfe };
    const uint32_t expected_quotient10[] = { 0x00000000, 0x0000101a };
    const uint32_t expected_remainder10[] = { 0x00000c42, 0xeb3d5d4c };
    big_uint_div(quotients, remainders, a10, b10, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient10, 2));
    expect(tester, big_uint_equals(remainders, expected_remainder10, 2));

    // forced 1 by 2
    const uint32_t a11[] = { 0x00100000, 0x00000000 };
    const uint32_t b11[] = { 0x00000000, 0xf0000000 };
    const uint32_t expected_quotient11[] = { 0x00000000, 0x00111111 };
    const uint32_t expected_remainder11[] = { 0x00000000, 0x10000000 };
    big_uint_div(quotients, remainders, a11, b11, 2);

    expect(tester, big_uint_equals(quotients, expected_quotient11, 2));
    expect(tester, big_uint_equals(remainders, expected_remainder11, 2));

    // misc test
    const uint32_t a12[] = { 0x41763a5f, 0x991b4b60, 0x84285b8e };
    const uint32_t b12[] = { 0x126d0ba2, 0x278b1be0, 0x1eb138e3 };
    const uint32_t expected_quotient12[] = { 0x00000000, 0x00000000, 0x00000003 };
    const uint32_t expected_remainder12[] = { 0x0a2f1779, 0x2279f7c0, 0x2814b0e5 };
    big_uint_div(quotients, remainders, a12, b12, 3);

    expect(tester, big_uint_equals(quotients, expected_quotient12, 3));
    expect(tester, big_uint_equals(remainders, expected_remainder12, 3));

    log_tests(tester);
}

void test_big_uint_gcd() {
    testing_logger_t *tester = create_tester();
    uint32_t result[5] = { 0 };

    // relatively prime example
    const uint32_t a1[] = { 0x00000005 };
    const uint32_t b1[] = { 0x00000007 };
    const uint32_t expected1[] = { 0x00000001 };
    big_uint_gcd(result, a1, b1, 1);

    expect(tester, big_uint_equals(result, expected1, 1));

    // non-relatively prime
    const uint32_t a2[] = { 0x00000012 };
    const uint32_t b2[] = { 0x00000015 };
    const uint32_t expected2[] = { 0x00000003 };
    big_uint_gcd(result, a2, b2, 1);

    expect(tester, big_uint_equals(result, expected2, 1));

    // padded 0, non-relatively prime
    const uint32_t a3[] = { 0x00000000, 0x8ab6d43d };
    const uint32_t b3[] = { 0x00000000, 0xab43d5eb };
    const uint32_t expected3[] = { 0x00000000, 0x0000000b };
    big_uint_gcd(result, a3, b3, 2);

    expect(tester, big_uint_equals(result, expected3, 2));

    // multi-digit, non-relatively prime
    const uint32_t a4[] = { 0xffe352fa, 0x8ab6d43d };
    const uint32_t b4[] = { 0xc78d5a01, 0xab43d5eb };
    const uint32_t expected4[] = { 0x00000000, 0x00000007 };
    big_uint_gcd(result, a4, b4, 2);

    expect(tester, big_uint_equals(result, expected4, 2));

     // Multiple digit test (no carry, overflow)
    const uint32_t a5[] = { 0x00020000, 0x00010000 };
    const uint32_t b5[] = { 0x00000000, 0x02000000 };
    const uint32_t expected5[] = { 0x00000000, 0x00010000 };
    big_uint_gcd(result, a5, b5, 2);

    expect(tester, big_uint_equals(result, expected5, 2));

    // Multiple digit test (no carry, overflow)
    const uint32_t a6[] = { 0x00000025, 0x00300000 };
    const uint32_t b6[] = { 0x00000013, 0x11000000 };
    const uint32_t expected6[] = { 0x00000000, 0x00100000 };
    big_uint_gcd(result, a6, b6, 2);

    expect(tester, big_uint_equals(result, expected6, 2));

    // Multiple digit test (carry, overflow)
    const uint32_t a7[] = { 0x00000000, 0x10000000 };
    const uint32_t b7[] = { 0x00001100, 0xf0025000 };
    const uint32_t expected7[] = { 0x00000000, 0x00001000 };
    big_uint_gcd(result, a7, b7, 2);

    expect(tester, big_uint_equals(result, expected7, 2));

    // Misc. tests
    const uint32_t a8[] = { 0x00000000, 0x31f596dc };
    const uint32_t b8[] = { 0x00000000, 0x0000fedc };
    const uint32_t expected8[] = { 0x00000000, 0x000004 };
    big_uint_gcd(result, a8, b8, 2);

    expect(tester, big_uint_equals(result, expected8, 2));

    const uint32_t a9[] = { 0x000087b2, 0x799af391 };
    const uint32_t b9[] = { 0x0000a941, 0x69aca1e3 };
    const uint32_t expected9[] = { 0x00000000, 0x00000001 };
    big_uint_gcd(result, a9, b9, 2);

    expect(tester, big_uint_equals(result, expected9, 2));

    log_tests(tester);
}

void test_big_uint_gcd_extended() {
	testing_logger_t *tester = create_tester();
	uint32_t result_x[5] = { 0 };
	uint32_t result_y[5] = { 0 };

	const uint32_t a1[] = { 0x0000008f };
	const uint32_t b1[] = { 0x000000ea };
	const uint32_t expected_x1[] = { 0xfffffffd };
	const uint32_t expected_y1[] = { 0x00000005 };

	big_uint_gcd_extended(result_x, result_y, a1, b1, 1);

	expect(tester, big_uint_equals(expected_x1, result_x, 1));
	expect(tester, big_uint_equals(expected_y1, result_y, 1));

	const uint32_t a2[] = { 0x2b487392 };
	const uint32_t b2[] = { 0xd2c60104 };
	const uint32_t expected_x2[] = { 0x0564f14f };
	const uint32_t expected_y2[] = { 0xe5bb484b };

	big_uint_gcd_extended(result_x, result_y, a2, b2, 1);

	expect(tester, big_uint_equals(expected_x2, result_x, 1));
	expect(tester, big_uint_equals(expected_y2, result_y, 1));

	const uint32_t a3[] = { 0x00000000, 0x30bfb01a };
	const uint32_t b3[] = { 0x00000000, 0x987de21e };
	const uint32_t expected_x3[] = { 0xffffffff, 0xf6bd5ebe };
	const uint32_t expected_y3[] = { 0x00000000, 0x1cf7999b };

	big_uint_gcd_extended(result_x, result_y, a3, b3, 2);

	expect(tester, big_uint_equals(expected_x3, result_x, 2));
	expect(tester, big_uint_equals(expected_y3, result_y, 2));

	const uint32_t a4[] = { 0x0e8b90bd, 0x220b8c80 };
	const uint32_t b4[] = { 0x6ec46fd6, 0xe7ee1360 };
	const uint32_t expected_x4[] = { 0x0021b929, 0x43ebb88f };
	const uint32_t expected_y4[] = { 0xfeff2f07, 0xf8541193 };

	big_uint_gcd_extended(result_x, result_y, a4, b4, 2);

	expect(tester, big_uint_equals(expected_x4, result_x, 2));
	expect(tester, big_uint_equals(expected_y4, result_y, 2));

	const uint32_t a5[] = { 0x00000000, 0xcec6b8e4 };
	const uint32_t b5[] = { 0x7bec5ab5, 0xe87e8fcf };
	const uint32_t expected_x5[] = { 0xffffffff, 0xf2e4bc35 };
	const uint32_t expected_y5[] = { 0x07dad8bf, 0x603c39da };

	big_uint_gcd_extended(result_x, result_y, a5, b5, 2);

	expect(tester, big_uint_equals(expected_x5, result_x, 2));
	expect(tester, big_uint_equals(expected_y5, result_y, 2));

	const uint32_t a6[] = { 0x0ab1a3c2, 0xf61a4999 };
	const uint32_t b6[] = { 0x00000000, 0x083a6d6c };
	const uint32_t expected_x6[] = { 0x00000000, 0x0336ce65 };
	const uint32_t expected_y6[] = { 0xfbd2a1ae, 0x9bcddfcb };

	big_uint_gcd_extended(result_x, result_y, a6, b6, 2);

	expect(tester, big_uint_equals(expected_x6, result_x, 2));
	expect(tester, big_uint_equals(expected_y6, result_y, 2));

	const uint32_t a7[] = { 0xd6cfbac0, 0xf2dcfe01, 0xab2a4b8d };
	const uint32_t b7[] = { 0x41763a5f, 0x991b4b60, 0x84285b8e };
	const uint32_t expected_x7[] = { 0x016c1fa8, 0xee5ca7b3, 0x8afa8433 };
	const uint32_t expected_y7[] = { 0xfb552303, 0x6be085f9, 0xea8238e3 };

	big_uint_gcd_extended(result_x, result_y, a7, b7, 3);

	expect(tester, big_uint_equals(expected_x7, result_x, 3));
	expect(tester, big_uint_equals(expected_y7, result_y, 3));

	const uint32_t a8[] = { 0x5eda613c, 0x268411c6, 0x987e7270 };
	const uint32_t b8[] = { 0xc6f11378, 0x4d56c2b4, 0xa2799234 };
	const uint32_t expected_x8[] = { 0xfd1ea5e9, 0x3a87833e, 0x0f5901bd };
	const uint32_t expected_y8[] = { 0x060a7f7c, 0x08577482, 0xd35e08b6 };

	big_uint_gcd_extended(result_x, result_y, a8, b8, 3);

	expect(tester, big_uint_equals(expected_x8, result_x, 3));
	expect(tester, big_uint_equals(expected_y8, result_y, 3));

	const uint32_t a9[] = { 0x00000000, 0x00000000, 0x2adaa46f };
	const uint32_t b9[] = { 0x00000000, 0xdaff9a2e, 0x7f6758e3 };
	const uint32_t expected_x9[] = { 0x00000000, 0x00000000, 0x09c35db4 };
	const uint32_t expected_y9[] = { 0xffffffff, 0xce1b6a35, 0x19c3216b };

	big_uint_gcd_extended(result_x, result_y, a9, b9, 3);

	expect(tester, big_uint_equals(expected_x9, result_x, 3));
	expect(tester, big_uint_equals(expected_y9, result_y, 3));

	const uint32_t a10[] = { 0x00000000, 0x00000000, 0xfcb90859 };
	const uint32_t b10[] = { 0x00000000, 0x00000000, 0x8221014d };
	const uint32_t expected_x10[] = { 0xffffffff, 0xffffffff, 0xe5e6a3b3 };
	const uint32_t expected_y10[] = { 0x00000000, 0x00000000, 0x32afd6de };

	big_uint_gcd_extended(result_x, result_y, a10, b10, 3);

	expect(tester, big_uint_equals(expected_x10, result_x, 3));
	expect(tester, big_uint_equals(expected_y10, result_y, 3));

	log_tests(tester);
}

int main() {
    test_big_uint_equals();
    test_big_uint_cmp();
    test_big_uint_cpy();
    test_big_uint_load();
    test_big_uint_sprint();
    test_big_uint_max();
    test_big_uint_min();
    test_big_uint_shl();
    test_big_uint_shr();
    test_big_uint_shl2();
    test_big_uint_shr2();
    test_big_uint_or();
    test_big_uint_and();
    test_big_uint_xor();
    test_big_uint_add();
    test_big_uint_sub();
    test_big_uint_mult();
    test_big_uint_div();
    test_big_uint_gcd();
    test_big_uint_gcd_extended();

    return 0;
}
