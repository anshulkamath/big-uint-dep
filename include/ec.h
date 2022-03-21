#ifndef EC_H
#define EC_H

#include <stdint.h>
#include "mod.h"

#define N_MAX 8

typedef struct point {
    uint32_t x[N_MAX];  // x coordinate of point
    uint32_t y[N_MAX];  // y coordinate of point
} point_t;

typedef struct ec {
    uint32_t a[N_MAX];  // curve parameter a
    uint32_t b[N_MAX];  // curve parameter b
    uint32_t p[N_MAX];  // prime of the finite field
    uint32_t n[N_MAX];  // order of the generator point
    mod_t    mod_p;     // the barrett reduction precomputation factor for p
    mod_t    mod_n;     // the barrett reduction precomputation factor for n
    point_t  g;         // generator point
} ec_t;

// ------------------------------------------
//                Point Stubs                
// ------------------------------------------

/**
 * @brief prints out the point as a coordinate pair in R^2 in hex
 * 
 * @param pt the point to print
 */
void point_print(const point_t *pt);

/**
 * @brief initializes a point with the given coordinates
 * 
 * @param res where to put the new point
 * @param x pointer to the x coordinate
 * @param y pointer to the y coordinate
 */
void point_init(point_t *res, const uint32_t *x, const uint32_t *y);

/**
 * @brief returns true if and only if the given point `pt` is on the curve
 *        defined by `ec`
 * 
 * @param pt a pointer to the point to check
 * @param ec a pointer to the elliptic curve instance to use
 * @return 1 when `pt` is on the curve defined by `ec`
 * @return 0 when `pt` is not on the curve defined by `ec`
 */
uint8_t point_is_on_curve(const point_t *pt, const ec_t *ec);

/**
 * @brief returns true if and only if the given point represents the
 *        identity element (infinity)
 * 
 * @param pt the point to check
 * @return 1 when pt is equivalent to identity
 * @return 0 when pt is not equivalent to identity
 */
uint8_t point_is_identity(const point_t *pt);

/**
 * @brief gets a constant reference to the global identity object
 * 
 * @return point_t* a pointer to the global identity object
 */
const point_t* get_identity();

/**
 * @brief checks if two points are equal
 * 
 * @param p1 
 * @param p2 
 * @return uint8_t 
 */
uint8_t point_equals(const point_t *p1, const point_t *p2);

// ------------------------------------------
//            Elliptic Curve Stubs           
// ------------------------------------------

/**
 * @brief prints the elliptic curve's details
 * 
 * @param ec a pointer to the elliptic curve to print
 */
void ec_print(const ec_t *ec);

/**
 * @brief initializes an elliptic curve and checks if said curve is valid
 * 
 * @param ec where to put the elliptic curve instance
 * @param a a pointer to the parameter `a` for the elliptic curve instance
 * @param b a pointer to the parameter `b` for the elliptic curve instance
 * @param p a pointer to the parameter `p` for the elliptic curve instance
 * @param n a pointer to the parameter `n` for the elliptic curve instance
 * @param g a pointer to the parameter `g` for the elliptic curve instance
 * @return 1 when the elliptic curve was not initialized properly
 * @return 0 when the elliptic curve was initialized properly
 */
uint8_t ec_init(ec_t *ec, const uint32_t *a, const uint32_t *b, const uint32_t *p, const uint32_t *n, const point_t *g);

/**
 * @brief adds two points together on a given elliptic curve using the group
 *        relevant group operation
 * 
 * @param res where to store the resultant point
 * @param p1 a pointer to the first point to add
 * @param p2 a pointer to the second point to add
 * @param ec a pointer to the elliptic curve instance to use
 */
void ec_add(point_t *res, const point_t *p1, const point_t *p2, const ec_t *ec);

/**
 * @brief multiplies a point `pt` by a scalar `k` using repeated addition
 * 
 * @param res where to store the resultant point
 * @param k a pointer to the scalar big integer to multiply by
 * @param pt a pointer to the point to multiply
 * @param ec a pointer to the elliptic curve instance to use
 */
void ec_mult(point_t *res, const uint32_t *k, const uint32_t *pt, const ec_t *ec);

/**
 * @brief generates a private and a public key using the given elliptic curve
 * 
 * @param pr_key where to store the private key
 * @param pu_key where to store the public key
 * @param ec a pointer to the elliptic curve instance to use
 */
void ec_keygen(uint32_t pr_key[N_MAX], point_t pu_key, const ec_t *ec);

#undef N_MAX
#endif
