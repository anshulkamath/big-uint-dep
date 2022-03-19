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
from dataclasses import astuple, dataclass

# constants
p = 0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f
a = 0x0
b = 0x7
x = 0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798
y = 0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8
n = 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141

@dataclass
class Coord:
    x: int
    y: int

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    @staticmethod
    def identity():
        ''' returns the identity element '''
        return Coord(0, 0)
    
    @staticmethod
    def is_identity(point):
        ''' returns true if and only if `point` is identity '''
        return point == Coord.identity()


    def __repr__(self):
        return f'({hex(self.x)} , {hex(self.y)})'

    def __iter__(self):
        return iter(astuple(self))

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

class Curve:
    def __init__(self, p = p, n = n, a = a, b = b, G = Coord(x, y), x = -1, y = -1):
        ''' initializes an instance of a (Weierstrauss) curve '''
        if (4 * a ** 3 + 27 * b ** 2) % p == 0:
            raise Exception('Invalid params a and/or b.')
        
        self.p = p  # set prime number for curve
        self.a = a  # set a parameter of curve
        self.b = b  # set b parameter of curve
        self.n = n  # set order of curve 
        
        # set generator point based on available params
        if x > -1 and y > -1:
            self.G = Coord(x, y)
            return
        if not G and (x == -1 or y == -1):
            raise Exception(f'Invalid param: ({x} , {y}) is not a valid generator point.')
        
        self.G = G

    def __repr__(self):
        return f'Curve with\n\tp = {hex(p)},\n\tn = {hex(n)},\n\ta = {hex(a)}, and\n\tb = {hex(b)}'
    
    def is_on_curve(self, p: Coord) -> bool:
        ''' returns true if and only if p is on the curve '''
        rhs = p.y * p.y % self.p
        lhs = (p.x ** 3 + self.a * p.x + self.b) % self.p

        return rhs == lhs

def ec_add(p1: Coord, p2: Coord, cv: Curve) -> Coord:
    ''' adds two points on an elliptic curve together '''
    x1, y1 = p1
    x2, y2 = p2

    # if either p1 or p2 is 0, return the other
    if Coord.is_identity(p1):
        return p2
    
    if Coord.is_identity(p2):
        return p1
    
    # if p1 and p2 share the same x but have opposite ys,
    # then they are additive inverses.
    if x1 == x2 and (y1 == -y2 % cv.p):
        return Coord.identity()

    # if they are the same point, use tangent line instead
    if (x1 == x2) and (y1 == y2):
        lamb = (3 * x1 * x1 + cv.a) * pow(2 * y1, cv.p - 2, cv.p)
    
    # if p1 and p2 are distinct
    else:
        lamb = (y2 - y1) * pow(x2 - x1, cv.p - 2, cv.p) % cv.p

    x3 = (lamb * lamb - x1 - x2) % cv.p
    y3 = (lamb * (x1 - x3) - y1) % cv.p

    return Coord(x3, y3)

def ec_mult(p: Coord, k: int, cv: Curve) -> Coord:
    ''' multiplies a point `p` on curve `cv` `k` times '''
    # calculate log_2(k)
    bits = 0
    while (k >> bits): bits += 1
    bits -= 1

    res = Coord(0, 0)
    while bits >= 0:
        res = ec_add(res, res, cv)
        if ((k >> bits) & 1):
            res = ec_add(res, p, cv)

        bits -= 1

    return res

def ecdsa_keygen(cv: Curve) -> tuple[int, Coord]:
    ''' generates a private and public key using the given curve, respectively '''
    skey = random.randint(1, cv.n - 1)
    return (skey, ec_mult(cv.G, skey, cv))

def ec_sign(m_hash: int, skey: int, cv: Curve) -> Coord:
    ''' takes in a message and signs it using the private key `skey` '''
    # define n
    n = cv.n
    
    # find bit length of our group p
    l_p = cv.p.bit_length()
    l_m = m_hash.bit_length()

    # z = L_p leftmost bits of m_hash
    z = m_hash >> (l_m - l_p)

    r = 0; s = 0
    while not r or not s:
        # find cryptographically secure random number
        k = random.randint(1, n - 1)

        x1, _ = ec_mult(cv.G, k, cv)
        r = x1 % n
        s = pow(k, n - 2, n) * (z + r * skey) % n

    return Coord(r, s)

def ec_verify(signature: Coord, m_hash: int, pkey: Coord, cv: Curve) -> bool:
    ''' returns true if and only if the signature is valid with the given public key '''
    p = cv.p
    n = cv.n

    # verify public key is a valid curve point
    if pkey == Coord.identity():
        return False
    
    if not cv.is_on_curve(pkey):
        return False
    
    if not (ec_mult(pkey, n, cv) == Coord.identity()):
        return False

    # verify signature
    r, s = signature
    if (r < 1 or r > n) or (s < 1 or s > n):
        return False

    # find bit length of our group p
    l_p = p.bit_length()
    l_m = m_hash.bit_length()

    # z = L_p leftmost bits of m_hash
    z = m_hash >> (l_m - l_p)

    s_inv = pow(s, n - 2, n)
    u1 = (z * s_inv) % n
    u2 = (r * s_inv) % n

    x1, y1 = ec_add(ec_mult(cv.G, u1, cv), ec_mult(pkey, u2, cv), cv)

    if Coord(x1, y1) == Coord.identity():
        return False
    
    return r == mod.mod_p(x1, n)
