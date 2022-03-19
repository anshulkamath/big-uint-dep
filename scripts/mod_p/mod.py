''' this file contains the rudimentary python scripts to test and implement the mod p functions '''
import random
import sys
import os

# adding ./scripts to the current path
current = os.path.dirname(os.path.realpath(__file__))
parent = os.path.dirname(current)
sys.path.append(parent)

# setting random seed
random.seed(1)

# constants
SIZE_INT_32 = 32

# 13
prime0 = 0xD

# 4,394,089,623,437,882,399
prime1 = 0x3CFAF13B4C3EB41F

# 8,286,390,253,466,614,501
prime2 = 0x72FF2C084822FAE5

# ECDSA constant prime
prime_ecdsa = 0XFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F

def mod_p(n, p):
    ''' takes in a big integer n and an big prime p and returns n mod p '''
    return n % p

def mod_add(m, n, p):
    ''' calculates m + n (mod p) '''
    return (m + n) % p

def mod_sub(m, n, p):
    ''' calculates m - n (mod p) '''
    return (m - n) % p

def mod_init(p, len):
    ''' creates a mod_t from a prime p '''
    k = 0
    num_digits = len

    # calculate ceil(log_2 p)
    while ((1 << k) < p): k += SIZE_INT_32

    r = (1 << (2 * k)) // p

    return [k, 2 * num_digits + 1, p, r]

def mod_mult(m, n, mod_t):
    ''' calculates m * n (mod p) using Barrett Reduction '''
    [k, _, p, r] = mod_t

    x = m * n
    t = x - ((x * r) >> (2 * k)) * p
    
    if t >= p: t -= p

    return t

def mod_exp(x, e, mod_t):
    ''' calculates x^e (mod p), where p is the prime given in mod_t '''
    ind = 0
    y = 1

    # count the number of bits in the number
    num_bits = 0
    while e >> num_bits: num_bits += 1
    num_bits -= 1

    # do modular exponentiation using the bits of the number
    while (e >> ind):
        y = mod_mult(y, y, mod_t)
        if e >> (num_bits - ind) & 1:
            y = mod_mult(y, x, mod_t)

        ind += 1
    
    return y

def mod_inv(x, mod_t):
    ''' calculates x^(-1) (mod p) '''
    [_, _, p, _] = mod_t
    
    # Euler's theorem: a^phi(p) = 1 (mod p) --> phi(p) = p - 1
    # Hence, a^{-1} = a^{p-2}
    return mod_exp(x, p - 2, mod_t)

def mod_div(m, n, mod_t):
    ''' calculates m * n^(-1) (mod p) '''
    n_inv = mod_inv(n, mod_t)

    return mod_mult(m, n_inv, mod_t)

