/* Exercise 3-6: Write a version of itoa that accepts three arguments
 * instead of two. The third argument is a minimum field width; the
 * converted number must be padded with blanks on the left if necessary to
 * make it wide enough.
 */

#include "reverse.h"
void itoa_new(int n, char s[], int w)
{
    int i, sign;
    char s1[100];
    i = 0, sign = n;
    do {
        s[i++] = abs(n % 10) + '0';

    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    while (i < w)
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}