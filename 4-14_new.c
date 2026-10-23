/* Exercise 4-14: Define a macro swap(t,x,y) that interchanges two
 * arguments of type t. (Block structure will help.)
 */

#include <stdio.h>

#define swap(t, x, y) \
    do {              \
        t _z;         \
        _z = x;       \
        x = y;        \
        y = _z;       \
    } while (0)

int main(void)
{
    int a = 1, b = 2;
    printf("before: a=%d b=%d\n", a, b);

    if (a < b)
        swap(int, a, b);
    else
        printf("no swap\n");

    printf("after:  a=%d b=%d\n", a, b);

    double x = 3.14, y = 2.71;
    swap(double, x, y);
    printf("double: x=%g y=%g\n", x, y);

    return 0;
}
