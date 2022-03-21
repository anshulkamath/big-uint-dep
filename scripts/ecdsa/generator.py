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
from ecdsa import *

G_inv = Coord(G.x, (-G.y) % p)

def generate_ec_add_test(ind, file, func, func_name, num_digits=8, p1=None, p2=None):
    ''' generates a test case for the ec_add function '''
    cv = EllipticCurve()
    
    if not p1:
        p1 = cv.gen_point()

    if not p2:
        p2 = cv.gen_point()

    res = func(p1, p2)

    with open(file, 'a', newline='') as out:
        out.write(f'\t// Test {ind}\n')
        out.write(f'\tconst uint32_t x{ind}a[] = {tester.format_point(p1.x, num_digits)};\n')
        out.write(f'\tconst uint32_t y{ind}a[] = {tester.format_point(p1.y, num_digits)};\n')
        out.write(f'\tconst point_t p{ind}a;\n')
        out.write(f'\tpoint_init(&p{ind}a, x{ind}a, y{ind}a);\n\n')

        out.write(f'\tconst uint32_t x{ind}b[] = {tester.format_point(p2.x, num_digits)};\n')
        out.write(f'\tconst uint32_t y{ind}b[] = {tester.format_point(p2.y, num_digits)};\n')
        out.write(f'\tconst point_t p{ind}b;\n')
        out.write(f'\tpoint_init(&p{ind}b, x{ind}b, y{ind}b);\n\n')
        
        out.write(f'\tconst uint32_t expected_x{ind}[] = {tester.format_point(res.x, num_digits)};\n')
        out.write(f'\tconst uint32_t expected_y{ind}[] = {tester.format_point(res.y, num_digits)};\n')
        out.write(f'\tconst point_t expected_p{ind};\n')
        out.write(f'\tpoint_init(&expected_p{ind}, &expected_x{ind}, &expected_y{ind});\n\n')

        out.write(f'\t{func_name}(&result, &p{ind}a, &p{ind}b, &EC);\n\n')

        out.write(f'\texpect(tester, point_equals(&expected_p{ind}, &result));\n\n')
    
def create_ec_add_test(file, func, func_name, generate_func, results=['result'], misc_tests=None):
    ''' creates a test for the given function '''
    indexer = tester.create_indexer()
    test_creator = tester.test_creator(
        file,
        func_name,
        results=results
    )

    next(test_creator)

    def generate(p1 = None, p2=None):
        generate_func(next(indexer), file, func, func_name, num_digits=8, p1=p1, p2=p2)
    
    generate(I, I)
    generate(I, G)
    generate(G, I)
    generate(G, G)
    generate(G, G_inv)

    generate()
    generate()
    generate()

    generate()
    generate()
    generate()
    generate()

    # if there are miscellaneous tests to run afterwards, run them
    if misc_tests:
        for (test, digits, p) in misc_tests:
            test(next(indexer), file, func, func_name, digits, p=p)

    next(test_creator)