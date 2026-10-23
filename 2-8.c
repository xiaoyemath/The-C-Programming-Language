/* Exercise 2-8: Write a function rightrot(x,n) that returns the value of
 * the integer x rotated to the right by n positions.
 */

unsigned rightrot(unsigned x, int n)
{
    int wordlength = 8 * sizeof(unsigned);
    unsigned right_x = (x >> n);
    unsigned left_x = (x & ~(~0 << n));
    return (right_x | (left_x << (wordlength - n)));
}