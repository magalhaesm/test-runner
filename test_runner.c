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

void	test_runner(t_unit_test test)
{
	g_test.curr = &test;
	g_test.total += 1;

	test.func();
}

int		run_grp(t_unit_test tests[], int num_tests, char *filename)
{
	int fails = 0;
	int fail_index[num_tests];

	for (int i = 0; i < num_tests; i++)
	{
		test_runner(tests[i]);
		if (g_test.curr->failed)
			fail_index[fails++] = i;
	}
	// BUG: não exibe a linha de erro
	if (fails)
	{
		printf("%s %s\n", TEST_FAIL_MSG, filename);
		for (int i = 0; i < fails; i++)
		{
			printf(" %s %s", FAIL_SYMBOL, tests[fail_index[i]].name);
			printf(" at line %d\n", tests[fail_index[i]].line);
		}
	}
	else
	{
		printf("%s %s\n", TEST_PASS_MSG, filename);
		for (int i = 0; i < num_tests; i++)
		{
			printf(" %s %s\n", PASS_SYMBOL, tests[i].name);
		}
	}
	return 0;
}
