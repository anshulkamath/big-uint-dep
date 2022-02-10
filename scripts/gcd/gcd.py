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

def generate_test_case(ind, num_digits = 1, num_bytes_a=1, num_bytes_b=1, a=None, b=None):
    if num_digits < num_bytes_a or num_digits < num_bytes_b:
        raise Exception('Cannot have num_digits < num_bytes')
    
    if not a:
        a = random.randint(0, 1 << 32 * num_bytes_a)
    if not b:
        b = random.randint(0, 1 << 32 * num_bytes_b)

    def format_int(num):
        hex_repr = hex(num)[2:]
        expected_len = num_digits * 8

        if len(hex_repr) < expected_len:
            hex_repr = (expected_len - len(hex_repr)) * '0' + hex_repr

        ret_str = ''
        for i in range(num_digits):
            ret_str += '0x' + hex_repr[i * 8:(i + 1) * 8] + ', '

        return ret_str[:-2]

    x, y = gcd_extended(a, b)
    x %= 1 << 32 * num_digits # make sure that x is unsigned
    y %= 1 << 32 * num_digits # make sure that y is unsigned

    with open(test_file, 'a', newline='') as out:
        out.write(f'\tconst uint32_t a{ind}[] = {{ {format_int(a)} }};\n')
        out.write(f'\tconst uint32_t b{ind}[] = {{ {format_int(b)} }};\n')
        out.write(f'\tconst uint32_t expected_x{ind}[] = {{ {format_int(x)} }};\n')
        out.write(f'\tconst uint32_t expected_y{ind}[] = {{ {format_int(y)} }};\n')
        out.write('\n')
        out.write(f'\tbig_uint_gcd_extended(result_x, result_y, a{ind}, b{ind}, {num_digits});\n')
        out.write('\n')
        out.write(f'\texpect(tester, big_uint_equals(expected_x{ind}, result_x, {num_digits}));\n')
        out.write(f'\texpect(tester, big_uint_equals(expected_y{ind}, result_y, {num_digits}));\n')
        out.write('\n')

def create_test():
    test_creator = tests.test_creator(
        test_file,
        'big_uint_gcd_extended',
        results=['result_x', 'result_y']
    )
    indexer = tests.create_indexer()

    next(test_creator)

    generate_test_case(next(indexer), 1, 1, a=143, b=234)
    generate_test_case(next(indexer), 1, 1, 1)
    generate_test_case(next(indexer), 2, 1, 1)
    generate_test_case(next(indexer), 2, 2, 2)
    generate_test_case(next(indexer), 2, 1, 2)
    generate_test_case(next(indexer), 2, 2, 1)
    generate_test_case(next(indexer), 3, 3, 3)
    generate_test_case(next(indexer), 3, 3, 3)
    generate_test_case(next(indexer), 3, 1, 2)
    generate_test_case(next(indexer), 3, 1, 1)

    next(test_creator)

create_test()
