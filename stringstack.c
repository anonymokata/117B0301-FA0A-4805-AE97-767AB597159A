#include <stdlib.h>
#include <string.h>

#include "stringstack.h"

/* This is larger than the stacks in the operator stack because we need a
 * memory of every string we have allocated.
 */
#define STACK_SIZE 500

static const char *stack[STACK_SIZE];
static int stack_idx;

void ss_init(void) {
  stack_idx = 0;
  memset(stack, 0, sizeof(stack));
}

void ss_push(const char *newitem) {
  if (stack_idx < STACK_SIZE)
    stack[stack_idx++] = newitem;
}

const char *ss_pop(void) { return stack[--stack_idx]; }

const char *ss_peek(void) { return stack[stack_idx - 1]; }

void ss_release(void) {}