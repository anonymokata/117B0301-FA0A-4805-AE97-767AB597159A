#include "stack.h"
#include <stdio.h>
#include <string.h>

#define STACK_SIZE 50
char _stack[STACK_SIZE];
int _idx;

void stack_init(void) {
  memset(_stack, 0, sizeof(_stack));
  _idx = 0;
}

void stack_push(char c) {
  if (_idx < sizeof(_stack)) {
    _stack[_idx++] = c;
  }
}

char stack_pop(void) {
  if (0 == _idx) {
    return STACK_UNDERFLOW;
  }
  return _stack[--_idx];
}

char stack_peek(void) {
  if (_idx > 0) {
    return _stack[_idx - 1];
  }
  return STACK_UNDERFLOW;
}
