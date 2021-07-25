#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "sha256.h"

/** Helper function to get the amount of memory (in bytes) needed for SHA-2 */
static uint64_t get_memory_size(size_t bits) {
    int curr_size = bits + 1 + 64;
    int counter = -1;

    while (curr_size > 512 * ++counter);

    return 512 * counter / 8;
}

/** Helper function to right rotate a number by a given value n */
static uint32_t right_rotate(uint32_t num, uint32_t n) {
    return num >> n | num << (32 - n);
}

void sha256(uint8_t *hash, const char *message, uint8_t length) {
    // initialize hash values
    // (first 32 bits of fractional part of the square root of the first 8 primes)
    uint32_t hashes[] = {
        0x6a09e667u, 0xbb67ae85u, 0x3c6ef372u, 0xa54ff53au,
        0x510e527fu, 0x9b05688cu, 0x1f83d9abu, 0x5be0cd19u
    };

    // initialize array of round constants
    // (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311)
    const uint32_t k[] = {
        0x428a2f98u, 0x71374491u, 0xb5c0fbcfu, 0xe9b5dba5u, 0x3956c25bu, 0x59f111f1u, 0x923f82a4u, 0xab1c5ed5u,
        0xd807aa98u, 0x12835b01u, 0x243185beu, 0x550c7dc3u, 0x72be5d74u, 0x80deb1feu, 0x9bdc06a7u, 0xc19bf174u,
        0xe49b69c1u, 0xefbe4786u, 0x0fc19dc6u, 0x240ca1ccu, 0x2de92c6fu, 0x4a7484aau, 0x5cb0a9dcu, 0x76f988dau,
        0x983e5152u, 0xa831c66du, 0xb00327c8u, 0xbf597fc7u, 0xc6e00bf3u, 0xd5a79147u, 0x06ca6351u, 0x14292967u,
        0x27b70a85u, 0x2e1b2138u, 0x4d2c6dfcu, 0x53380d13u, 0x650a7354u, 0x766a0abbu, 0x81c2c92eu, 0x92722c85u,
        0xa2bfe8a1u, 0xa81a664bu, 0xc24b8b70u, 0xc76c51a3u, 0xd192e819u, 0xd6990624u, 0xf40e3585u, 0x106aa070u,
        0x19a4c116u, 0x1e376c08u, 0x2748774cu, 0x34b0bcb5u, 0x391c0cb3u, 0x4ed8aa4au, 0x5b9cca4fu, 0x682e6ff3u,
        0x748f82eeu, 0x78a5636fu, 0x84c87814u, 0x8cc70208u, 0x90befffau, 0xa4506cebu, 0xbef9a3f7u, 0xc67178f2u
    };

    const size_t total_length = get_memory_size(8 * length);

    // pre-processing (with padding)
    // 1. copy all data to new memory
    uint8_t temp_data[total_length];
    uint64_t cursor;

    // initialize everything to 0 and then copy the original message
    memset(temp_data, 0, total_length);
    memcpy(temp_data, message, length);

    // 2. append a 1 to the data
    temp_data[length] = 128;
    cursor = length + 1;

    // 3. pad the rest of the data with 0s until total length is reached
    while (cursor < total_length)
        temp_data[cursor++] = 0;

    // 4. set the last 8 bytes to the length of the message
    uint64_t* last_64 = (uint64_t *) &temp_data[total_length - 8];
    *last_64 = htonll((uint64_t) (8 * length));

    // break the data into 512 bit chunks
    uint32_t w[64];
    for (size_t i = 0; i < total_length; i += 64) {
        memset(w, 0, 64 * sizeof(uint32_t));

        // convert to big endian
        for (size_t j = 0; j < 16; j++) {
            w[j] = htonl(*((uint32_t *) (temp_data + i + j * 4)));
        }

        // Extend the first 16 words into the remaining 48 words w[16..63] of the message schedule array:
        for (size_t j = 16; j < 64; j++) {
            uint32_t s0 = right_rotate(w[j - 15], 7) ^ right_rotate(w[j - 15], 18) ^ (w[j - 15] >> 3);
            uint32_t s1 = right_rotate(w[j - 2], 17) ^ right_rotate(w[j - 2], 19) ^ (w[j - 2] >> 10);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }

        // Initialize working variables to current hash value:
        uint32_t a = hashes[0];
        uint32_t b = hashes[1];
        uint32_t c = hashes[2];
        uint32_t d = hashes[3];
        uint32_t e = hashes[4];
        uint32_t f = hashes[5];
        uint32_t g = hashes[6];
        uint32_t h = hashes[7];

        // Compression function main loop
        for (size_t j = 0; j < 64; j++) {
            uint32_t S1 = right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
            uint32_t ch = (e & f) ^ ((~e) & g);
            uint32_t temp1 = h + S1 + ch + k[j] + w[j];
            uint32_t S0 = right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Add the compressed chunk to the current hash value:
        hashes[0] += a;
        hashes[1] += b;
        hashes[2] += c;
        hashes[3] += d;
        hashes[4] += e;
        hashes[5] += f;
        hashes[6] += g;
        hashes[7] += h;
    }

    // put all hashes into an array and convert them to big endian
    for (size_t i = 0; i < 8; i++) {
        hashes[i] = htonl(hashes[i]);
    }

    // copy all the hash data into the hash casted as 32 bit integer
    memcpy(hash, hashes, 8 * sizeof(uint32_t));
}
