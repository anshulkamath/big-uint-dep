''' this file contains the rudimentary python scripts to test and implement the big int gcd functions '''
import random
import test_generator as tests

test_file = './scripts/test-bezout.c'

def gcd_helper(a, b, trace=False):
    if a % b == 0:
        return b
    
    if trace:
        print(f'{a} = {b} * ({a // b}) + {a % b}')
    
    return gcd_helper(b, a % b, trace)

def gcd(a, b, trace=False):
    a, b = max(a, b), min(a, b)

    return gcd_helper(a, b, trace)

def gcd_extended_helper(a, b, trace=False):
    # when the remainder is 0, we can start unraveling the stack
    if a % b == 0:
        return 0, 1

    quotient = a // b
    # get the x, y values from the successive division
    x, y = gcd_extended_helper(b, a % b, trace)

    # subtract the coefficient for 'a' successive division
    # NOTE: the successive division has the form (c - a * quotient),
    #       where c is some other number
    x -= y * quotient

    if trace:
        print(f'{a} = {b} * {quotient} + {a % b}')
    
    # swap x and y for the previous division
    return y, x

def gcd_extended(a, b, trace=False):
    a, b = max(a, b), min(a, b)

    return gcd_extended_helper(a, b, trace)
