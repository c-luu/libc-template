#include <stdio.h>
#include <string.h>
#include <check.h>
#include "example.h"

START_TEST (test_init) {
    fail_if(1 == 0, "create a test");
}
END_TEST

Suite* buffinfo_suite (void) {
	Suite *suite = suite_create("example");

	TCase *setup = tcase_create("setup");
	tcase_add_test(setup, test_init);

	suite_add_tcase(suite, setup);

	return suite;
}

int main (int argc, char *argv[]) {
	int number_failed;
	Suite *suite = buffinfo_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_NORMAL);
	number_failed = srunner_ntests_failed(runner);
	srunner_free(runner);

	return number_failed;
}