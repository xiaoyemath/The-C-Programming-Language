#include "calc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            last_was_number = 1;
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 == 0.0)
                printf("error: zero divisor for modulo\n");
            else
                push((int)pop() % (int)op2);
            break;
        /* Exercise 4-3: Add the modulus (%) operator and provisions for
         * negative numbers. (Negative-number handling is in getop below.)
         */
        case MATHNAME:
            if (strcmp(s, "sin") == 0)
                push(sin(pop()));
            else if (strcmp(s, "cos") == 0)
                push(cos(pop()));
            else if (strcmp(s, "pow") == 0) {
                op2 = pop();
                push(pow(pop(), op2));
            } else if (strcmp(s, "peek") == 0)
                peek();
            else if (strcmp(s, "swap") == 0)
                swap();
            else if (strcmp(s, "clear") == 0)
                clear();
            else if (strcmp(s, "dup") == 0)
                dup();
            else if (strcmp(s, "last") == 0)
                push(last);
            else
                printf("error: unknown command %s\n", s);
            break;
            /* Exercise 4-5: Add access to library functions like sin, exp, and
             * pow. See <math.h> in Appendix B, Section 4.
             */

        case VARIABLE:
            if (last_was_number) {
                variable[s[0] - 'A'] = pop();
                last_was_number = 0;
            } else {
                push(variable[s[0] - 'A']);
            }
            break;

        case '\n':
            last = pop();
            printf("\t%.8g\n", last);
            last_was_number = 0;
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}