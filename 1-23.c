/* Exercise 1-23: Write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly.
 * C comments do not nest.
 */

#include <stdio.h>
#define IN1 1
#define IN2 2
#define OUT 0

int main()
{
    int c, state = OUT;
    while ((c = getchar()) != EOF) {
        switch (state) {
        case OUT:
            if (c == '/') {
                int next = getchar();
                switch (next) {
                case '/':
                    state = IN1;
                    break;
                case '*':
                    state = IN2;
                    break;
                default:
                    putchar(c);
                    putchar(next);
                }
            } else {
                putchar(c);
            }
            break;
        case IN1: {
            if (c == '\n') {
                putchar('\n');
                state = OUT;
            }
            break;
        }
        case IN2: {
            if (c == '*') {
                int next = getchar();
                if (next == '/') {
                    state = OUT;
                } else {
                    ungetc(next, stdin);
                }
            }
            break;
        }
        }
    }
    return 0;
}

// we have ''''//+/* */''''