/* Exercise 4-2: Extend atof to handle scientific notation of the form
 * 123.45e-6 where a floating-point number may be followed by e or E and an
 * optionally signed exponent.
 */

#include <ctype.h>
#include <math.h>
/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;
    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        int exp_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        int exp = 0;
        for (; isdigit(s[i]); i++)
            exp = 10 * exp + (s[i] - '0');
        if (exp_sign == -1) {
            for (int j = 0; j < exp; j++)
                power *= 10;
        } else {
            for (int j = 0; j < exp; j++)
                power /= 10;
        }
    }
    return sign * val / power;
}