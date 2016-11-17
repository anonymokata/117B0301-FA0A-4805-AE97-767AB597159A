#include <stdlib.h>

#include "ast.h"

struct ast *ast_create() {
  return (struct ast *)calloc(1, sizeof(struct ast));
}

void ast_release(struct ast *node) {
  if (NULL == node)
    return;
  if (node->left) {
    ast_release(node->left);
    node->left = NULL;
  }
  if (node->right) {
    ast_release(node->right);
    node->right = NULL;
  }
  free(node);
}