import random
import sys
import os

# adding ./scripts to the current path
current = os.path.dirname(os.path.realpath(__file__))
parent = os.path.dirname(current)
sys.path.append(parent)

# setting random seed
random.seed(1)

from ecpy.curves import Curve, Point
import ecdsa as ec
from helpers import *

def gen_int(p: int = ec.p) -> int:
    ''' returns a random element in F_p '''
    return random.randint(1, p - 1)

def test_equals(p1: ec.Coord, p2: Point) -> bool:
    ''' checks if the two points are equal '''
    if p2.is_infinity:
        res = p1.x == 0 and p1.y == 0
    else:
        res = p1.x == p2.x and p1.y == p2.y
    
    return res

def test_ec_add():
    ''' test for elliptic curve addition '''
    cv1 = Curve.get_curve('secp256k1')
    cv2 = ec.Curve(ec.p, ec.n, ec.a, ec.b)
    mod_t = ec.mod.mod_init(ec.p, 0)

    random.seed(1)

    get_err = lambda p1, p2, cv, exp, act: \
            f'Error when adding {p1} to {p2} in curve {cv}.\nExpected\n\t{exp}\nbut got\n\t{act}\ninstead'

    # test distinct points
    for i in range(100):
        P1 = gen_point(cv2)
        P2 = gen_point(cv2)

        Q1 = Point(P1.x, P1.y, cv1)
        Q2 = Point(P2.x, P2.y, cv1)

        # varying tests for different conditions in ec_add
        if (50 <= i < 60):
            P1 = ec.Coord(0, 0)
            Q1 = Point.infinity()
        
        if (60 <= i < 70):
            P2 = ec.Coord(0, 0)
            Q2 = Point.infinity()
        
        if (70 <= i < 80):
            P2 = ec.Coord(P1.x, -P1.y)
            Q2 = Point(P2.x, P2.y, cv1)
        
        if (80 <= i < 100):
            P2 = P1
            Q2 = Q1

        exp = Q1 + Q2
        act = ec.ec_add(P1, P2, cv2, mod_t)

        if not test_equals(act, exp):
            print(get_err(P1, P2, cv2, exp, act))
            return False

    return True

def test_ec_mult():
    ''' tests for elliptic curve multiplication '''
    cv1 = Curve.get_curve('secp256k1')
    cv2 = ec.Curve(ec.p, ec.n, ec.a, ec.b)
    mod_t = ec.mod.mod_init(ec.p, 0)

    random.seed(1)

    get_err = lambda p1, k, cv, exp, act: \
            f'Error when multiplying {p1} by {k} in curve {cv}.\nExpected\n\t{exp}\nbut got\n\t{act}\ninstead'

    for _ in range(100):
        P = gen_point(cv2)
        Q = Point(P.x, P.y, cv1)
        k = random.randint(1, cv2.p - 1)

        exp = k * Q
        act = ec.ec_mult(P, k, cv2, mod_t)

        if not test_equals(act, exp):
            print(get_err(P, k, cv2, exp, act))
            return False

    return True

def run_tests(tests: callable = [test_ec_add, test_ec_mult]):
    ''' runs all test suites '''
    get_test_status = lambda x : '[PASS]' if x else '[FAIL]'
    for test in tests:
        res = test()
        print(f'{getattr(test, "__name__", repr(test))}: {get_test_status(res)}')

run_tests()
