/* Exercise 4-3: Given the basic framework, it's straightforward to
 * extend the calculator. Add the modulus (%) operator and provisions
 * for negative numbers.
 *
 * Exercise 4-4: Add commands to print the top element of the stack
 * without popping, to duplicate it, and to swap the top two elements.
 * Add a command to clear the stack.
 *
 * Exercise 4-5: Add access to library functions like sin, exp, and pow.
 * See <math.h> in Appendix B, Section 4.
 *
 * Exercise 4-6: Add commands for handling variables. (It's easy to
 * provide twenty-six variables with single-letter names.) Add a
 * variable for the most recently printed value.
 *
 * Exercise 4-7: Write a routine ungets(s) that will push back an entire
 * string onto the input. Should ungets know about buf and bufp, or
 * should it just use ungetch?
 *
 * Exercise 4-8: Suppose that there will never be more than one character
 * of pushback. Modify getch and ungetch accordingly.
 *
 * Exercise 4-9: Our getch and ungetch do not handle a pushed-back EOF
 * correctly. Decide what their properties ought to be if an EOF is
 * pushed back, then implement your design.
 *
 * Exercise 4-10: An alternate organization uses getline to read an entire
 * input line; this makes getch and ungetch unnecessary. Revise the
 * calculator to use this approach.
 *
 * Exercise 4-11: Modify getop so that it doesn't need to use ungetch.
 * Hint: use an internal static variable.
 */

#include <stdio.h>
#include "getline.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h> /* for atof() */
#include <string.h> /* for strcmp() */

#define MAXOP 100    /* max size of operand or operator */
#define NUMBER '0'   /* signal that a number was found */
#define MATHNAME 'n' /* signal that a named command was found */
#define MAXVAL 100   /* maximum depth of val stack */
#define BUFSIZE 100  /* buffer size for ungetch */
#define VARIABLE 'V'
#define MAXLINE 100 /* max input line length */

int getop(char[]);
int getop_without_getch(char[]);
void push(double);
double pop(void);
double variable[26]; /* variables A..Z */
int last_was_number;
double last;
void peek(void);
void swap(void);
void clear(void);
void dup(void);
int getch(void);
void ungetch(int);

/* reverse Polish calculator */
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

/* Exercise 4-6: Add commands for handling variables. (It's easy to provide
 * twenty-six variables with single-letter names.) Add a variable for the
 * most recently printed value.
 */

/* stack */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
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

/* peek: print top of stack without popping */
void peek(void)
{
    if (sp > 0)
        printf("top of stack: %g\n", val[sp - 1]);
    else
        printf("stack empty\n");
}

/* swap: swap the top two stack elements */
void swap(void)
{
    double temp;
    if (sp > 1) {
        temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    }
}

/* clear: empty the stack */
void clear(void)
{
    int i;
    sp = 0;
    for (i = 0; i < 26; i++)
        variable[i] = 0.0;
}

/* dup: push a copy of the top element */
void dup(void)
{
    if (sp > 0)
        push(val[sp - 1]);
    else
        printf("stack empty\n");
}

/* Exercise 4-4: Add the commands to print the top elements of the stack
 * without popping, to duplicate it, and to swap the top two elements.
 * Add a command to clear the stack.
 */

/* Exercise 4-11: Modify getop so that it doesn't need to use ungetch.
 * Hint: use an internal static variable.
 */

int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (isalpha(c)) {
        i = 0;
        while (isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        if (i == 1 && isupper(s[0]))
            return VARIABLE;
        return MATHNAME;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */

    i = 0;
    if (c == '-') {
        if (isdigit(c = getch()) || c == '.')
            s[++i] = c; /* keep '-' in s[0], store first digit at s[1] */
        else {
            if (c != EOF)
                ungetch(c);
            return '-'; /* minus operator */
        }
    }
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
char line[MAXLINE];
int lp = 0;
int getop_getline(char s[])
{
    if (line[lp] == '\0') {
        if (getline(line, MAXLINE) == 0)
            return EOF;
        lp = 0;
    }
    while ((s[0] = c = line[lp++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    if (isalpha(c)) {
        i = 0;
        while (isalpha(s[++i] = c = line[lp++]))
            ;
        s[i] = '\0';
        lp--;
        if (i == 1 && isupper(s[0]))
            return VARIABLE;
        return MATHNAME;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    i = 0;
    if (c == '-') {
        c = line[lp++];
        if (isdigit(c) || c == '.')
            s[++i] = c;
        else {
            lp--;
            return '-'; /* minus operator */
        }
    }
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = line[lp++]))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = line[lp++]))
            ;
    s[i] = '\0';
    lp--;
    return NUMBER;
}

int getop_without_getch(char s[])
{
    int i, c;
    static int lastc = EOF;
    if (lastc != EOF) {
        c = lastc;
        lastc = EOF;
    } else
        c = getchar();
    while (c == ' ' || c == '\t')
        c = getchar();
    s[0] = c;
    s[1] = '\0';
    if (isalpha(c)) {
        i = 0;
        while (isalpha(s[++i] = c = getchar()))
            ;
        s[i] = '\0';
        if (c != EOF)
            lastc = c;
        if (i == 1 && isupper(s[0]))
            return VARIABLE;
        return MATHNAME;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-') {
        c = getchar();
        if (isdigit(c) || c == '.')
            s[++i] = c;
        else {
            if (c != EOF)
                lastc = c;
            return '-'; /* minus operator */
        }
    }
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        lastc = c;
    return NUMBER;
}
void ungets(char s[])
{
    int i;
    for (i = strlen(s) - 1; i >= 0; i--)
        ungetch(s[i]);
}
/* Exercise 4-7: Write a routine ungets(s) that will push back an entire
 * string onto the input. Should ungets know about buf and bufp, or should
 * it just use ungetch?
 */

/* Exercise 4-10: An alternate organization uses getline to read an entire
 * input line; this makes getch and ungetch unnecessary. Revise the
 * calculator to use this approach.
 */

int buf[BUFSIZE]; // int buf;
int bufp = 0;     // int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
    /*  int c;
        if(bufp > 0){
            bufp = 0;
            c = buf;
        }else
            c = getchar();
        return c;
    */
}
/* Exercise 4-9: Our getch and ungetch do not handle a pushed-back EOF
 * correctly. Decide what their properties ought to be if an EOF is pushed
 * back, then implement your design.
 */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
    /*  buf = c;
        bufp = 1;
    */
}
/* Exercise 4-8: Suppose that there will never be more than one character
 * of pushback. Modify getch and ungetch accordingly.
 */