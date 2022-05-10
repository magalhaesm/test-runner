#include "test_runner.h"
#include <stdio.h>

int         g_test_failed;
int         g_test_assert;
int         g_assert_twice;

void setup(void)
{
	g_test_failed = 0;
	g_test_assert = 0;
	g_assert_twice = 0;
}

void test_assert(int condition)
{
	g_test_assert += 1;
	if (g_test_assert != 1)
		g_assert_twice = 1;
	else if (!condition)
		g_test_failed = 1;
}

void test_runner(void (*func)(void), const char *funcname, const char *filename, int line)
{
	setup();
	func();
	display_result(funcname, filename, line);
}

void display_pass(const char *funcname)
{
	printf("[ %s ] %s", GREEN("PASSED"), funcname);
}

void display_fail(const char *funcname, const char *filename, int line)
{
	printf("[ %s ] %s", RED("FAILED"), funcname);
	printf("\n[  %s  ] --- %s:%d", YELLOW("LINE"), filename, line);
}

void display_result(const char *funcname, const char *filename, int line)
{
	if (!g_test_assert || g_assert_twice || g_test_failed)
		display_fail(funcname, filename, line);
	else
		display_pass(funcname);
	printf("\n");
}
