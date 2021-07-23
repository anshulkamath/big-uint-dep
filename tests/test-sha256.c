#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hex.h"
#include "sha256.h"

void test_sha256() {
    const uint32_t num_bytes = SHA256_BITS / 8;

    // defining test vectors
    const char test1[] = "";
    const char test2[] = "abc";
    const char test3[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    const char test4[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
    const char test5[] = "the quick brown fox jumped over the lazy dog";

    const char expected1[] = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    const char expected2[] = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
    const char expected3[] = "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1";
    const char expected4[] = "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1";
    const char expected5[] = "20c1892df4e665666558289367ae1682d1f93bc5be4049627492cdb5a42635e4";

    uint8_t result[num_bytes];
    char result_str[num_bytes * 2 + 1];
    result_str[num_bytes * 2] = '\0'; // null terminate the result string

    // test 1
    sha256(result, test1, 0);
    to_string(result, num_bytes, result_str);
    assert(strcmp(result_str, expected1) == 0);

    // test 2
    sha256(result, test2, 3);
    to_string(result, num_bytes, result_str);
    assert(strcmp(result_str, expected2) == 0);

    // test 3
    sha256(result, test3, 56);
    to_string(result, num_bytes, result_str);
    assert(strcmp(result_str, expected3) == 0);

    // test 4
    sha256(result, test4, 112);
    to_string(result, num_bytes, result_str);
    assert(strcmp(result_str, expected4) == 0);

    // test 5
    sha256(result, test5, 44);
    to_string(result, num_bytes, result_str);
    assert(strcmp(result_str, expected5) == 0);

    printf("[PASS]\n");
}

int main() {
    test_sha256();
    
    return 0;
}
