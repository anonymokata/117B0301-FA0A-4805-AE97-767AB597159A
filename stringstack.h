#ifndef _STRINGSTACK_H_
#define _STRINGSTACK_H_

#define SS_UNDERFLOW NULL

/* Call this before using your stack, or to reset the condition of the stack */
void ss_init(void);

/* Put a character on the stack */
void ss_push(const char *);

/* Remove the most recent character from the stack */
const char *ss_pop(void);

/* look at the most recently pushed character on the stack */
const char *ss_peek(void);

/* Deallocate stack resources, including all returned strings */
void ss_release(void);

#endif