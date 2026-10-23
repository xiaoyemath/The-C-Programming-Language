/* Exercise 1-11: How would you test the word count program? What kinds of
 * input are most likely to uncover bugs if there are any?
 */

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000 /* 最大输入行长度 */
int get_line(char line[], int maxline);
void reverse(char line[]);
int main()
{
    char line[MAXLINE];
    get_line(line, MAXLINE);
    reverse(line);
    printf("%s", line);
    return 0;
}
int get_line(char s[], int lim)
{
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
void reverse(char s[])
{
    int i, j;
    char temp;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}