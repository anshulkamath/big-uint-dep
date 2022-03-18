''' helpers for ecdsa tester '''

import random
import sys
import os

# adding ./scripts to the current path
current = os.path.dirname(os.path.realpath(__file__))
parent = os.path.dirname(current)
sys.path.append(parent)

# setting random seed
random.seed(1)

import ecdsa as ec

def check_euler_criterion(x: int, p: int) -> bool:
    ''' checks Euler's criterion; x^{(p-1)/2} = 1 (mod p) '''
    return pow(x, (p - 1) // 2, p) == 1

def get_val(x: int, cv: ec.Curve) -> ec.Coord:
    ''' takes in an x and returns the square of a point on the curve '''
    y_sq = (x ** 3 + cv.a * x + cv.b) % cv.p

    return y_sq

def on_curve(p: ec.Coord, cv: ec.Curve, mod_t: list) -> bool:
    ''' takes in a point and a curve and returns true iff the point is on the curve '''
    x, y = p.x, p.y
    rhs = ec.mod.mod_exp(y, 2, mod_t)
    lhs = get_val(x, cv) % cv.p

    return rhs == lhs

def gen_point(cv: ec.Curve) -> ec.Coord:
    ''' generates a random point on the elliptic curve using Tonelli-Shanks algorithm '''
    y = None

    # iterate until we get a solution
    while not y:
        # generate an x coordinate
        x = random.randint(1, cv.p - 1)
        
        # find the square of our y-coordinate
        y_sq = get_val(x, cv)

        # find the modular inverse of y
        y = tonelli_shanks(y_sq, cv.p)

    return ec.Coord(x, y)

def tonelli_shanks(n: int, p: int) -> ec.Coord:
    '''
    takes in an `n` and some prime `p` and finds the integer r in F_p where
    r^2 = n (mod p) using the Tonelli-Shanks algorithm.
    If no such r exists, returns None.
    '''
    # simple cases
    if check_euler_criterion(n, p) != 1:
        return 0
    elif n == 0:
        return 0
    elif p == 2:
        return p
    elif p % 4 == 3:
        return pow(n, (p + 1) // 4, p)
    
    # find Q and S such that `p - 1 = Q * 2^S`
    s = 0
    while ((p - 1) >> s & 1 == 0): s += 1
    q = (p - 1) // (1 << s)

    # make sure that other factor is odd (should be maintained by termination condition)
    assert(q % 2 == 1)

    # find the square root of n
    x = 2
    while (check_euler_criterion(x, p)):
        x += 1

    x = pow(n, (q + 1) // 2, p)
    b = pow(n, q, p)
    g = pow(x, q, p)
    r = s

    while True:
        t = b
        m = 0

        for m in range(r):
            # no solution exists
            if t == 1:
                break
            t = pow(t, 2, p)
        
        if m == 0:
            return random.choice([x, p - x])
        
        gs = pow(g, 1 << (r - m - 1), p)
        g = (gs * gs) % p
        x = (x * gs) % p
        b = (b * g) % p
        r = m

def tonnelli_shanks_test():
    for _ in range(100):
        n = random.randint(1, ec.p - 1)
        r = tonelli_shanks(n, ec.p)
        if not r: continue
        does_pass = (r * r % ec.p) == n
        print(f'n = {hex(n)},\tp = {hex(ec.p)}: {"[PASS]" if does_pass else "[FAIL]"}')
