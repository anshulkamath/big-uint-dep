#ifndef HEX_H
#define HEX_H

#include <stdlib.h>

/**
 * @brief Converts a decimal int to a hexadecimal string
 * 
 * @param decimal The number to convert to hex
 * @param hex Where to store the char array
 */
void itoh(int decimal, char *hex);

/**
 * @brief Converts the array of decimal values to a hex string
 * 
 * @param vals The decimal values to convert
 * @param len_vals The number of elements in vals
 * @param hex_str The string of hexadecimal characters (null-terminated)
 */
void to_string(uint8_t vals[], size_t len_vals, char *hex_str);

#endif
