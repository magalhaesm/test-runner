#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

# define BOLD(string)			"\033[1m" string "\033[0m"
# define BG_RED(string)			"\033[7;31m" string "\033[0m"
# define FG_RED(string)			"\033[1;31m" string "\033[0m"
# define BG_GREEN(string)		"\033[7;32m" string "\033[0m"
# define FG_GREEN(string)		"\033[1;32m" string "\033[0m"

# define TEST_FAIL				BG_RED(" FAILED ")
# define TEST_PASS				BG_GREEN(" PASSED ")

# define FAIL_SIGN				FG_RED("")
# define PASS_SIGN				FG_GREEN("✓")

# define run_group(tests)		run_units(tests, sizeof(tests)/sizeof(tests[0]), __FILE__)
# define unit_test(function)	{.func=function, .name=#function}
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
	bool		has_entry_point;
}				t_test;

void	init_tests(void);
void	test_assert(int condition, int line);
void	test_runner(t_unit_test *new_test);
bool	run_units(t_unit_test tests[], int num_tests, char *filename);

#endif
