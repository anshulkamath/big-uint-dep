''' this file contains the rudimentary python scripts to test and implement the mod p functions '''
import random
import sys
import os

# adding ./scripts to the current path
current = os.path.dirname(os.path.realpath(__file__))
parent = os.path.dirname(current)
sys.path.append(parent)

import test_generator as tester


test_file = './scripts/test-mod-p.c'

prime0 = 0xd

# 4,394,089,623,437,882,399
prime1 = 0x3CFAF13B4C3EB41F

# 8,286,390,253,466,614,501
prime2 = 0x72FF2C084822FAE5

def mod_p(n, p):
    ''' takes in a big integer n and an big prime p and returns n mod p '''
    return n % p

def generate_mod_p_test_case(ind, func_name, num_digits, n = None, p = None):
    ''' generates a test case for the mod_p function '''
    if not n:
        n = tester.generate_random_number(num_digits)
    if not p:
        p = random.choice([prime0, prime1, prime2])

    res = mod_p(n, p)

    with open(test_file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}\n')
        out.write(f'\tconst uint32_t n{ind}[] = {tester.format_int(n, num_digits)};\n')
        out.write(f'\tconst uint32_t p{ind}[] = {tester.format_int(p, num_digits)};\n')
        out.write(f'\tconst uint32_t expected{ind}[] = {tester.format_int(res, num_digits)};\n')
        out.write('\n')
        out.write(f'\t{func_name}(result, n{ind}, p{ind}, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected{ind}, result, {num_digits}));\n')
        out.write('\n')

def create_test(file, func_name, generate_func):
    test_creator = tester.test_creator(
        file,
        func_name,
    )
    indexer = tester.create_indexer()

    next(test_creator)

    def generate(num_digits, n = None, p = None):
        generate_func(next(indexer), func_name, num_digits, n, p)
    
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

create_test(test_file, 'mod_big_uint', generate_mod_p_test_case)
