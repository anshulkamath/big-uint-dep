''' this file generates the tests to implement the mod p functions '''
import sys
import os

# adding ./scripts to the current path
current = os.path.dirname(os.path.realpath(__file__))
parent = os.path.dirname(current)
sys.path.append(parent)

import mod_p as mod_p
import test_generator as tester

test_file = './tests/test-mod.c'

# initialize our tester file
tester.initialize_test(test_file, libs=['"mod.h"\n', '<stdlib.h>', '<stdio.h>', '"testing-logger.h"'])

mod_p.create_test(test_file, mod_p.mod_p, 'mod_big_uint', mod_p.generate_unary_test_case)
mod_p.create_test(test_file, mod_p.mod_addition, 'mod_add', mod_p.generate_binary_test_case)
mod_p.create_test(test_file, mod_p.mod_subtraction, 'mod_sub', mod_p.generate_binary_test_case)
mod_p.create_test(test_file, mod_p.mod_init, 'mod_init', mod_p.generate_mod_init_test_case, results=[])
mod_p.create_test(test_file, mod_p.mod_mult, 'mod_mult', mod_p.generate_mult_test_case, misc_tests=[
    (mod_p.generate_mult_test_case_misc, 1, mod_p.prime0),
    (mod_p.generate_mult_test_case_misc, 2, mod_p.prime1),
    (mod_p.generate_mult_test_case_misc, 2, mod_p.prime2)
])
mod_p.create_test(test_file, mod_p.mod_exp, 'mod_exp', mod_p.generate_mod_exp_test_case)

# mod_p.create_test(test_file, mod_p.mod_div, 'mod_div', mod_p.generate_binary_test_case)

# call all the tests
tester.test_closer(test_file)
