#include <stdio.h>
#include <string.h>
#include "calc.h"

/* 4-9: int buffer, so a pushed-back EOF is stored correctly */
int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;     /* next free position in buf */

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* 4-7: push an entire string back onto the input */
void ungets(char s[])
{
    int i;
    for (i = strlen(s) - 1; i >= 0; i--)
        ungetch(s[i]);
}
