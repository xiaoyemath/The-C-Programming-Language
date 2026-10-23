/* Exercise 5-12: Extend entab and detab to accept the shorthand entab -m
 * +n to mean tab stops every n columns, starting at column m. Choose
 * convenient (for the user) default behavior.
 *
 * 用法:
 *   detab              -> 默认制表位: 每 8 列一个 (8,16,24,...)
 *   detab 4 8 16 32    -> 显式指定制表位在第 4,8,16,32 列
 *   detab -3 +6        -> 第一个制表位在第 3 列, 之后每隔 6 列 (3,9,15,...)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100   /* 行长上限 */
#define TABINC 8      /* 默认制表位间隔 */
#define YES 1
#define NO 0

void settab(int argc, char *argv[], char *tab);
void detab(char *tab);
void entab(char *tab);
int tabpos(int pos, char *tab);

int main(int argc, char *argv[])
{
    char tab[MAXLINE + 1];

    settab(argc, argv, tab);
    detab(tab);   /* 想得到 entab 程序, 把这一行换成 entab(tab); */
    return 0;
}

/* settab: 设置制表位, 支持三种形式 (默认 / -m +n / 显式列表) */
void settab(int argc, char *argv[], char *tab)
{
    int i, pos, inc;

    if (argc <= 1)                              /* 无参数: 默认每 8 列 */
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = (i % TABINC == 0) ? YES : NO;
    else if (argc == 3 && argv[1][0] == '-' && argv[2][0] == '+') {
        /* -m +n: 第一个制表位在第 m 列, 此后每隔 n 列 */
        pos = atoi(&argv[1][1]);                /* 跳过 '-', 取 m */
        inc = atoi(&argv[2][1]);                /* 跳过 '+', 取 n */
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = (i == pos) ? YES : NO;
        while (pos + inc <= MAXLINE) {
            pos += inc;
            tab[pos] = YES;
        }
    } else {                                    /* 显式给定制表位列号 */
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = NO;
        while (--argc > 0) {
            pos = atoi(*++argv);
            if (pos > 0 && pos <= MAXLINE)
                tab[pos] = YES;
        }
    }
}

/* detab: 把 tab 替换成空格, 跳到下一个制表位 */
void detab(char *tab)
{
    int c, pos = 1;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            do
                putchar(' ');
            while (tabpos(pos++, tab) != YES);
        } else if (c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            ++pos;
        }
    }
}

/* entab: 用最少的 tab 和空格替换连续空格 */
void entab(char *tab)
{
    int c, pos;
    int nb = 0;
    int nt = 0;

    for (pos = 1; (c = getchar()) != EOF; ++pos) {
        if (c == ' ') {
            if (tabpos(pos, tab) == NO)
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
                while (tabpos(pos, tab) != YES)
                    ++pos;
        }
    }
}

/* tabpos: 判断 pos 这一列是不是制表位 */
int tabpos(int pos, char *tab)
{
    if (pos > MAXLINE)
        return YES;
    else
        return tab[pos];
}
