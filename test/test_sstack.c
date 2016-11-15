#include <stdio.h>
#include <stdlib.h>

#include "../stringstack.h"

#include "test_sstack.h"

static void setup() { ss_init(); }

static void teardown() { ss_release(); }

#define ALICE "Alice"
#define BOB "Bob"
#define ZED "Zed"

START_TEST(pushedString_whenPopped_returnsString) {
  ss_push(ALICE);
  ck_assert_str_eq(ss_pop(), ALICE);
}
END_TEST

START_TEST(twoPushedStrings_whenPopped_willReturnStringsInReverseOrder) {
  ss_push(ALICE);
  ss_push(BOB);
  ck_assert_str_eq(ss_pop(), BOB);
  ck_assert_str_eq(ss_pop(), ALICE);
}
END_TEST

START_TEST(onePushedString_withTwoPops_willReturnStackUnderflow) {
  ss_push(ZED);
  ck_assert_str_eq(ss_pop(), ZED);
  ck_assert_ptr_eq(ss_pop(), SS_UNDERFLOW);
}
END_TEST

START_TEST(
    fiveHundredOnePushedStrings_whenPoppedFiveHundredOneTimes_willReturnStackUnderflowOnTheFiftyFirstPop) {
  int i;
  ss_push(ZED);
  for (i = 0; i < 500; ++i) {
    ss_push(ALICE);
  }
  for (i = 0; i < 500; ++i) {
    ss_pop();
  }
  ck_assert_ptr_eq(ss_pop(), SS_UNDERFLOW);
}
END_TEST

START_TEST(stackPeek_withTwoStringsPushed_returnsMostRecentStringPushed) {
  ss_push(ALICE);
  ss_push(BOB);
  ck_assert_str_eq(ss_peek(), BOB);
}
END_TEST

START_TEST(
    stackPeekCalledTwice_withTwoStringsPushed_returnsMostRecentStringPushed) {
  ss_push(ALICE);
  ss_push(BOB);
  ck_assert_str_eq(ss_peek(), BOB);
  ck_assert_str_eq(ss_peek(), BOB);
}
END_TEST

START_TEST(stackPeek_withEmptyStack_returnsStackUnderflow) {
  ck_assert_ptr_eq(ss_peek(), SS_UNDERFLOW);
}
END_TEST

START_TEST(
    stackPopCalledTwiceWithSamePointerButDifferentContents_poppedTwice_returnsTwoDifferentStrings) {
  char name[6];
  strcpy(name, ALICE);
  ss_push(name);
  strcpy(name, BOB);
  ss_push(name);

  ck_assert_str_eq(ss_pop(), BOB);
  ck_assert_str_eq(ss_pop(), ALICE);
}
END_TEST

TCase *tcase_stringstack(void) {
  TCase *tc;

  tc = tcase_create("string-stack");
  tcase_add_checked_fixture(tc, setup, teardown);
  tcase_add_test(tc, pushedString_whenPopped_returnsString);
  tcase_add_test(tc,
                 twoPushedStrings_whenPopped_willReturnStringsInReverseOrder);
  tcase_add_test(tc, onePushedString_withTwoPops_willReturnStackUnderflow);
  tcase_add_test(
      tc,
      fiveHundredOnePushedStrings_whenPoppedFiveHundredOneTimes_willReturnStackUnderflowOnTheFiftyFirstPop);
  tcase_add_test(tc,
                 stackPeek_withTwoStringsPushed_returnsMostRecentStringPushed);
  tcase_add_test(
      tc,
      stackPeekCalledTwice_withTwoStringsPushed_returnsMostRecentStringPushed);
  tcase_add_test(tc, stackPeek_withEmptyStack_returnsStackUnderflow);
  tcase_add_test(
      tc,
      stackPopCalledTwiceWithSamePointerButDifferentContents_poppedTwice_returnsTwoDifferentStrings);

  return tc;
}

Suite *suite_stringstack(void) {
  Suite *s;

  s = suite_create("string-stack");

  suite_add_tcase(s, tcase_stringstack());

  return s;
}
