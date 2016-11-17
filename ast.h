#ifndef _AST_H_
#define _AST_H_

struct ast {
  char op;
  struct ast *left;
  struct ast *right;
};

struct ast *ast_create(void);
void ast_release(struct ast *node);

#endif