import math
import random

test_file = ''
func_names = []

def generate_random_number(num_digits):
    ''' generates a random number with the given number of digits '''
    return random.randint(0, 1 << (32 * num_digits))

def get_num_digits(n):
    ''' takes in an integer n and returns the number of 32-bit digits in n '''
    return math.ceil(len(hex(n)[2:]) / 8)

def format_int(num, num_digits):
    ''' formats the given number into a C initializer list '''
    hex_repr = hex(num)[2:]
    expected_len = num_digits * 8

    if len(hex_repr) < expected_len:
        hex_repr = (expected_len - len(hex_repr)) * '0' + hex_repr

    ret_str = ''
    for i in range(num_digits):
        ret_str += '0x' + hex_repr[i * 8:(i + 1) * 8] + ', '

    return f'{{ {ret_str[:-2]} }}'

def format_point(num, num_digits=8):
    ''' formats the given big point into a C initializer list '''
    hex_repr = hex(num)[2:]
    expected_len = 8 * num_digits

    if len(hex_repr) < expected_len:
        hex_repr = (expected_len - len(hex_repr)) * '0' + hex_repr

    ret_str = '{\n\t\t'
    for i in range(num_digits):
        if i > 0 and i % 4 == 0:
            ret_str += '\n\t\t'
        ret_str += '0x' + hex_repr[i * 8:(i + 1) * 8] + ', '

    return f'{ret_str[:-2]}\n\t}}'

def create_indexer():
    ''' generator to maintain index '''
    i = 1
    while True:
        yield i
        i += 1

def initialize_test(file_name, libs):
    ''' creates a new file to hold all tests '''
    with open(file_name, 'w+', newline='') as out:
        for lib in libs:
            out.write(f'#include {lib}\n')
        
        out.write('\n')

def test_creator(file_name, function_name, types=['uint32_t'], results=['result'], args=[]):
    ''' generator to create and write skeleton of test '''
    func_names.append(f'test_{function_name}')

    with open(file_name, 'a', newline='') as out:
        out.write(f'void {func_names[-1]}({", ".join(args)}) {{\n')
        out.write('\ttesting_logger_t *tester = create_tester();\n')
        for type, result in zip(types, results):
            if type == 'uint32_t':
                out.write(f'\t{type} {result}[8] = {{ 0 }};\n')
            else:
                out.write(f'\t{type} {result};\n')
        out.write('\n')

    yield

    with open(file_name, 'a', newline='') as out:
        out.write('\tlog_tests(tester);\n')
        out.write('}\n\n')

    yield

def test_closer(file_name):
    ''' generator that creates the main function to call all tests '''
    with open(file_name, 'a', newline='') as out:
        out.write(f'int main() {{\n')
        out.write(f'\t// Calling all tests:\n')
        for func in func_names:
            out.write(f'\t{func}();\n')
        
        out.write('\n\treturn 1;\n')
        out.write('}\n')
