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

def gen_int(p: int = ec.p) -> int:
    ''' returns a random element in F_p '''
    return random.randint(1, p - 1)

def test_equals(p1: ec.Coord, p2: Point) -> bool:
    ''' checks if the two points are equal '''
    if p2.is_infinity:
        res = p1 == ec.Coord.identity()
    else:
        res = p1.x == p2.x and p1.y == p2.y
    
    return res

def test_ec_add():
    ''' test for elliptic curve addition '''
    cv1 = Curve.get_curve('secp256k1')
    cv2 = ec.EllipticCurve(ec.p, ec.n, ec.a, ec.b)

    random.seed(1)

    get_err = lambda p1, p2, cv, exp, act: \
            f'Error when adding {p1} to {p2} in curve {cv}.\nExpected\n\t{exp}\nbut got\n\t{act}\ninstead'

    # test distinct points
    for i in range(100):
        P1 = cv2.gen_point()
        P2 = cv2.gen_point()

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
        act = cv2.ec_add(P1, P2)

        if not test_equals(act, exp):
            print(get_err(P1, P2, cv2, exp, act))
            return False

    return True

def test_ec_mult(num_tests=100):
    ''' tests for elliptic curve multiplication '''
    cv1 = Curve.get_curve('secp256k1')
    cv2 = ec.EllipticCurve(ec.p, ec.n, ec.a, ec.b)

    random.seed(1)

    get_err = lambda p1, k, cv, exp, act: \
            f'Error when multiplying\n\tpoint: {p1} \n\tby scalar: {hex(k)}\nin curve:\n  {cv}.\n\nExpected point\n\t{exp}\nbut got point\n\t{act}\ninstead\n'

    for i in range(num_tests):
        P = cv2.gen_point()
        k = random.randint(1, cv2.p - 1)
            
        # manual test before wrapping to identity
        if i == 0:
            P = cv2.G
            k = cv2.n - 1

        # manual test wrapping to identity
        if i == 1:
            P = cv2.G
            k = cv2.n
        
        # manual test wrapping to original generator
        if i == 2:
            P = cv2.G
            k = cv2.n + 1
        
        Q = Point(P.x, P.y, cv1)

        exp = k * Q
        act = cv2.ec_mult(k, P)

        if not test_equals(act, exp):
            print(get_err(P, k, cv2, exp, act))
            return False

    # test scalar multiplication
    for _ in range(5):
        P = cv2.gen_point()
        k1 = random.randint(1, cv2.p - 1)
        k2 = random.randint(1, cv2.p - 1)

        exp = cv2.ec_mult(k2, cv2.ec_mult(k1, P))
        act = cv2.ec_mult(k1 * k2, P)

        if exp != act:
            print(get_err(P, k1 * k2, cv2, exp, act))
            return False
    
    # test distribution
    for _ in range(5):
        P = cv2.gen_point()
        k1 = random.randint(1, cv2.p - 1)
        k2 = random.randint(1, cv2.p - 1)

        exp = cv2.ec_add(cv2.ec_mult(k1, P), cv2.ec_mult(k2, P))
        act = cv2.ec_mult(k1 + k2, P)

        if exp != act:
            print(get_err(P, k1 * k2, cv2, exp, act))
            return False

    return True

def test_ecdsa_signature():
    ''' tests ecdsa signature algorithm '''    
    random.seed(1)
    cv = ec.EllipticCurve()
    ecdsa = ec.ECDSA(cv)
    skey, pkey = cv.ec_keygen()

    get_err = lambda m, e, a : f'Error when verifying message {m}. Expected {e} but got {a}'

    for _ in range(10):
        # get random 'hash'
        m = int.from_bytes(random.randbytes(64), byteorder='little')

        signature = ecdsa.ec_sign(m, skey)

        if not ecdsa.ec_verify(signature, m, pkey):
            print(get_err(m, True, False))
            return False
        
    return True

def run_tests(tests: callable = [test_ec_add, test_ec_mult, test_ecdsa_signature]):
    ''' runs all test suites '''
    get_test_status = lambda x : '[PASS]' if x else '[FAIL]'
    for test in tests:
        res = test()
        print(f'{getattr(test, "__name__", repr(test))}: {get_test_status(res)}')

run_tests()
