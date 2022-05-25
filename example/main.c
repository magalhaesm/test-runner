#include "../test_runner.h"
#include <string.h>

void	test_func_strcmp(void)
{
	char	*test1 = "palavra";
	char	*test2 = "palavra1";

	ASSERT_EXPR(strcmp(test1, test2) == 0);
}

int main() {
	t_unit_test tests[] = {
		UNIT_TEST(test_func_strcmp),
	};
	RUN_GROUP(tests);
}
