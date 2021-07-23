#ifndef SHA256_H
#define SHA256_H

#include <stdlib.h>

/** Constant defining the number of bytes for a SHA-2 hash */
extern const uint16_t SHA256_BITS;

/**
 * @brief Takes in the byte data and encrypts it using SHA-2
 * 
 * @param hash A pointer to where the hash should be written
 * @param data The data to hash
 * @param length The length of the data
 */
void sha256(uint8_t *hash, const char *message, uint8_t length);

#endif
