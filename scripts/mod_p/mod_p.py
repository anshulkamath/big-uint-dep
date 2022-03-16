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

def mod_addition(m, n, p):
    ''' calculates m + n (mod p) '''
    return (m + n) % p

def mod_subtraction(m, n, p):
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

def generate_mod_init_test_case(ind, file, func, func_name, num_digits, p=None):
    ''' generates a test case for the mod_init function '''
    if not p:
        p = random.choice([prime0, prime1, prime2])

    [k, n_p, p, r] = func(p, num_digits)

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}\n')
        out.write(f'\tconst uint32_t p{ind}[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst uint32_t expected_k{ind} = {k // SIZE_INT_32};\n')
        out.write(f'\tconst size_t expected_digits{ind} = {num_digits};\n')
        out.write(f'\tconst uint32_t expected_p{ind}[] = {tester.format_int(p, n_p)};\n')
        out.write(f'\tconst uint32_t expected_r{ind}[] = {tester.format_int(r, n_p)};\n')
        out.write('\n')
        out.write(f'\tconst mod_t result_mod{ind} = {func_name}(p{ind}, {num_digits});\n')
        out.write('\n')
        out.write(
            f'\texpect(tester, \n' +
            f'\t\texpected_k{ind} == result_mod{ind}.k &&\n' +
            f'\t\texpected_digits{ind} == result_mod{ind}.len &&\n' +
            f'\t\tbig_uint_equals(expected_p{ind}, result_mod{ind}.p, {n_p}) &&\n' +
            f'\t\tbig_uint_equals(expected_r{ind}, result_mod{ind}.r, {n_p})\n' +
            f'\t);\n'
        )
        out.write('\n')

def generate_mult_test_case(ind, file, func, func_name, num_digits, p=None, m=None, n=None):
    ''' generates a test case for modular multiplication '''
    if not p:
        p = random.choice([prime0, prime1, prime2])

    while not n:
        n = tester.generate_random_number(num_digits) % p

    while not m:
        m = tester.generate_random_number(num_digits) % p
    
    # calculate the product of m and n mod p
    res = func(m, n, mod_init(p, num_digits))

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}\n')
        out.write(f'\tconst uint32_t m{ind}[] = {tester.format_int(m, num_digits)};\n')
        out.write(f'\tconst uint32_t n{ind}[] = {tester.format_int(n, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst mod_t    mod{ind} = mod_init(p{ind}, {num_digits});\n')
        out.write(f'\tconst uint32_t expected{ind}[] = {tester.format_int(res, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(result, m{ind}, n{ind}, &mod{ind}, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}, result, {num_digits}));\n')
        out.write('\n')

def generate_mult_test_case_misc(ind, file, func, func_name, num_digits, p=None, m=None, n=None):
    ''' additional tests for modular multiplication '''
    if not p:
        p = random.choice([prime0, prime1, prime2])

    while not n:
        n = tester.generate_random_number(num_digits) % p

    while not m:
        m = tester.generate_random_number(num_digits) % p
    
    # calculate the product of m and n mod p
    res = func(m, n, mod_init(p, num_digits))

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}a\n')
        out.write(f'\t// Operator assignment\n')
        out.write(f'\tuint32_t m{ind}a[] = {tester.format_int(m, num_digits)};\n')
        out.write(f'\tconst uint32_t n{ind}a[] = {tester.format_int(n, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}a[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst mod_t    mod{ind}a = mod_init(p{ind}a, {num_digits});\n')
        out.write(f'\tconst uint32_t expected{ind}a[] = {tester.format_int(res, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(m{ind}a, m{ind}a, n{ind}a, &mod{ind}a, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}a, m{ind}a, {num_digits}));\n')
        out.write('\n')

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}b\n')
        out.write(f'\t// Operator assignment\n')
        out.write(f'\tuint32_t m{ind}b[] = {tester.format_int(m, num_digits)};\n')
        out.write(f'\tconst uint32_t n{ind}b[] = {tester.format_int(n, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}b[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst mod_t    mod{ind}b = mod_init(p{ind}b, {num_digits});\n')
        out.write(f'\tconst uint32_t expected{ind}b[] = {tester.format_int(res, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(m{ind}b, n{ind}b, m{ind}b, &mod{ind}b, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}b, m{ind}b, {num_digits}));\n')
        out.write('\n')

def generate_mod_exp_test_case(ind, file, func, func_name, num_digits, p=None, m=None, n=None):
    ''' generates a test case for modular multiplication '''
    if not p:
        p = random.choice([prime0, prime1, prime2])

    while not n:
        n = tester.generate_random_number(num_digits) % p

    while not m:
        m = tester.generate_random_number(num_digits) % p
    
    # calculate the product of m and n mod p
    res = func(m, n, mod_init(p, num_digits))

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}\n')
        out.write(f'\tconst uint32_t x{ind}[] = {tester.format_int(m, num_digits)};\n')
        out.write(f'\tconst uint32_t e{ind}[] = {tester.format_int(n, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst mod_t    mod{ind} = mod_init(p{ind}, {num_digits});\n')
        out.write(f'\tconst uint32_t expected{ind}[] = {tester.format_int(res, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(result, x{ind}, e{ind}, &mod{ind}, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}, result, {num_digits}));\n')
        out.write('\n')

def generate_mod_inv_test_case(ind, file, func, func_name, num_digits, n = None, p = None):
    ''' generates a test case for the mod_p function '''
    while not n:
        n = tester.generate_random_number(num_digits) % p
    if not p:
        p = random.choice([prime0, prime1, prime2])

    res = func(n, mod_init(p, num_digits))

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}\n')
        out.write(f'\tconst uint32_t x{ind}[] = {tester.format_int(n, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst uint32_t expected{ind}[] = {tester.format_int(res, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(result, x{ind}, p{ind}, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}, result, {num_digits}));\n')
        out.write('\n')

def create_test(file, func, func_name, generate_func, results=['result'], misc_tests=None):
    ''' creates a test for the given function '''
    indexer = tester.create_indexer()
    test_creator = tester.test_creator(
        file,
        func_name,
        results=results
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

    # if there are miscellaneous tests to run afterwards, run them
    if misc_tests:
        for (test, digits, p) in misc_tests:
            test(next(indexer), file, func, func_name, digits, p=p)

    next(test_creator)
