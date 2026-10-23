#ifndef CALC_H
#define CALC_H

#define NUMBER '0'   /* signal that a number was found */
#define MATHNAME 'n' /* signal that a named command was found */
#define VARIABLE 'V' /* signal that a single-letter variable was found */
#define MAXOP 100    /* max size of operand or operator */
#define MAXVAL 100   /* maximum depth of val stack */
#define BUFSIZE 100  /* buffer size for ungetch */
#define MAXLINE 100  /* max input line length */

/* 4-6: variables A..Z and the most recently printed value */
extern double variable[26];
extern int last_was_number;
extern double last;

/* 4_stack.c */
void push(double);
double pop(void);
void peek(void);
void swap(void);
void clear(void);
void dup(void);

/* 2_(un)getch.c */
int getch(void);
void ungetch(int);
void ungets(char[]);

/* 1_getop.c */
int getop(char[]);
int getop_without_getch(char[]); /* 4-11 */

/* 3_getop(line).c */
int getop_getline(char[]); /* 4-10 */

#endif
