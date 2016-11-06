#ifndef _UNIT_H_
#define _UNIT_H_

void rpn_init();
void rpn_release();

char* infix_to_rpn(const char* infix);

#endif
