#ifndef GETLINE_H
#define GETLINE_H

#include <stdio.h>

/* 改名 my_getline：避免与 macOS <stdio.h> 中的 POSIX getline 冲突 */
int my_getline(char s[], int lim)
{
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

#endif
