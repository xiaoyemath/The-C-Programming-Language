/* Exercise 5-6: Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities
 * include getline (Chapters 1 and 4), atoi, itoa, and their variants
 * (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
 * (Chapter 4).
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* get_line */
int get_line(char *s, int lim)
{
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - start;
}

/* atoi */
int atoi(char *s)
{
    int n = 0;
    while (*s >= '0' && *s <= '9')
        n = 10 * n + (*s++ - '0');
    return n;
}

/* reverse */
void reverse(char *s)
{
    char *p = s + strlen(s) - 1;
    int tmp;
    while (s < p) {
        tmp = *s;
        *s++ = *p;
        *p-- = tmp;
    }
}

/* itoa */
void itoa(int n, char *s)
{
    int sign;
    char *p = s;

    if ((sign = n) < 0)
        n = -n;
    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(p);
}

/* strindex */
int strindex(const char *s, const char *t)
{
    const char *i, *j, *k;

    for (i = s; *i != '\0'; i++) {
        for (j = i, k = t; *k != '\0' && *j == *k; j++, k++)
            ;
        if (k > t && *k == '\0')
            return i - s;
    }
    return -1;
}

#define BUFSIZE 100
#define NUMBER '0'

char buf[BUFSIZE];
char *bufp = buf;
/* getch */
int getch(void)
{
    return (bufp > buf) ? *--bufp : getchar();
}
/* ungetch */
void ungetch(int c)
{
    if (bufp >= buf + BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        *bufp++ = c;
}

/* getop */
int getop(char *s)
{
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t')
        ;
    *(s + 1) = '\0';
    if (!isdigit(c) && c != '.')
        return c;   /* 不是数 */
    if (isdigit(c)) /* 收集整数部分 */
        while (isdigit(*++s = c = getch()))
            ;
    if (c == '.') /* 收集小数部分 */
        while (isdigit(*++s = c = getch()))
            ;
    *s = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

/* atof */
double atof(char *s)
{
    double val, power;
    int sign;

    while (isspace(*s))
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + (*s - '0');
    if (*s == '.')
        s++;
    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

/* itob */
void itob(int n, char *s, int b)
{
    int sign;
    char *p = s;
    static char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if ((sign = n) < 0)
        n = -n;
    do {
        *s++ = digits[n % b];
    } while ((n /= b) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(p);
}
