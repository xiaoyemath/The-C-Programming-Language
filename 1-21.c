/* Exercise 1-21: Write a program entab that replaces strings of blanks by
 * the minimum number of tabs and blanks to achieve the same spacing. Use
 * the same tab stops as for detab. When either a tab or a single blank
 * would suffice to reach a tab stop, which should be given preference?
 */

#include <stdio.h>
#define tab 8
int main()
{
    int pos, nb = 0, nt = 0, c;
    for (pos = 1; (c = getchar()) != EOF; ++pos) {
        if (c == ' ') {
            if (pos % tab != 0)
                ++nb;
            else {
                nb = 0;
                ++nt;
            }
        } else {
            for (; nt > 0; --nt)
                putchar('\t');
            if (c == '\t')
                nb = 0;
            else
                for (; nb > 0; --nb)
                    putchar(' ');
            putchar(c);
            if (c == '\n')
                pos = 0;
            else if (c == '\t')
                pos += tab - (pos - 1) % tab - 1;
        }
    }
    return 0;
}
