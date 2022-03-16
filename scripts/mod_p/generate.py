''' this file generates the tests to implement the mod p functions '''
import sys
import os

# adding ./scripts to the current path
current = os.path.dirname(os.path.realpath(__file__))
parent = os.path.dirname(current)
sys.path.append(parent)

import mod as mod
import generator as test
import test_generator as tester

test_file = './tests/test-mod.c'

# initialize our tester file
tester.initialize_test(test_file, libs=['"mod.h"\n', '<stdlib.h>', '<stdio.h>', '"testing-logger.h"'])

test.create_test(test_file, mod.mod_p, 'mod_big_uint', test.generate_unary_test_case)
test.create_test(test_file, mod.mod_addition, 'mod_add', test.generate_binary_test_case)
test.create_test(test_file, mod.mod_subtraction, 'mod_sub', test.generate_binary_test_case)
test.create_test(test_file, mod.mod_init, 'mod_init', test.generate_mod_init_test_case, results=[])
test.create_test(test_file, mod.mod_mult, 'mod_mult', test.generate_mult_test_case, misc_tests=[
    (test.generate_mult_test_case_misc, 1, mod.prime0),
    (test.generate_mult_test_case_misc, 2, mod.prime1),
    (test.generate_mult_test_case_misc, 2, mod.prime2)
])
test.create_test(test_file, mod.mod_exp, 'mod_exp', test.generate_mod_exp_test_case)
test.create_test(test_file, mod.mod_inv, 'mod_inv', test.generate_mod_inv_test_case)
test.create_test(test_file, mod.mod_div, 'mod_div', test.generate_mult_test_case, misc_tests=[
    (test.generate_mult_test_case_misc, 1, mod.prime0),
    (test.generate_mult_test_case_misc, 2, mod.prime1),
    (test.generate_mult_test_case_misc, 2, mod.prime2)
])

# call all the tests
tester.test_closer(test_file)
