
#include "../librpn.h"
#include "test_stack.h"
#include <check.h>

#define BUFFER_LENGTH 256

struct test_value {
  const char *source;
  const char *expected;
};

struct test_value cases[] = {{"a+b", "ab+"},     {"i+j", "ij+"},
                             {"c-d", "cd-"},     {"a+b-c", "abc-+"},
                             {"a-b+c", "ab-c+"}, {"a^b^c", "ab^c^"},
                             {"a*b/c", "abc/*"}, {"a/b*c", "ab/c*"}};

START_TEST(simple_values) {
  static char source[BUFFER_LENGTH];
  memset(source, 0, BUFFER_LENGTH);
  strncpy(source, cases[_i].source, BUFFER_LENGTH - 1);
  const char *expected = cases[_i].expected;
  ck_assert_str_eq(infix_to_rpn(source), expected);
}
END_TEST

TCase *tcase_without_parens(void) {
  TCase *tc;
  int num_cases = sizeof(cases) / sizeof(struct test_value);

  tc = tcase_create("without-parens");
  tcase_add_loop_test(tc, simple_values, 0, num_cases);

  return tc;
}

Suite *suite_rpn(void) {
  Suite *s;

  s = suite_create("infix-to-rpn");

  suite_add_tcase(s, tcase_without_parens());

  return s;
}

int main(int argc, char **argv) {
  Suite *s;
  Suite *stacksuite;
  SRunner *runner;
  int number_fails;

  s = suite_rpn();
  stacksuite = suite_stack();
  runner = srunner_create(s);
  srunner_add_suite(runner, stacksuite);
  srunner_run_all(runner, CK_NORMAL);
  number_fails = srunner_ntests_failed(runner);
  srunner_free(runner);

  return number_fails;
}
