/* Exercise 3-4: In a two's complement number representation, our version
 * of itoa does not handle the largest negative number, that is, the value
 * of n equal to -(2^(wordsize-1)). Explain why not. Modify it to print
 * that value correctly, regardless of the machine on which it runs.
 */

#include "reverse.h"
#include <stdio.h>
#include <stdlib.h>

void itoa(int n, char s[])
{
    int i, sign;
    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char s[100];
    int n = -2147483648;
    itoa(n, s);
    printf("%d -> %s\n", n, s);
    return 0;
}
