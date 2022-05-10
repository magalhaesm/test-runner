#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H

# define RED(string) "\033[1;31m" string "\033[0m"
# define GREEN(string) "\033[1;32m" string "\033[0m"
# define YELLOW(string) "\033[1;33m" string "\033[0m"
# define BOLD(string) "\033[1m" string "\033[0m"

# define RUN(func) test_runner(func, #func, __FILE__)
# define ASSERT(condition) test_assert(condition, __LINE__)

typedef struct	s_test_state
{
	int failed;
}				t_test_state;

typedef struct	s_test
{
	const char *funcname;
	const char *filename;
	int	line;
	t_test_state state;
}				t_test;

void test_assert(int condition, int line);
void test_runner(void (*func)(void), const char *funcname, const char *filename);
void display_result(void);
void display_fail(void);
void display_pass(void);

#endif
