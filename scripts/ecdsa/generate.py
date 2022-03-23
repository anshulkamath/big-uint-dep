''' this file generates the tests to implement the mod p functions '''
import sys
import os

# adding ./scripts to the current path
current = os.path.dirname(os.path.realpath(__file__))
parent = os.path.dirname(current)
sys.path.append(parent)

import ecdsa as ecdsa
import generator as test
import test_generator as tester

test_file = './scripts/ecdsa/test-ec.c'
cv = ecdsa.EllipticCurve()

tester.initialize_test(test_file, [])
test.create_ec_add_test(test_file, cv.ec_add, 'ec_add', test.generate_ec_add_test)
test.create_point_inv_test(test_file, 'point_is_inverse', test.generate_point_inv_test)
