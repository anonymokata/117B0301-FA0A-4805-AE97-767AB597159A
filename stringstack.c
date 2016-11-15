#include <stdlib.h>
#include <string.h>

#include "stringstack.h"

/* This is larger than the stacks in the operator stack because we need a
 * memory of every string we have allocated.
 */
#define STACK_SIZE 500

static char *stack[STACK_SIZE];
static int stack_idx;

static char *memory[STACK_SIZE];
static int memory_idx;

void ss_init(void) {
  stack_idx = 0;
  memory_idx = 0;

  memset(stack, 0, sizeof(stack));
  memset(memory, 0, sizeof(memory));
}

void ss_push(const char *newitem) {}

const char *ss_pop(void) { return "NULL"; }

const char *ss_peek(void) { return NULL; }

void ss_release(void) {}
