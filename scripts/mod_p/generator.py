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
from mod import *

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

def generate_mod_copy_test_case(ind, file, func, func_name, num_digits, p=None):
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
        out.write(f'\tconst mod_t expected_mod{ind} = mod_init(p{ind}, {num_digits});\n')
        out.write(f'\tmod_t result_mod{ind};\n')
        out.write('\n')
        out.write(f'\tmod_t_copy(&result_mod{ind}, &expected_mod{ind});\n')
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

def generate_mult_op_ass1(ind, file, func, func_name, num_digits, p=None, m=None, n=None):
    ''' additional tests for operator assignment. Tests (m = m `opp` n) '''
    if not p:
        p = random.choice([prime0, prime1, prime2])

    while not n:
        n = tester.generate_random_number(num_digits) % p

    while not m:
        m = tester.generate_random_number(num_digits) % p
    
    # calculate the product of m and n mod p
    res_a = func(m, n, mod_init(p, num_digits))

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}a\n')
        out.write(f'\t// Operator assignment\n')
        out.write(f'\tuint32_t m{ind}a[] = {tester.format_int(m, num_digits)};\n')
        out.write(f'\tconst uint32_t n{ind}a[] = {tester.format_int(n, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}a[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst mod_t    mod{ind}a = mod_init(p{ind}a, {num_digits});\n')
        out.write(f'\tconst uint32_t expected{ind}a[] = {tester.format_int(res_a, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(m{ind}a, m{ind}a, n{ind}a, &mod{ind}a, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}a, m{ind}a, {num_digits}));\n')
        out.write('\n')

def generate_mult_op_ass2(ind, file, func, func_name, num_digits, p=None, m=None, n=None):
    ''' additional tests for operator assignment. Tests (m = n `opp` m) '''
    if not p:
        p = random.choice([prime0, prime1, prime2])

    while not n:
        n = tester.generate_random_number(num_digits) % p

    while not m:
        m = tester.generate_random_number(num_digits) % p
    
    # calculate the product of m and n mod p
    res_b = func(n, m, mod_init(p, num_digits))

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}b\n')
        out.write(f'\t// Operator assignment\n')
        out.write(f'\tuint32_t m{ind}b[] = {tester.format_int(m, num_digits)};\n')
        out.write(f'\tconst uint32_t n{ind}b[] = {tester.format_int(n, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}b[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst mod_t    mod{ind}b = mod_init(p{ind}b, {num_digits});\n')
        out.write(f'\tconst uint32_t expected{ind}b[] = {tester.format_int(res_b, num_digits)};\n')
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
        out.write(f'\tconst mod_t    mod{ind} = mod_init(p{ind}, {num_digits});\n')
        out.write(f'\tconst uint32_t expected{ind}[] = {tester.format_int(res, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(result, x{ind}, &mod{ind}, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}, result, {num_digits}));\n')
        out.write('\n')

def generate_mod_neg_test_case(ind, file, func, func_name, num_digits, n = None, p = None):
    ''' generates a test case for the mod_p function '''
    if not n:
        n = tester.generate_random_number(num_digits) % p
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

def create_test(file, func, func_name, generate_func, types=['uint32_t'], results=['result'], misc_tests=None):
    ''' creates a test for the given function '''
    indexer = tester.create_indexer()
    test_creator = tester.test_creator(
        file,
        func_name,
        types=types,
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
