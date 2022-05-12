#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H

# define RED(string)		"\033[1;31m" string "\033[0m"
# define GREEN(string)		"\033[1;32m" string "\033[0m"
# define BOLD(string)		"\033[1m" string "\033[0m"

# define TEST_FAIL_MSG		RED("FAILED")
# define TEST_PASS_MSG		GREEN("PASSED")

# define RUN(func)			test_runner(func, #func)
# define BEGIN()			test_begin(__FILE__)
# define END()				test_end()
# define ASSERT(condition)	test_assert(condition, __LINE__)

typedef struct	s_test
{
	const char	*funcname;
	const char	*filename;
	int			line;
	int			failed;
	int			total;
	int			failures;
}				t_test;

void test_begin(const char *filename);
int test_end(void);
void test_assert(int condition, int line);
void test_runner(void (*func)(void), const char *funcname);
void display_func(const char *message);
void display_diagnostics(void);
void display_result(void);

#endif
