#include "test_runner.h"

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

void	init_tests()
{
	if (!g_test.has_entry_point)
	{
		g_test.has_entry_point = true;
		printf("Running unit tests\n");
	}
}

bool	run_units(t_unit_test tests[], int num_tests, char *filename)
{
	init_tests();
	int fails = 0;
	int fail_index[num_tests];

	for (int i = 0; i < num_tests; i++)
	{
		test_runner(&tests[i]);
		if (g_test.curr->failed)
			fail_index[fails++] = i;
	}
	if (fails)
	{
		printf("\n%s %s\n", TEST_FAIL, realpath(filename, NULL));
		for (int i = 0; i < fails; i++)
		{
			printf(" %s %s", FAIL_SIGN, tests[fail_index[i]].name);
			printf(" at line %d\n", tests[fail_index[i]].line);
		}
	}
	else
	{
		printf("\n%s %s\n", TEST_PASS, filename);
		for (int i = 0; i < num_tests; i++)
		{
			printf(" %s %s\n", PASS_SIGN, tests[i].name);
		}
	}
	return 0;
}
