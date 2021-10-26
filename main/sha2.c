#include <stdio.h>
#include <string.h>
#include "sha256.h"
#include "hex.h"

#define MESSAGE_SIZE 256

void to_hex(char *dest, const char *src, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        sprintf(&dest[i], "%08x", src[i]);
    }
    dest[len - 1] = 0;
}

int main(int argc, char **argv) {
    if (argc == 0) {
        printf("Please provide a string to hash.");
        return 0;
    }
    
    // stores the result of sha2 in bits
    uint8_t result[32];

    // to convert the bits of sha2 to hex
    char result_str[65];

    // get the length of the string
    size_t len = 0;
    while (argv[1][len]) ++len;

    // encode using sha2
    sha256(result, argv[1], len);

    // convert this to a string
    to_string(result, 32, result_str);

    // print the hash
    printf("SHA-2: %s\n", result_str);

    return 0;
}
