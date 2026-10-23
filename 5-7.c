/* Exercise 5-7: Rewrite readlines to store lines in an array supplied by
 * main, rather than calling alloc to maintain storage. How much faster is
 * the program?
 */
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000   /* 最多可排序的行数 */
#define MAXLEN 1000     /* 每行最大长度 */
#define ALLOCSIZE 10000 /* 可用存储空间大小 */

char *lineptr[MAXLINES]; /* 指向文本行的指针 */

int readlines(char *lineptr[], int maxlines, char *storage, int maxsize);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int get_line(char *, int);
char *alloc(int);

/* sort input lines */
int main(void)
{
    int nlines; /* 读入的输入行数 */
    char storage[MAXLINES * MAXLEN];

    if ((nlines = readlines(lineptr, MAXLINES, storage,
                            MAXLINES * MAXLEN)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: 读入输入行 */
int readlines(char *lineptr[], int maxlines, char *storage, int maxsize)
{
    int len, nlines;
    char line[MAXLEN];
    char *p = storage;

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (storage + maxsize - p) < len)
            return -1;
        else {
            line[len - 1] = '\0'; /* 删除换行符 */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

/* writelines: 输出输入行 */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* qsort: 按递增顺序对 v[left]...v[right] 排序 */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

int get_line(char *s, int lim)
{
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - start;
}

/* swap: 交换 v[i] 和 v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) // 返回指向 n 个字符的指针
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { // 有足够空间
        allocp += n;
        return allocp - n; // 原指针
    } else                 // 空间不够
        return 0;
}

void afree(char *p) // 释放 p 指向的存储
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
