/* Exercise 4-1: Write the function strrindex(s,t), which returns the
 * position of the rightmost occurrence of t in s, or -1 if there is none.
 */

#include <string.h>
int strindex(char s[], char t[])
{
    int i, j, k;
    for (i = strlen(s) - 1; i >= 0; i--) {
        for (k = strlen(t) - 1, j = i; k >= 0 && s[j] == t[k]; k--, j--)
            ;
        if (k < 0) {
            return i - strlen(t) + 1;
        }
    }
    return -1;
}