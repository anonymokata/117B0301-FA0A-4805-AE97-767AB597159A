#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "librpn.h"
#include "stack.h"

int main(int argc, const char **argv) {
  const char *work = NULL;
  stack_init();

  if (argc > 1) {
    work = rpn_to_infix(argv[1]);
    printf("%s => %s\n", argv[1], work);
  }

  return EXIT_SUCCESS;
}
