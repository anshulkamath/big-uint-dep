#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hex.h"
#include "testing-logger.h"
#include "sha256.h"

#define SHA256_BITS 256

// Tests
void empty_string_test() {
    // Defining tester
    testing_logger_t *tester = create_tester();

    // Defining test variables
    const uint32_t num_bytes = SHA256_BITS / 8;
    uint8_t result[num_bytes];
    char result_str[num_bytes * 2 + 1];
    result_str[num_bytes * 2] = '\0'; // null terminate the result string
    
    // Defining test params
    const char test[] = "";
    const char expected[] = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    
    sha256(result, test, 0);
    to_string(result, num_bytes, result_str);
    expect(tester, strcmp(result_str, expected) == 0);

    // print the results of the test
    log_tests(tester);
}

void single_char_test() {
    // Defining tester
    testing_logger_t *tester = create_tester();

    // Defining test variables
    const uint32_t num_bytes = SHA256_BITS / 8;
    uint8_t result[num_bytes];
    char result_str[num_bytes * 2 + 1];
    result_str[num_bytes * 2] = '\0'; // null terminate the result string
    
    // Defining test params
    const char test[] = "a";
    const char expected[] = "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb";
    
    sha256(result, test, 1);
    to_string(result, num_bytes, result_str);
    expect(tester, strcmp(result_str, expected) == 0);

    // print the results of the test
    log_tests(tester);
}

void small_string_test() {
    // Defining tester
    testing_logger_t *tester = create_tester();

    // Defining test variables
    const uint32_t num_bytes = SHA256_BITS / 8;
    uint8_t result[num_bytes];
    char result_str[num_bytes * 2 + 1];
    result_str[num_bytes * 2] = '\0'; // null terminate the result string
    
    // Defining test params
    const char test[] = "abc";
    const char expected[] = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
    
    sha256(result, test, 0);
    to_string(result, num_bytes, result_str);
    expect(tester, strcmp(result_str, expected) == 0);

    // print the results of the test
    log_tests(tester);
}

void normal_string_test() {
    // Defining tester
    testing_logger_t *tester = create_tester();

    // Defining test variables
    const uint32_t num_bytes = SHA256_BITS / 8;
    uint8_t result[num_bytes];
    char result_str[num_bytes * 2 + 1];
    result_str[num_bytes * 2] = '\0'; // null terminate the result string
    
    // Defining test params
    const char test[] = "the quick brown fox jumped over the lazy dog";
    const char expected[] = "20c1892df4e665666558289367ae1682d1f93bc5be4049627492cdb5a42635e4";
    
    sha256(result, test, 44);
    to_string(result, num_bytes, result_str);
    expect(tester, strcmp(result_str, expected) == 0);

    // print the results of the test
    log_tests(tester);
}

void overflow_test() {
    // Defining tester
    testing_logger_t *tester = create_tester();

    // Defining test variables
    const uint32_t num_bytes = SHA256_BITS / 8;
    uint8_t result[num_bytes];
    char result_str[num_bytes * 2 + 1];
    result_str[num_bytes * 2] = '\0'; // null terminate the result string
    
    // Defining test params
    const char test[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    const char expected[] = "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1";
    
    sha256(result, test, 56);
    to_string(result, num_bytes, result_str);
    expect(tester, strcmp(result_str, expected) == 0);

    // print the results of the test
    log_tests(tester);
}

void super_overflow_test() {
    // Defining tester
    testing_logger_t *tester = create_tester();

    // Defining test variables
    const uint32_t num_bytes = SHA256_BITS / 8;
    uint8_t result[num_bytes];
    char result_str[num_bytes * 2 + 1];
    result_str[num_bytes * 2] = '\0'; // null terminate the result string
    
    // Defining test params
    const char test[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
    const char expected[] = "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1";
    
    sha256(result, test, 112);
    to_string(result, num_bytes, result_str);
    expect(tester, strcmp(result_str, expected) == 0);

    // print the results of the test
    log_tests(tester);
}

int main() {
    empty_string_test();
    single_char_test();
    normal_string_test();
    overflow_test();
    super_overflow_test();
    
    return 0;
}
