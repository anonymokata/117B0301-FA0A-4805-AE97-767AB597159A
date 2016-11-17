#ifndef _ASTSTACK_H_
#define _ASTSTACK_H_

#include "ast.h"

#define AS_UNDERFLOW NULL

/* Call this before using your stack, or to reset the condition of the stack */
void as_init(void);

/* Put a character on the stack */
void as_push(struct ast *node);

/* Remove the most recent character from the stack */
struct ast *as_pop(void);

/* look at the most recently pushed character on the stack */
struct ast *ss_peek(void);

#endif