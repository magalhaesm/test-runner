#include "test_runner.h"

t_test	g_test;

void	test_assert(int condition, int line)
{
	if (g_test.curr->line)
		return;
	if (condition == false)
	{
		g_test.curr->failed = true;
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

void	init_tests(const char *funcname, char *filename)
{
	char path[PATH_MAX];

	if (g_test.has_entry_point == false)
	{
		g_test.has_entry_point = true;
		if (g_test.is_unit == false)
		{
			realpath(filename, path);
			printf("Running %s() from %s\n", funcname, path);
		}
		else
			printf("%s\n", BOLD("Running unit tests"));
	}
}

int		run_units(t_unit_test tests[], int num_tests, char *filename)
{
	int		fails;
	int		fail_index[num_tests];

	g_test.is_unit = true;
	BEGIN();
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
	t_unit_test *test;

	printf("\n%s %s\n", FAILED, s.filename);
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

