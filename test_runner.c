#include "test_runner.h"
#include <stdio.h>

t_test	g_test;

void test_assert(int condition, int line)
{
	if (!condition)
	{
		g_test.line = line;
		g_test.failed = 1;
		g_test.failures += 1;
	}
}

void test_begin(const char *filename)
{
	g_test.filename = filename;
	g_test.failures = 0;
	g_test.total = 0;
	printf("[==========] Running tests for %s\n", filename);
}

int test_end(void)
{
	printf("[==========]\n");
	printf("Tests: %d", g_test.total - g_test.failures);
	printf("\tFailures: %d\n", g_test.failures);
	if (g_test.failures)
		return (1);
	else
		return (0);
}

void test_runner(void (*func)(void), const char *funcname)
{
	g_test.funcname = funcname;
	g_test.failed = 0;
	g_test.total += 1;

	func();
	display_result();
}

void display_func(const char *message)
{
	printf("[  %s  ] %s", message, g_test.funcname);
}

void display_diagnostics()
{
	printf(" in %s:%d", g_test.filename, g_test.line);
}

void display_result(void)
{
	if (g_test.failed)
	{
		display_func(TEST_FAIL_MSG);
		display_diagnostics();
	}
	else
		display_func(TEST_PASS_MSG);
	printf("\n");
}
