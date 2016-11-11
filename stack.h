/* A static stack capable of holding single character input.
 */

#ifndef _STACK_H_
#define _STACK_H_

/* Put a character on the stack */
void stack_push(char);

/* Remove the most recent character from the stack */
char stack_pop();

/* look at the most recently pushed character on the stack */
char stack_peek();

#endif