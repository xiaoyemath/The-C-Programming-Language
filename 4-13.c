/* Exercise 4-13: Write a recursive version of the function reverse(s),
 * which reverses the string s in place.
 */

#include <string.h>

static void reverse_r(char s[], int i, int j)
{
    if (i >= j)
        return;
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
    reverse_r(s, i + 1, j - 1);
}
void reverse(char s[])
{
    reverse_r(s, 0, (int)strlen(s) - 1);
}
