#include "test_stack.h"
#include "../stack.h"

TCase *tcase_stack(void) {
  TCase *tc;

  tc = tcase_create("stack");

  return tc;
}