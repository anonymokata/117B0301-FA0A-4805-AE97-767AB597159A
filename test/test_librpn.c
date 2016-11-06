#include "../librpn.h"

#include <check.h>


START_TEST(aplusb_yieldsabplus)
{
    ck_assert_str_eq(infix_to_rpn("a+b"), "ab+");
}
END_TEST

TCase *tcase_without_parens(void)
{
	TCase *tc;

	tc = tcase_create("without-parens");
	tcase_add_test(tc, aplusb_yieldsabplus);

	return tc;
}

Suite *suite_rpn(void)
{
	Suite *s;

	s = suite_create("infix-to-rpn");

	suite_add_tcase(s, tcase_without_parens
());

	return s;
}

int main(int argc, char **argv)
{
	Suite *s;
	SRunner *runner;
	int number_fails;

	rpn_init();

	s = suite_rpn();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	number_fails = srunner_ntests_failed(runner);
	srunner_free(runner);

	rpn_release();

	return number_fails;
}
