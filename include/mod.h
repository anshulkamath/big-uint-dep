#ifndef MOD_H
#define MOD_H

#include <stdlib.h>
#include "big-uint.h"

#define N_MAX 32    // maximum number of digits

typedef struct mod {
    uint32_t p[2 * N_MAX];  // pointer to prime number
    uint32_t r[2 * N_MAX];  // r-value in barrett reduction
    size_t            len;  // number of digits in p
    uint32_t            k;  // k-value in barrett reduction
} mod_t;

/**
 * @brief Returns a mod_t that results from Barrett Reduction
 * 
 * @param p The prime that is used to calculate r
 * @param len The number of digits in p
 * @return mod_t 
 */
mod_t mod_init(const uint32_t *p, size_t len);

/**
 * @brief Calculates the pre-computation factor r in Barrett reduction 
 * 
 * @param p The prime to use in Barrett reduction
 * @param r A pointer of where to store the result
 * @param len The number of digits in p and r
 */
void barrett_r(const uint32_t *p, uint32_t *r, size_t len);

/**
 * @brief Takes in a big integer n and puts the result n (mod p) into result
 * 
 * @param result A pointer to where to store the modular projection
 * @param n The big integer we are modding
 * @param p The prime we are modding out by
 * @param len The number of digits in n and p
 */
void mod_big_uint(uint32_t *result, const uint32_t *n, const uint32_t *p, size_t len);

/**
 * @brief Computes a + b (mod p) and puts the sum into result
 * 
 * @param result A pointer to where to store the modular sum
 * @param a The first integer to sum
 * @param b The second integer to sum
 * @param p The prime we are modding out by
 * @param len The number of digits in a, b, and p
 */
void mod_add(uint32_t *result, const uint32_t *a, const uint32_t *b, const uint32_t *p, size_t len);

/**
 * @brief Computes a - b (mod p) and puts the difference into result
 * 
 * @param result A pointer to where to store the modular difference
 * @param a The first integer to subtract from
 * @param b The second integer to we are subtracting
 * @param p The prime we are modding out by
 * @param len The number of digits in a, b, and p
 */
void mod_sub(uint32_t *result, const uint32_t *a, const uint32_t *b, const uint32_t *p, size_t len);

/**
 * @brief Computes a * b (mod p) and puts the product into result
 * 
 * @param result A pointer to where to store the modular product
 * @param a The first integer to multiply
 * @param b The second integer to multiply
 * @param mod The mod struct initialized with the barrett reduction precomputation factor
 * @param len The number of digits in a, b, and p
 */
void mod_mult(uint32_t *result, const uint32_t *a, const uint32_t *b, const mod_t *mod, size_t len);

/**
 * @brief Computes x^e (mod p) and puts the product into result
 * 
 * @param result A pointer to where to store the modular product
 * @param x The base of the exponent
 * @param e The power of the exponent
 * @param mod The mod struct initialized with the barrett reduction precomputation factor
 * @param len The number of digits in x, e, and p
 */
void mod_exp(uint32_t *result, const uint32_t *x, const uint32_t *e, const mod_t *mod, size_t len);

/**
 * @brief Calculates the multiplicative inverse of x modulo p
 * 
 * @param result A pointer to where to store the modular inverse
 * @param x The integer we are finding the inverse of
 * @param mod The mod struct initialized with the barrett reduction precomputation factor
 * @param len The number of digits in x and p
 */
void mod_inv(uint32_t *result, const uint32_t *x, const mod_t *mod, size_t len);

/**
 * @brief Calculates the product m * n^{-1} modulo p
 * 
 * @param result A pointer to where to store the modular product
 * @param m The first integer to multiply
 * @param n The second integer to multiply the inverse of
 * @param mod The mod struct initialized with the barrett reduction precomputation factor
 * @param len The number of digits in m, n, and p 
 */
void mod_div(uint32_t *result, const uint32_t *m, const uint32_t *n, const mod_t *mod, size_t len);

#endif
