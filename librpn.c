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

enum operator_p {
  OP_EXPONENT,
  OP_DIVISION,
  OP_MULTIPLICATION,
  OP_SUBTRACTION,
  OP_ADDITION,

  // Should always be the last option, so invalid operators will never be popped
  // from the stack and put into the buffer for precedence.
  OP_INVALID
};

#define NOT_AN_OPERATOR -1
enum operator_p operator_precedence(char op) {
  switch (op) {
  case '^':
    return OP_EXPONENT;
  case '/':
    return OP_DIVISION;
  case '*':
    return OP_MULTIPLICATION;
  case '-':
    return OP_SUBTRACTION;
  case '+':
    return OP_ADDITION;
  // There is special logic to handle parens, so for purposes of operator
  // precedence we should treat them like other symbols.
  case '(':
  case ')':
  default:
    return OP_INVALID;
  }
}

void handle_operator(char symbol) {
  char last_operator;
  enum operator_p precedence;

  precedence = operator_precedence(symbol);
  for (last_operator = stack_peek();
       STACK_UNDERFLOW != last_operator &&
       operator_precedence(last_operator) <= precedence;
       last_operator = stack_peek()) {
    buffer_append(stack_pop());
  }
  stack_push(symbol);
}

void handle_right_paren(char symbol /* unused */) {
  char last_operator;
  for (last_operator = stack_pop();
       last_operator != '(' && last_operator != STACK_UNDERFLOW;
       last_operator = stack_pop()) {
    buffer_append(last_operator);
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
    switch (symbol) {
    case '(':
      stack_push(symbol);
      break;
    case ')':
      handle_right_paren(symbol);
      break;
    case '^':
    case '/':
    case '*':
    case '-':
    case '+':
      handle_operator(symbol);
      break;
    default:
      buffer_append(symbol);
      break;
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
