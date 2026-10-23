/* Exercise 5-10: Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a
 * separate argument. For example, expr 2 3 4 + * evaluates 2 x (3+4).
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXVAL 100

int sp = 0;          /* 栈顶指针：下一个空位置的下标 */
double val[MAXVAL];  /* 存放操作数的栈 */

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full\n");
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int main(int argc, char *argv[])
{
    int i;
    double op2;

    for (i = 1; i < argc; i++) {
        char *p = argv[i];

        /* 判断是否为数字（含负数，如 -3） */
        if (isdigit(*p) || (*p == '-' && isdigit(*(p + 1))))
            push(atof(p));

        /* 运算符：注意减法和除法要按正确顺序弹出 */
        else if (*p == '+' && *(p + 1) == '\0')
            push(pop() + pop());
        else if (*p == '-' && *(p + 1) == '\0') {
            op2 = pop();
            push(pop() - op2);
        }
        else if (*p == '*' && *(p + 1) == '\0')
            push(pop() * pop());
        else if (*p == '/' && *(p + 1) == '\0') {
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
        }
        else
            printf("error: unknown token %s\n", p);
    }

    if (sp == 1)
        printf("%.8g\n", pop());
    else
        printf("error: invalid expression\n");

    return 0;
}
