#include <stdio.h>
#include "calc.h"

/* 4-6: variables A..Z and the most recently printed value */
double variable[26];
int last_was_number;
double last;

/* stack */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* 4-4: peek, swap, clear, dup */

/* peek: print top of stack without popping */
void peek(void)
{
    if (sp > 0)
        printf("top of stack: %g\n", val[sp - 1]);
    else
        printf("stack empty\n");
}

/* swap: swap the top two stack elements */
void swap(void)
{
    double temp;
    if (sp > 1) {
        temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    }
}

/* clear: empty the stack and reset all variables */
void clear(void)
{
    int i;
    sp = 0;
    for (i = 0; i < 26; i++)
        variable[i] = 0.0;
}

/* dup: push a copy of the top element */
void dup(void)
{
    if (sp > 0)
        push(val[sp - 1]);
    else
        printf("stack empty\n");
}
