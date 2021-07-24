#ifndef TESTING_H
#define TESTING_H

#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define MAG     "\x1b[35m"
#define YEL     "\x1b[33m"

#define expect(tester, assertion) expect_helper(tester, assertion, __FILE__, __LINE__, #assertion)
#define log_tests(tester) log_tests_helper(tester, __FUNCTION__)

typedef struct testing_logger testing_logger_t;

/**
 * @brief Creates an instance of the testing logger on the heap and resturns it
 * 
 * @return testing_logger_t* The instance of the testing logger that was made
 */
testing_logger_t* init_tester();

/**
 * @brief Checks if an assertion is valid and, if not, logs the first
 *        invalid assertion to the testing_logger struct
 * 
 * @param tester The testing logger structure to hold the new data
 * @param assertion The assertion to verify
 */
void expect_helper(testing_logger_t *tester, int assertion, char* file, int line, char* expr);

/**
 * @brief Prints a summary of whether or not test suite passed
 * 
 * @param tester The testing logger object to print the summary of
 */
void log_tests_helper(testing_logger_t *tester, const char* test_func);

#endif
