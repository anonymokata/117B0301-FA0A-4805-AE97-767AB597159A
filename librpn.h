#ifndef _UNIT_H_
#define _UNIT_H_

#include "ast.h"

char *infix_to_rpn(char *infix);

char *rpn_to_infix(const char *rpn);

char *rpn_to_rpn(const char *rpn);

struct ast *parse_rpn(const char *rpn);
char *print_infix(struct ast *tree);
char *print_rpn(struct ast *tree);

#endif
