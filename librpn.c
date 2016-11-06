#include "librpn.h"
#include <stdlib.h>
#include <string.h>

/* Assume there are 26 available symbols [a-z].
 * Each symbol save the first may be followed by an operator [^,-,+,/,*]
 * This gives 26 * 2 - 1 = 51 characters needed to represent any possible
 * operation in RPN.
 * An additional character is needed for a terminating NULL value.
 */
#define RPN_BUFFER_SIZE 52

char *infix_to_rpn(char *infix) {
  char buffer[RPN_BUFFER_SIZE];
  memset(buffer, 0, RPN_BUFFER_SIZE);

  buffer[0] = infix[0];
  buffer[1] = infix[2];
  buffer[2] = infix[1];

  // Unchecked copy is safe because the RPN representation will always be the
  // same size or smaller than the infix notation.
  strcpy(infix, buffer);
  return infix;
}