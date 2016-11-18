#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "librpn.h"
#include "stack.h"

int main(int argc, const char **argv) {
  const char *work = NULL;
  stack_init();

  if (argc > 1) {
    const char *subject = argv[1];
    if (strlen(subject) < 3) {
      fprintf(stderr, "\"%s\" is too short to be valid input.\n", subject);
      return EXIT_FAILURE;
    }
    if (isalpha(subject[0]) && isalpha((char)subject[1])) {
      printf("RPN Notation: %s => Infix: %s\n", subject, rpn_to_infix(subject));
    } else {
      printf("Infix Notation: %s => RPN: %s\n", subject, infix_to_rpn(subject));
    }
  }

  return EXIT_SUCCESS;
}
