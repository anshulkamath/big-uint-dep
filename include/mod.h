#ifndef MOD_H
#define MOD_H

#include <stdlib.h>
#include "big-uint.h"

/**
 * @brief Takes in a big integer n and puts the result n (mod p) into result
 * 
 * @param result A pointer to where to store the modular projection
 * @param n The big integer we are modding
 * @param p The prime we are modding out by
 * @param len The number of digits in n and p
 */
void mod_big_uint(uint32_t* result, const uint32_t* n, const uint32_t* p, size_t len);

/**
 * @brief Computes a + b (mod p) and puts the sum into result
 * 
 * @param result A pointer to where to store the modular sum
 * @param a The first integer to sum
 * @param b The second integer to sum
 * @param p The prime we are modding out by
 * @param len The number of digits in a, b, and p
 */
void mod_add(uint32_t* result, const uint32_t* a, const uint32_t* b, const uint32_t* p, size_t len);

/**
 * @brief Computes a - b (mod p) and puts the difference into result
 * 
 * @param result A pointer to where to store the modular difference
 * @param a The first integer to subtract from
 * @param b The second integer to we are subtracting
 * @param p The prime we are modding out by
 * @param len The number of digits in a, b, and p
 */
void mod_sub(uint32_t* result, const uint32_t* a, const uint32_t* b, const uint32_t* p, size_t len);

/**
 * @brief Computes a * b (mod p) and puts the sum into result
 * 
 * @param result A pointer to where to store the modular product
 * @param a The first integer to multiply
 * @param b The second integer to multiply
 * @param p The prime we are modding out by
 * @param len The number of digits in a, b, and p
 */
void mod_mult(uint32_t* result, const uint32_t* a, const uint32_t* b, const uint32_t* p, size_t len);

/**
 * @brief Calculates the multiplicative inverse of n modulo p
 * 
 * @param result A pointer to where to store the modular inverse
 * @param n The integer we are finding the inverse of
 * @param p The prime p of the field we are in
 * @param len The number of digits in n and p
 */
void mod_inv(uint32_t* result, const uint32_t* n, const uint32_t* p, size_t len);

#endif
