/* Exercise 5-11: Modify the programs entab and detab (written as exercises
 * in Chapter 1) to accept a list of tab stops as arguments. Use the
 * default tab settings if there are no arguments.
 *
 * 用法:
 *   detab            -> 默认制表位: 每 8 列一个 (8,16,24,...)
 *   detab 4 8 16 32  -> 显式指定制表位在第 4,8,16,32 列
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

/* settab: 用命令行参数设置制表位, 无参数则用默认值 */
void settab(int argc, char *argv[], char *tab)
{
    int i, pos;

    if (argc <= 1)                       /* 无参数: 默认每 TABINC 列一个 */
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = (i % TABINC == 0) ? YES : NO;
    else {                               /* 显式给定制表位列号 */
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = NO;                 /* 先全部关掉 */
        while (--argc > 0) {             /* 遍历参数表 */
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
            /* 输出一个空格, 直到刚输出的那一列恰好是制表位为止 */
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
    int nb = 0;   /* 累积的空格数 */
    int nt = 0;   /* 累积的 tab 数 */

    for (pos = 1; (c = getchar()) != EOF; ++pos) {
        if (c == ' ') {
            if (tabpos(pos, tab) == NO)
                ++nb;            /* 没到制表位, 记一个空格 */
            else {
                nb = 0;          /* 到制表位了, 空格归零 */
                ++nt;            /* 换成一个 tab */
            }
        } else {
            for (; nt > 0; --nt)
                putchar('\t');   /* 先输出 tab */
            if (c == '\t')
                nb = 0;          /* 遇到 tab, 丢弃累积的空格 */
            else
                for (; nb > 0; --nb)
                    putchar(' ');/* 输出剩余空格 */
            putchar(c);
            if (c == '\n')
                pos = 0;
            else if (c == '\t')
                while (tabpos(pos, tab) != YES)
                    ++pos;       /* 跳到下一个制表位 */
        }
    }
}

/* tabpos: 判断 pos 这一列是不是制表位 */
int tabpos(int pos, char *tab)
{
    if (pos > MAXLINE)
        return YES;   /* 超出表长, 视为制表位, 避免死循环 */
    else
        return tab[pos];
}
