/* A static stack capable of holding single character input.
 */

#ifndef _STACK_H_
#define _STACK_H_

/* Call this before using your stack, or to reset the condition of the stack */
void stack_init(void);

/* Put a character on the stack */
void stack_push(char);

/* Remove the most recent character from the stack */
char stack_pop(void);

/* look at the most recently pushed character on the stack */
char stack_peek(void);

#endif
