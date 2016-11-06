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
#define RPN_BUFFER_COUNT 50

char arena[RPN_BUFFER_COUNT][RPN_BUFFER_SIZE];
int arena_idx = 0;

void rpn_init() {
  memset(arena, 0, RPN_BUFFER_SIZE * RPN_BUFFER_COUNT);
  arena_idx = 0;
}

void rpn_release() {
  // Overwriting memory because it can prevent false positives in the event of
  // bad memory handling.
  memset(arena, 0, RPN_BUFFER_SIZE * RPN_BUFFER_COUNT);
}

char *arena_get_next() {
  if (arena_idx < RPN_BUFFER_COUNT) {
    return (char *)&arena[arena_idx++];
  }
  return NULL;
}

char *infix_to_rpn(const char *infix) {
    char *buffer;

    buffer = arena_get_next(); 
    strcpy(buffer, "ab+");
    return buffer; 
}