#include <ctype.h>
#include <stdio.h>
#include "calc.h"

/* getop: get next operator or numeric operand (uses getch/ungetch) */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (isalpha(c)) {
        i = 0;
        while (isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        if (i == 1 && isupper(s[0]))
            return VARIABLE;
        return MATHNAME;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */

    i = 0;
    if (c == '-') {
        if (isdigit(c = getch()) || c == '.')
            s[++i] = c; /* keep '-' in s[0], store first digit at s[1] */
        else {
            if (c != EOF)
                ungetch(c);
            return '-'; /* minus operator */
        }
    }
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

/* 4-11: getop without getch/ungetch -- at most one character of
 * pushback, kept in a static variable */
int getop_without_getch(char s[])
{
    int i, c;
    static int lastc = EOF;
    if (lastc != EOF) {
        c = lastc;
        lastc = EOF;
    } else
        c = getchar();
    while (c == ' ' || c == '\t')
        c = getchar();
    s[0] = c;
    s[1] = '\0';
    if (isalpha(c)) {
        i = 0;
        while (isalpha(s[++i] = c = getchar()))
            ;
        s[i] = '\0';
        if (c != EOF)
            lastc = c;
        if (i == 1 && isupper(s[0]))
            return VARIABLE;
        return MATHNAME;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-') {
        c = getchar();
        if (isdigit(c) || c == '.')
            s[++i] = c;
        else {
            if (c != EOF)
                lastc = c;
            return '-'; /* minus operator */
        }
    }
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        lastc = c;
    return NUMBER;
}
