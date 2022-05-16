#include "test_runner.h"
#include <stdio.h>

t_test	g_test;

void	test_assert(int condition, int line)
{
	if (g_test.curr->line)
		return;
	if (!condition)
	{
		g_test.curr->failed = 1;
		g_test.curr->line = line;
		g_test.failures += 1;
	}
}

void	test_runner(t_unit_test *test)
{
	g_test.curr = test;
	g_test.total += 1;
	test->func();
}

void	init_tests(void)
{
	if (!g_test.has_entry_point)
	{
		g_test.has_entry_point = true;
		printf("Running unit tests\n");
	}
}

// TODO: usar setjmp para chamar a função que exibe o diagnóstico
int		run_units(t_unit_test tests[], int num_tests, char *filename)
{
	int		fails;
	int		fail_index[num_tests];

	init_tests();
	fails = 0;
	for (int i = 0; i < num_tests; i++)
	{
		test_runner(&tests[i]);
		if (tests[i].failed)
			fail_index[fails++] = i;
	}
	t_session session = {
		.fails = fails,
		.fail_index = fail_index,
		.tests = tests,
		.num_tests = num_tests,
		.filename = filename,
	};

	print_result(session);
	return 0;
}

void print_fail(t_session s)
{
	char	path[PATH_MAX];
	t_unit_test *test;

	// TODO: tratar possível erro
	realpath(s.filename, path);
	printf("\n%s %s\n", FAILED, path);
	for (int i = 0; i < s.fails; i++)
	{
		test = &s.tests[s.fail_index[i]];
		printf("  %s %s", FAIL_SIGN, test->name);
		printf(" at line %d\n", test->line);
	}
}

void print_pass(t_session s)
{
	printf("\n%s %s\n", PASSED, s.filename);
	for (int i = 0; i < s.num_tests; i++)
	{
		printf("  %s %s\n", PASS_SIGN, s.tests[i].name);
	}
}

void print_result(t_session s)
{
	if (s.fails)
		print_fail(s);
	else
		print_pass(s);
}
