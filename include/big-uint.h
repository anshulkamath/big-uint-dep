#ifndef BIG_UINT_H
#define BIG_UINT_H

#include <stdlib.h>

/**
 * @brief Returns true if and only if the two big uints are equal
 * 
 * @param a The first number to compare
 * @param b The second number to compare
 * @param len The number of digits in the length
 * @return int 0 if and only if the elements are not equal
 */
int big_uint_equals(const uint32_t *a, const uint32_t *b, size_t len);

/**
 * @brief Compares a > b. Returns 1, 0, and -1 if a > b, a == b, and a < b,
 *        respectively.
 * 
 * @param a A pointer to the first integer to compare
 * @param b A pointer to the second integer to compare
 * @param len The number of digits in the integers
 * @return int 1, 0, and -1 if a > b, a == b, and a < b, respectively.
 */
int big_uint_cmp(const uint32_t *a, const uint32_t *b, size_t len);

/**
 * @brief Returns a pointer to max(a, b). If a == b, returns a
 * 
 * @param a The first number to comparee
 * @param len_a The number of digits in a
 * @param b The second number to compare
 * @param len_b The number of digits in b
 * @return uint32_t* A pointer to max(a, b)
 */
uint32_t* big_uint_max(uint32_t *a, size_t len_a, uint32_t *b, size_t len_b);

/**
 * @brief Returns a pointer to min(a, b). If a == b, returns a
 * 
 * @param a The first number to comparee
 * @param len_a The number of digits in a
 * @param b The second number to compare
 * @param len_b The number of digits in b
 * @return uint32_t* A pointer to min(a, b)
 */
uint32_t* big_uint_min(uint32_t *a, size_t len_a, uint32_t *b, size_t len_b);

/**
 * @brief Writes the hex representation fo the given value to the given char*
 * 
 * @param dest The element to write to
 * @param value A pointer to the integer
 * @param len The number of digits in the integer
 */
void big_uint_sprint(char *dest, const uint32_t *value, size_t len);

/**
 * @brief Prints out the hex representation of the big integer
 * 
 * @param value The integer to print the hex value of
 * @param len The number of digits in the integer
 */
void big_uint_print(const uint32_t *value, size_t len);


/**
 * @brief Shifts the digits of a to the left n times
 * 
 * @param result Where the result is stored
 * @param a The number to shift
 * @param len The number of digits in the shiftee
 * @param n The number of digits to shift left
 */
void big_uint_shl(uint32_t *result, const uint32_t *a, size_t len, size_t n);

/**
 * @brief Shifts the digits of a to the right n times
 * 
 * @param result Where the result is stored
 * @param a The number to shift
 * @param len The number of digits in the shiftee
 * @param n The number of digits to shift right
 */
void big_uint_shr(uint32_t *result, const uint32_t *a, size_t len, size_t n);

/**
 * @brief Calculates the sum a + b and writes it to result.
 * @note If the sum results in overflow, returns sum mod 2^n,
 *       where n is the number of bits in the integer
 *
 * @param result The variable to which we write the sum
 * @param a The first element of the sum
 * @param b The second element of the sum
 * @param len The number of digits in a and b
 */
void big_uint_add(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len);

/**
 * @brief Calculates the difference a - b and writes it to result.
 * @note If the difference results in underflow, returns sum mod 2^n,
 *       where n is the number of bits in the integer
 *
 * @param result The variable to which we write the sum
 * @param a The first element of the sum
 * @param b The second element of the sum
 * @param len The number of digits in a and b
 */
void big_uint_sub(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len);

/**
 * @brief Calculates the product a * b and writes it to result.
 * @note If the product results in overflow, returns sum mod 2^n,
 *       where n is the number of bits in the integer
 *
 * @param result The variable to which we write the sum
 * @param a The first element of the sum
 * @param b The second element of the sum
 * @param len The number of digits in a and b
 */
void big_uint_mult(uint32_t *result, const uint32_t *a, const uint32_t *b, size_t len);

/**
 * @brief Calculates the quotient u / v and writes it to result.
 * @note Divide by 0 results in no changes.
 * 
 * @param q The quotient
 * @param r The remainder
 * @param u The dividend
 * @param v The divisor
 * @param len The number of digits
 */
void big_uint_div(uint32_t *q, uint32_t *r, const uint32_t *u, const uint32_t *v, size_t len);

/**
 * @brief Calculates the gcd of big uints a and b as gcd(a, b) = d
 * 
 * @param d A pointer to the big_uint d to write to
 * @param a A pointer to the big_uint a as defined above
 * @param b A pointer to the big_uint b as defined above
 * @param len The number of digits in each big uint
 */
void big_uint_gcd(uint32_t* d, const uint32_t *a, const uint32_t *b, size_t len);

#endif
