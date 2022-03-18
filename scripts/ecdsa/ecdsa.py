''' implementation for elliptic curve diffie hellman key exchange algorithm '''
''' 
    elliptic curve given by:
        { (x, y) \in F_q^2 | y^2 = x^3 + ax + b mod q, 4a^3 + 27b^2 != 0 }
    
    curve parameters are given below:
        p = 0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f
        a = 0x0
        b = 0x7
        x = 0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798
        y = 0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8
        n = 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141
'''
import random
import sys
import os

# adding ./scripts to the current path
current = os.path.dirname(os.path.realpath(__file__))
parent = os.path.dirname(current)
sys.path.append(parent)

# setting random seed
random.seed(1)

import mod_p.mod as mod

# constants
p = 0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f
a = 0x0
b = 0x7
x = 0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798
y = 0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8
n = 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141

class Coord:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def __repr__(self):
        return f'({hex(self.x)} , {hex(self.y)})'

class Curve:
    def __init__(self, p = p, n = n, a = a, b = b):
        ''' initializes an instance of a (Weierstrauss) curve '''
        self.p = p
        self.n = n
        self.a = a
        self.b = b

    def __repr__(self):
        return f'Curve with p = {hex(p)}, n = {hex(n)}, a = {hex(a)}, and b = {hex(b)}'
    
    def is_on_curve(self, p: Coord) -> bool:
        ''' returns true if and only if p is on the curve '''
        rhs = p.y * p.y % self.p
        lhs = (p.x ** 3 + self.a * p.x + self.b) % self.p

        return rhs == lhs

def ec_add(p1: Coord, p2: Coord, cv: Curve, mod_t: list) -> Coord:
    ''' adds two points on an elliptic curve together '''
    x1, y1 = p1.x, p1.y
    x2, y2 = p2.x, p2.y

    # if either p1 or p2 is 0, return the other
    if (x1 == 0 and y1 == 0):
        return p2
    
    if (x2 == 0 and y2 == 0):
        return p1
    
    # if p1 and p2 share the same x but have opposite ys,
    # then they are additive inverses.
    if x1 == x2 and (y1 == -y2):
        return Coord(0, 0)

    # if they are the same point, use tangent line instead
    if (x1 == x2) and (y1 == y2):
        lamb = mod.mod_div((3 * x1 * x1 + cv.a), (2 * y1), mod_t)
    
    # if p1 and p2 are distinct
    else:
        lamb = mod.mod_div((y2 - y1), (x2 - x1), mod_t)

    x3 = (lamb * lamb - x1 - x2) % cv.p
    y3 = (lamb * (x1 - x3) - y1) % cv.p

    return Coord(x3, y3)

def ec_mult(p: Coord, k: int, cv: Curve, mod_t: list) -> Coord:
    ''' multiplies a point `p` on curve `cv` `k` times '''
    # calculate log_2(k)
    bits = 0
    while (k >> bits): bits += 1
    bits -= 1

    res = Coord(0, 0)
    while bits >= 0:
        res = ec_add(res, res, cv, mod_t)
        if ((k >> bits) & 1):
            res = ec_add(res, p, cv, mod_t)

        bits -= 1

    return res
