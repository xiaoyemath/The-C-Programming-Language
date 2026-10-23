/* Exercise 1-6: Verify that the expression getchar() != EOF is 0 or 1.
 */

#include <stdio.h>
int main()
{
    int c;

    printf("请输入一些字符，然后按 Ctrl+D（EOF）：\n");

    while ((c = getchar()) != EOF) {
        printf("读到字符 '%c'，表达式 (getchar() != EOF) 的值是 %d\n", c, (c != EOF));
    }

    /* 循环结束后，getchar() 返回 EOF，此时表达式值为 0 */
    printf("遇到 EOF，表达式 (getchar() != EOF) 的值是 %d\n", (getchar() != EOF));

    return 0;
}