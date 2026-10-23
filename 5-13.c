/* Exercise 5-13: Write the program tail, which prints the last n lines of
 * its input. By default, n is 10, let us say, but it can be changed by an
 * optional argument, so that tail -n prints the last n lines. The program
 * should behave rationally no matter how unreasonable the input or the
 * value of n. Write the program so it makes the best use of available
 * storage; lines should be stored as in the sorting program of Section
 * 5.6, not in a two-dimensional array of fixed size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALLOCSIZE 10000
#define MAXLEN 1000
#define MAXLINES 5000
int getaline(char *s, int lim);
char *alloc(int);
void afree(char *p);

int main(int argc, char *argv[])
{
    int n = 10;
    int count = 0;
    int len;
    int start, nprint;
    int j;
    char line[MAXLEN];
    char *lineptr[MAXLINES];
    char *p;

    if (argc == 2 && argv[1][0] == '-') {
        n = atoi(argv[1] + 1);
    }
    if (n < 0)
        n = 0;
    if (n > MAXLINES)
        n = MAXLINES;
    if (n == 0)
        return 0;
    while ((len = getaline(line, MAXLEN)) > 0) {
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        if ((p = alloc(strlen(line) + 1)) == NULL) {
            return 1;
        }
        strcpy(p, line);
        lineptr[count % n] = p;
        count++;
    }
    nprint = (count < n) ? count : n;
    start = (count < n) ? 0 : (count % n);
    for (j = 0; j < nprint; j++) {
        printf("%s\n", lineptr[(start + j) % n]);
    }
    return 0;
}
int getaline(char *s, int lim)
{
    int c;
    char *start = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - start;
}
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return 0;
    }
}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        allocp = p;
    }
}