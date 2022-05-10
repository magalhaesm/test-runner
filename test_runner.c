#include "test_runner.h"
#include <stdio.h>

t_test *g_curr_test;

void test_assert(int condition, int line)
{
	g_curr_test->line = line;
	if (!condition)
		g_curr_test->state.failed = 1;
}

void test_runner(void (*func)(void), const char *funcname, const char *filename)
{
	t_test new_test;

	new_test.funcname = funcname;
	new_test.filename = filename;
	new_test.state.failed = 0;
	g_curr_test = &new_test;

	func();
	display_result();
}

void display_pass(void)
{
	printf("[ %s ] %s", GREEN("PASSED"), g_curr_test->funcname);
}

// Expression Evaluated To FALSE
// No ASSERTION Found
void display_fail(void)
{
	printf("[ %s ] %s", RED("FAILED"), g_curr_test->funcname);
	printf(" in %s:%d", g_curr_test->filename, g_curr_test->line);
	printf("%s", RED(" Expression Evaluated To FALSE"));
}

void display_result(void)
{
	if (g_curr_test->state.failed)
		display_fail();
	else
		display_pass();
	printf("\n");
}
