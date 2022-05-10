#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H

# define RED(string) "\033[1;31m" string "\033[0m"
# define GREEN(string) "\033[1;32m" string "\033[0m"
# define YELLOW(string) "\033[1;33m" string "\033[0m"
# define BOLD(string) "\033[1m" string "\033[0m"

# define RUN(func) test_runner(func, #func, __FILE__, __LINE__)
# define ASSERT(condition) test_assert(condition)

void setup(void);
void test_assert(int condition);
void test_runner(void (*func)(void), const char *funcname, const char *filename, int line);
void display_result(const char *funcname, const char *filename, int line);
void display_pass(const char *funcname);
void display_fail(const char *funcname, const char *filename, int line);
void assertion_error(void);

#endif
