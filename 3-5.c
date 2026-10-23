/* Exercise 3-5: Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s. In particular,
 * itob(n,s,16) formats n as a hexadecimal integer in s.
 */

#include "reverse.h"
#include <stdlib.h>
void itob(int n, char s[], int b)
{
    int i, sign;
    sign = n, i = 0;
    do {
        int m = abs(n % b);
        if (b > 10 && m > 9) {
            s[i++] = m - 10 + 'A';
        } else {
            s[i++] = m + '0';
        }
    } while ((n /= b) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}