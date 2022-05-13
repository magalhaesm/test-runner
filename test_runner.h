#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H

# define BOLD(string)			"\033[1m" string "\033[0m"
# define BG_RED(string)			"\033[7;31m" string "\033[0m"
# define FG_RED(string)			"\033[1;31m" string "\033[0m"
# define BG_GREEN(string)		"\033[7;32m" string "\033[0m"
# define FG_GREEN(string)		"\033[1;32m" string "\033[0m"

# define TEST_FAIL_MSG			BG_RED(" FAILED ")
# define TEST_PASS_MSG			BG_GREEN(" PASSED ")

# define FAIL_SYMBOL			FG_RED("  ")
# define PASS_SYMBOL			FG_GREEN(" ✓ ")

# define SIZE_OF_TESTS			sizeof(tests)/sizeof(t_unit_test)

# define run_group(tests)		run_grp(tests, SIZE_OF_TESTS, __FILE__)
# define testing(FUNC)			{.func=FUNC, .name=#FUNC}
# define assert_expr(condition)	test_assert(condition, __LINE__)

typedef struct	s_unit_test
{
	char		*name;
	void		(*func)(void);
	int			line;
	int			failed;
} t_unit_test;

typedef struct	s_test_status
{
	t_unit_test *curr;
	int			total;
	int			failures;
}				t_test;

void	test_assert(int condition, int line);
void	test_runner(t_unit_test *test);
int		run_grp(t_unit_test tests[], int num_tests, char *filename);

#endif
