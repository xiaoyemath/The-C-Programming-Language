/* Exercise 1-13: Write a program to print a histogram of the lengths of
 * words in its input. It is easy to draw the histogram with the bars
 * horizontal; a vertical orientation is more challenging.
 */

#include <stdio.h>
#include <ctype.h>

#define MAXLEN 20   /* 统计的最大单词长度 */

int main()
{
    int c, len, inword;
    int count[MAXLEN + 1];  /* count[i] = 长度为 i 的单词个数 */
    int i, j;

    for (i = 0; i <= MAXLEN; i++)
        count[i] = 0;

    len = 0;
    inword = 0;
    while ((c = getchar()) != EOF) {
        if (!isalnum(c)) {          /* 非字母数字：空白或标点符号 */
            if (inword) {           /* 单词刚结束 */
                if (len <= MAXLEN)
                    count[len]++;
                else
                    count[MAXLEN]++;    /* 超长的都归到 MAXLEN 一档 */
                len = 0;
                inword = 0;
            }
        } else {
            inword = 1;
            len++;
        }
    }
    /* 处理最后一个单词（输入末尾没有换行的情况） */
    if (inword) {
        if (len <= MAXLEN)
            count[len]++;
        else
            count[MAXLEN]++;
    }

    /* 水平直方图 */
    printf("\n水平直方图:\n");
    for (i = 1; i <= MAXLEN; i++) {
        printf("%2d | ", i);
        for (j = 0; j < count[i]; j++)
            putchar('*');
        putchar('\n');
    }
    return 0;
}
