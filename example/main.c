#include "../test_runner.h"
#include <string.h>

void	tests_function_that_passes(void)
{
	char	*test1 = "mesma palavra";
	char	*test2 = "mesma palavra";

	ASSERT_EXPR(strcmp(test1, test2) == 0);
}

int main() {
	t_unit_test tests[] = {
		UNIT_TEST(tests_function_that_passes),
	};
	RUN_GROUP(tests);
}
