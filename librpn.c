#include "librpn.h"
#include "stack.h"
#include <stdlib.h>
#include <string.h>

/* Assume there are 26 available symbols [a-z].
 * Each symbol save the first may be followed by an operator [^,-,+,/,*]
 * This gives 26 * 2 - 1 = 51 characters needed to represent any possible
 * operation in RPN.
 * An additional character is needed for a terminating NULL value.
 */
#define RPN_BUFFER_SIZE 52

char buffer[RPN_BUFFER_SIZE];
int buffer_idx;

void buffer_init() {
  memset(buffer, 0, sizeof(buffer));
  buffer_idx = 0;
}

void buffer_append(char x) {
  if (buffer_idx < sizeof(buffer)) {
    buffer[buffer_idx++] = x;
  }
}

#define NOT_AN_OPERATOR -1
int operator_precedence(char op) {
  switch (op) {
  case '*':
  case '/':
  case '^':
    return 1;
  case '-':
    return 4;
  case '+':
    return 5;
  default:
    return NOT_AN_OPERATOR;
  }
}

char *infix_to_rpn(char *infix) {
  char symbol;
  char last_operator;
  int precedence;

  buffer_init();
  stack_init();

  for (int i = 0; infix[i]; ++i) {
    symbol = infix[i];
    precedence = operator_precedence(symbol);
    if (NOT_AN_OPERATOR == precedence) {
      buffer_append(symbol);
    } else {
      last_operator = stack_peek();
      if (STACK_UNDERFLOW != last_operator &&
          operator_precedence(last_operator) <= precedence) {
        buffer_append(stack_pop());
      }
      stack_push(symbol);
    }
  }

  while ((symbol = stack_pop()) != STACK_UNDERFLOW) {
    buffer_append(symbol);
  }

  // Unchecked copy is safe because the RPN representation will always be the
  // same size or smaller than the infix notation.
  strcpy(infix, buffer);
  return infix;
}
