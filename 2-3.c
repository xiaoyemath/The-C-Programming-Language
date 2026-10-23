/* Exercise 2-3: Write a function htoi(s), which converts a string of
 * hexadecimal digits (including an optional 0x or 0X) into its equivalent
 * integer value. The allowable digits are 0 through 9, a through f, and A
 * through F.
 */

#include <stdio.h>

void lower(char s[])
{
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
}

int ltr_to_nbr(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return -1;
}

int htoi(char s[])
{
    lower(s);
    int i = 0, sum = 0;
    if (s[0] == '0' && (s[1] == 'x'))
        i = 2;
    for (; s[i] != '\0'; i++)
        sum = sum * 16 + ltr_to_nbr(s[i]);
    return sum;
}
