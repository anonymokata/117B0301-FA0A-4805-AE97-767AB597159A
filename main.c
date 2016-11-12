#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "librpn.h"
#include "stack.h"

int main(int argc, const char **argv) {
  char *work = NULL;
  stack_init();

  if (argc > 1) {
    work = strdup(argv[1]);
    infix_to_rpn(work);
    printf("%s => %s\n", argv[1], work);
  }

  return EXIT_SUCCESS;
}
