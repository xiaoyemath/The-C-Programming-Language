/* Exercise 5-2: Write getfloat, the floating-point analog of getint. What
 * type does getfloat return as its function value?
 */

#include <ctype.h>
int getch(void);
void ungetch(int);
int getfloat(double *f)
{
    int c, sign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*f = 0.0; isdigit(c); c = getch())
        *f = 10.0 * *f + (c - '0');
    if (c == '.') {
        c = getch();
        int i = 0;
        while (isdigit(c)) {
            *f = 10.0 * *f + (c - '0');
            c = getch();
            ++i;
        }
        while (i != 0) {
            *f /= 10;
            --i;
        }
    }
    *f *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}