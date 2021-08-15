
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
