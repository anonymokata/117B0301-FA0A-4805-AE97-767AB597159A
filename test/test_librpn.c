#include <check.h>
#include <stdlib.h>

#include "../librpn.h"
#include "test_sstack.h"
#include "test_stack.h"

#define BUFFER_LENGTH 256

struct test_value {
  const char *infix;
  const char *rpn;
};

struct test_value cases[] = {{"a+b", "ab+"},
                             {"i+j", "ij+"},
                             {"c-d", "cd-"},
                             {"a+b-c", "abc-+"},
                             {"a-b+c", "ab-c+"},
                             {"a^b^c", "ab^c^"},
                             {"a*b/c", "abc/*"},
                             {"a/b*c", "ab/c*"},
                             {"(a+b)*c", "ab+c*"},
                             {"(a+b)^(c*d)", "ab+cd*^"},
                             {"((a+b)*c)/d", "ab+c*d/"},
                             {"(c*(a+b))/(d+e)", "cab+*de+/"},
                             {"l/m^n*o-p", "lmn^/o*p-"},
                             {"(v/w)^x*(y-z)", "vw/x^yz-*"}};

START_TEST(convert_infix_to_rpn) {
  static char infix[BUFFER_LENGTH];
  memset(infix, 0, BUFFER_LENGTH);
  strncpy(infix, cases[_i].infix, BUFFER_LENGTH - 1);
  const char *expected = cases[_i].rpn;
  ck_assert_str_eq(infix_to_rpn(infix), expected);
}
END_TEST

START_TEST(convert_rpn_to_infix) {
  char *actual;
  const char *expected;

  actual = rpn_to_infix(cases[_i].rpn);
  expected = cases[_i].infix;
  ck_assert_str_eq(actual, expected);
}
END_TEST

TCase *tcase_conversions(void) {
  TCase *tc;
  int num_cases = sizeof(cases) / sizeof(struct test_value);

  tc = tcase_create("conversions");
  tcase_add_loop_test(tc, convert_infix_to_rpn, 0, num_cases);
  tcase_add_loop_test(tc, convert_rpn_to_infix, 0, num_cases);

  return tc;
}

Suite *suite_rpn(void) {
  Suite *s;

  s = suite_create("infix-to-rpn");

  suite_add_tcase(s, tcase_conversions());

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
