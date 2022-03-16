import random
from mod_p import *

def test_barrett_r():
    random.seed(1)

    p = prime0
    mod_t = mod_init(p, 1)

    for _ in range(100):
        m = random.randint(1, 12)
        n = random.randint(1, 12)
        if not mod_mult(m, n, p, mod_t) == m * n % p:
            return False
    
    return True

def test_mod_exp():
    random.seed(1)

    p = prime0
    mod_t = mod_init(p, 1)

    for _ in range(100):
        x = random.randint(1, 12)
        e = random.randint(1, 5)
        if not mod_exp(x, e, mod_t) == x ** e % p:
            print(x, e, mod_mult(x, e, mod_t), x ** e % p)
            return False
    
    return True
