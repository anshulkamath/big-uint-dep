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

I = Coord(0, 0)
G = Coord(x, y)

class EllipticCurve:
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

    def ec_add(self, p1: Coord, p2: Coord) -> Coord:
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
        if x1 == x2 and (y1 == -y2 % self.p):
            return Coord.identity()

        # if they are the same point, use tangent line instead
        if (x1 == x2) and (y1 == y2):
            lamb = (3 * x1 * x1 + self.a) * pow(2 * y1, self.p - 2, self.p)
        
        # if p1 and p2 are distinct
        else:
            lamb = (y2 - y1) * pow(x2 - x1, self.p - 2, self.p) % self.p

        x3 = (lamb * lamb - x1 - x2) % self.p
        y3 = (lamb * (x1 - x3) - y1) % self.p

        return Coord(x3, y3)

    def ec_mult(self, k: int, p: Coord) -> Coord:
        ''' multiplies point `p` on the elliptic curve by k '''
        # calculate log_2(k)
        bits = k.bit_length()

        res = Coord(0, 0)
        while bits >= 0:
            res = self.ec_add(res, res)
            if ((k >> bits) & 1):
                res = self.ec_add(res, p)

            bits -= 1

        return res

    def ec_keygen(self) -> tuple[int, Coord]:
        ''' generates a private and public key using the given curve, respectively '''
        skey = random.randint(1, self.n - 1)
        return (skey, self.ec_mult(skey, self.G))

    def gen_point(self) -> Coord:
        ''' generates a random point on the elliptic curve using Tonelli-Shanks algorithm '''
        y = None

        # iterate until we get a solution
        while not y:
            # generate an x coordinate
            x = random.randint(1, self.p - 1)
            
            # find the square of our y-coordinate
            y_sq = self._get_sq_val(x)

            # find the modular inverse of y
            y = mod.mod_sqrt(y_sq, self.p)

        return Coord(x, y)
    
    def _get_sq_val(self, x: int) -> Coord:
        ''' takes in an x and returns the square of a point on the curve '''
        y_sq = (x ** 3 + self.a * x + self.b) % self.p

        return y_sq

class ECDSA:
    def __init__(self, cv: EllipticCurve):
        self.cv = cv
    
    def ec_sign(self, m_hash: int, skey: int) -> Coord:
        ''' takes in a message and signs it using the private key `skey` '''
        cv = self.cv
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

            x1, _ = cv.ec_mult(k, cv.G)
            r = x1 % n
            s = pow(k, n - 2, n) * (z + r * skey) % n

        return Coord(r, s)

    def ec_verify(self, signature: Coord, m_hash: int, pkey: Coord) -> bool:
        ''' returns true if and only if the signature is valid with the given public key '''
        cv = self.cv
        p: int = cv.p
        n: int = cv.n

        # verify public key is a valid curve point
        if pkey == Coord.identity():
            return False
        
        if not cv.is_on_curve(pkey):
            return False
        
        if not (cv.ec_mult(n, pkey) == Coord.identity()):
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

        x1, y1 = cv.ec_add(cv.ec_mult(u1, cv.G), cv.ec_mult(u2, pkey))

        if Coord(x1, y1) == Coord.identity():
            return False
        
        return r == x1 % n 
