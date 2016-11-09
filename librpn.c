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

char buffer[RPN_BUFFER_SIZE];
int buffer_idx;

void buffer_init()
{
    memset(buffer, 0, sizeof(buffer));
    buffer_idx = 0;
}

void buffer_append(char x)
{
    if (buffer_idx < sizeof(buffer))
    {
        buffer[buffer_idx++] = x;
    }
}

#define NOT_AN_OPERATOR -1
int operator_precedence(char operator)
{
    switch (operator)
    {
    case '*':
    case '/':
    case '+':
    case '-':
    case '^':
        return 5;
    default:
        return NOT_AN_OPERATOR;
    }
}

char stack[25];
int stack_idx = 0;

void stack_init()
{
    memset(stack, 0, sizeof(stack));
    stack_idx = 0;
}

void stack_push(char x)
{
    if (stack_idx < sizeof(stack))
    {
        stack[++stack_idx] = x;
    }
}

char stack_pop()
{
    if (stack_idx > 0)
    {
        char tmp = stack[stack_idx];
        stack[stack_idx--] = 0;
        return tmp;
    }
    return 0;
}

char *infix_to_rpn(char *infix)
{
    char symbol;
    int precedence;

    buffer_init();
    stack_init();

    for (int i = 0; infix[i]; ++i)
    {
        symbol = infix[i];
        precedence = operator_precedence(symbol);
        if (NOT_AN_OPERATOR == precedence)
        {
            buffer_append(symbol);
        }
        else
        {
            stack_push(symbol);
        }
    }

    while ((symbol = stack_pop()))
    {
        buffer_append(symbol);
    }

    // Unchecked copy is safe because the RPN representation will always be the
    // same size or smaller than the infix notation.
    strcpy(infix, buffer);
    return infix;
}