#include <stdlib.h>
#include <string.h>

#include "aststack.h"

/* This is larger than the stacks in the operator stack because we need a
 * memory of every string we have allocated.
 */
#define STACK_SIZE 500

static struct ast *stack[STACK_SIZE];
static int stack_idx;

void as_init(void) {
  stack_idx = 0;
  memset(stack, 0, sizeof(stack));
}

void as_push(struct ast *newitem) {
  if (stack_idx < STACK_SIZE) {
    stack[stack_idx++] = newitem;
  }
}

struct ast *as_pop(void) {
  return stack[--stack_idx];
}

struct ast *as_peek(void) {
  return stack[stack_idx - 1];
}
