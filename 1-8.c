/* Exercise 1-8: Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>
int main()
{
    int c, ln, sn, tn;
    ln = sn = tn = 0;
    c = getchar();
    while (c != EOF) {
        if (c == ' ') {
            sn++;
        } else if (c == '\t') {
            tn++;
        } else if (c == '\n') {
            ln++;
        }
        c = getchar();
    }
    printf("space number: %d\ntab number: %d\nline number: %d\n", sn, tn, ln);
}