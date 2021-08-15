''' this file contains the rudimentary python scripts to test and implement the big int gcd functions '''
import random

test_file = './generated_tests.c'

def gcd(a, b, trace=False, stack=False):
    ''' returns gcd(a, b) using Euclid's Division Algorithm '''
    if a == b:
        return a
    
    a, b = max(a, b), min(a, b) # standardize so that a > b

    if stack:
        stack = []
    
    if trace:
        print(f'a = {a}; b = {b}')
    
    while b:
        quotient, remainder = a // b, a % b

        if stack != False:
            stack.append((a, b, quotient, remainder))

        if trace:
            print(f'{a} = {b} * ({quotient}) + {remainder}')

        a, b = b, remainder

    if stack:
        return a, stack
    
    return a

def gcd_extended(a, b, trace=False):
    '''
    returns the values x, y such that ax + by = gcd(a, b)
    '''
    is_a_larger = a > b
    d, stack = gcd(a, b, trace, stack=True)

    if trace:
        print()
    
    # get rid of the last element (only confirms gcd)
    stack.pop()

    # initialize variables
    a, b, quotient, _ = stack.pop()
    x, y = 1, -quotient

    while stack:
        if trace:
            print(f'{d} = {x} * {a} + {y} * {b}')
        
        a, b, quotient, _ = stack.pop()
        x -= y * quotient
        x, y = y, x
    
    # print final results if we are tracing
    if trace:
        print(f'{d} = {x} * {a} + {y} * {b}')

    # if a > b, then x and y are flipped (since moves a > b)
    return (x, y) if is_a_larger else (y, x)

# Optimized functions (recursively created)

def gcd_helper(a, b, trace=False):
    if a % b == 0:
        return b
    
    if trace:
        print(f'{a} = {b} * ({a // b}) + {a % b}')
    
    return gcd_helper(b, a % b, trace)

def gcd_recursive(a, b, trace=False):
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

def gcd_extended_recursive(a, b, trace=False):
    a, b = max(a, b), min(a, b)

    return gcd_extended_helper(a, b, trace)
