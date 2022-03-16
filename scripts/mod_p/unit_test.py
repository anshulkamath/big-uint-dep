import random
from mod import *

def test_barrett_r():
    random.seed(1)

    for p in [prime0, prime1, prime2]:
        mod_t = mod_init(p, 2)

        for _ in range(1000):
            m = random.randint(1, p - 1)
            n = random.randint(1, p - 1)

            expected = m * n % p
            actual = mod_mult(m, n, mod_t)

            if not actual == expected:
                print(m, n, expected, actual)
                print()
                return False
    
    return True

def test_mod_exp():
    random.seed(1)

    for p in [prime0, prime1, prime2]:
        mod_t = mod_init(p, 2)

        for _ in range(1000):
            x = random.randint(1, p - 1)
            e = random.randint(1, 100)

            expected = x ** e % p
            actual = mod_exp(x, e, mod_t)

            if not mod_exp(x, e, mod_t) == expected:
                print(x, e, expected, actual)
                print()
                return False
    
    return True

def test_mod_inv():
    random.seed(1)
    
    for p in [prime0, prime1, prime2]:
        for _ in range(1000):
            x = random.randint(1, p - 1)
            
            expected = pow(x, -1, p)
            actual = mod_inv(x, mod_init(p, 2))
            
            if not actual == expected:
                print(x, p, expected, actual)
                print()
                return False
            
    return True

def test_mod_div():
    random.seed(1)

    for p in [prime0, prime1, prime2]:
        for _ in range(1000):
            m = random.randint(1, p - 1)
            n = random.randint(1, p - 1)

            expected = pow(n, -1, p) * m % p
            actual = mod_div(m, n, mod_init(p, 2))

            if not actual == expected:
                print(m, n, p, expected, actual)
                print()
                return False
    
    return True

def run_tests(tests: callable = [test_barrett_r, test_mod_exp, test_mod_inv, test_mod_div]):
    get_test_status = lambda x : '[PASS]' if x else '[FAIL]'
    for test in tests:
        res = test()
        print(f'{getattr(test, "__name__", repr(test))}: {get_test_status(res)}')

run_tests()