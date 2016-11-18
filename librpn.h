#ifndef _UNIT_H_
#define _UNIT_H_

#include "ast.h"

const char *infix_to_rpn(const char *infix);

const char *rpn_to_infix(const char *rpn);

const char *rpn_to_rpn(const char *rpn);

struct ast *parse_rpn(const char *rpn);
char *print_infix(struct ast *tree);
char *print_rpn(struct ast *tree);

#endif
