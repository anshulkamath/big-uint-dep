test_file = ''

def create_indexer():
    ''' generator to maintain index '''
    i = 1
    while True:
        yield i
        i += 1

def test_creator(file_name, function_name, results=['result']):
    ''' generator to create and write skeleton of test '''
    global test_file
    test_file = file_name

    # create a new file for the generated test output
    with open(test_file, 'w+', newline='') as out:
        out.write(f'void test_{function_name}() {{\n')
        out.write('\ttesting_logger_t *tester = create_tester();\n')
        for result in results:
            out.write(f'\tuint32_t {result}[5] = {{ 0 }};\n')
        out.write('\n')

    yield

    with open(test_file, 'a', newline='') as out:
        out.write('\tlog_tests(tester);\n')
        out.write('}\n')

    yield
