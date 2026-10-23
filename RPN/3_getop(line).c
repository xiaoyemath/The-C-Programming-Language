#include <ctype.h>
#include <stdio.h>
#include "calc.h"
#include "getline.h"

/* 4-10: read a whole line with my_getline, then parse tokens from the
 * buffer -- getch/ungetch are not needed. To try this version, call
 * getop_getline(s) instead of getop(s) in rpnmain.c. */

char line[MAXLINE];
int lp = 0;

int getop_getline(char s[])
{
    int i, c;

    if (line[lp] == '\0') {
        if (my_getline(line, MAXLINE) == 0)
            return EOF;
        lp = 0;
    }
    while ((s[0] = c = line[lp++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (isalpha(c)) {
        i = 0;
        while (isalpha(s[++i] = c = line[lp++]))
            ;
        s[i] = '\0';
        lp--;
        if (i == 1 && isupper(s[0]))
            return VARIABLE;
        return MATHNAME;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */

    i = 0;
    if (c == '-') {
        c = line[lp++];
        if (isdigit(c) || c == '.')
            s[++i] = c;
        else {
            lp--;
            return '-'; /* minus operator */
        }
    }
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = line[lp++]))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = line[lp++]))
            ;
    s[i] = '\0';
    lp--;
    return NUMBER;
}
