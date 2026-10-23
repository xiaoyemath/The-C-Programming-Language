/* Exercise 2-6: Write a function setbits(x,p,n,y) that returns x with the
 * n bits that begin at position p set to the rightmost n bits of y,
 * leaving the other bits unchanged.
 */

#include <stdio.h>
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned mask = (~(~0 << n)) << (p + 1 - n);
    return (x & ~mask) | ((y & ~(~0 << n)) << (p + 1 - n));
}