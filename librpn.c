#include <stdlib.h>
#include <string.h>

#include "aststack.h"
#include "librpn.h"
#include "stack.h"

#define RPN_BUFFER_SIZE 4096

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

const char *infix_to_rpn(const char *infix) {
  char symbol;

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

  return buffer;
}

int expression_needs_wrap(const char *expression, char op) {
  enum operator_p op_precedence;
  enum operator_p ex_precedence;

  if (strlen(expression) == 3) {
    ex_precedence = operator_precedence(expression[1]);
    op_precedence = operator_precedence(op);
    if (ex_precedence > op_precedence) {
      return 1;
    }
  }
  return 0;
}

int needs_parens(struct ast *current, struct ast *child) {
  enum operator_p precedence;
  enum operator_p child_precedence;

  if (NULL == child) {
    return 0;
  }

  precedence = operator_precedence(current->op);
  child_precedence = operator_precedence(child->op);

  if (OP_INVALID == child_precedence) {
    return 0;
  }

  if (precedence < child_precedence) {
    return 1;
  }

  return 0;
}

void print_infix_node(struct ast *parent) {
  enum operator_p parent_precedence;
  int left_parens;
  int right_parens;

  if (NULL == parent) {
    return;
  }

  left_parens = needs_parens(parent, parent->left);
  right_parens = needs_parens(parent, parent->right);

  if (left_parens)
    buffer_append('(');
  print_infix_node(parent->left);
  if (left_parens)
    buffer_append(')');
  buffer_append(parent->op);
  if (right_parens)
    buffer_append('(');
  print_infix_node(parent->right);
  if (right_parens)
    buffer_append(')');
}

char *print_infix(struct ast *top) {
  buffer_init();
  print_infix_node(top);

  return buffer;
}

void print_rpn_node(struct ast *parent) {
  if (NULL == parent) {
    return;
  }

  print_rpn_node(parent->left);
  print_rpn_node(parent->right);
  buffer_append(parent->op);
}

char *print_rpn(struct ast *top) {

  buffer_init();

  print_rpn_node(top);

  return buffer;
}

const char *rpn_to_infix(const char *rpn) {
  char *result;
  struct ast *tree;

  tree = parse_rpn(rpn);
  result = print_infix(tree);
  ast_release(tree);

  return result;
}

const char *rpn_to_rpn(const char *rpn) {
  char *result;
  struct ast *tree;

  tree = parse_rpn(rpn);
  result = print_rpn(tree);
  ast_release(tree);

  return result;
}

struct ast *parse_rpn(const char *rpn) {
  enum operator_p precedence;
  char x;
  struct ast *current;
  struct ast *TOP = NULL;

  as_init();

  for (int i = 0; rpn[i]; ++i) {
    x = rpn[i];
    precedence = operator_precedence(x);
    current = ast_create();
    current->op = x;

    switch (x) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
      current->right = as_pop();
      current->left = as_pop();
      as_push(current);
      TOP = current;
      break;
    default:
      as_push(current);
    }
  }
  return TOP;
}