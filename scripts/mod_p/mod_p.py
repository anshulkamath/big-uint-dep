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

import test_generator as tester
import gcd.gcd as gcd

# 13
prime0 = 0xD

# 4,394,089,623,437,882,399
prime1 = 0x3CFAF13B4C3EB41F

# 8,286,390,253,466,614,501
prime2 = 0x72FF2C084822FAE5

def mod_p(n, p):
    ''' takes in a big integer n and an big prime p and returns n mod p '''
    return n % p

def mod_addition(m, n, p):
    ''' calculates m + n (mod p) '''
    return (m + n) % p

def mod_subtraction(m, n, p):
    ''' calculates m - n (mod p) '''
    return (m - n) % p

def mod_mult(m, n, p):
    ''' calculates m * n (mod p) using Barrett Reduction '''
    k = 0

    # calculate ceil(log_2 p)
    while ((1 << k) < p): k += 1
    k *= 2 # calculate 4^k
    
    # calculate Barrett coefficient
    r = (1 << (2 * k)) // p

    x = m * n
    t = x - ((x * r) >> (2 * k)) * p
    
    if t >= p: t -= p

    return t

def mod_div(m, n, p):
    ''' calculates m * n^(-1) (mod p) '''
    while n == 0:
        n = tester.generate_random_number(tester.get_num_digits(n)) % p
    
    _, n_inv = gcd.gcd_extended(n, p)

    return (m * n_inv) % p

def generate_unary_test_case(ind, file, func, func_name, num_digits, n = None, p = None):
    ''' generates a test case for the mod_p function '''
    if not n:
        n = tester.generate_random_number(num_digits)
    if not p:
        p = random.choice([prime0, prime1, prime2])

    res = func(n, p)

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}\n')
        out.write(f'\tconst uint32_t n{ind}[] = {tester.format_int(n, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst uint32_t expected{ind}[] = {tester.format_int(res, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(result, n{ind}, p{ind}, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}, result, {num_digits}));\n')
        out.write('\n')

def generate_binary_test_case(ind, file, func, func_name, num_digits, m = None, n = None, p = None):
    ''' generates a test case for the mod_p function '''
    if not p:
        p = random.choice([prime0, prime1, prime2])

    if not n:
        n = tester.generate_random_number(num_digits)
    
    if not m:
        m = tester.generate_random_number(num_digits)

    res = func(m, n, p)

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}\n')
        out.write(f'\tconst uint32_t m{ind}[] = {tester.format_int(m % p, num_digits)};\n')
        out.write(f'\tconst uint32_t n{ind}[] = {tester.format_int(n % p, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst uint32_t expected{ind}[] = {tester.format_int(res, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(result, m{ind}, n{ind}, p{ind}, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}, result, {num_digits}));\n')
        out.write('\n')

def create_test(file, func, func_name, generate_func):
    ''' creates a test for the given function '''
    indexer = tester.create_indexer()
    test_creator = tester.test_creator(
        file,
        func_name,
    )

    next(test_creator)

    def generate(num_digits, p = None):
        generate_func(next(indexer), file, func, func_name, num_digits, p=p)
    
    generate(1, p = prime0)
    generate(2, p = prime0)
    generate(3, p = prime0)

    generate(2, p = prime1)
    generate(3, p = prime1)
    generate(3, p = prime1)
    generate(4, p = prime1)

    generate(2, p = prime2)
    generate(3, p = prime2)
    generate(3, p = prime2)
    generate(4, p = prime2)

    next(test_creator)
