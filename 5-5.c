/* Exercise 5-5: Write versions of the library functions strncpy, strncat,
 * and strncmp, which operate on at most the first n characters of their
 * argument strings. For example, strncpy(s,t,n) copies at most n
 * characters of t to s. Full descriptions are in Appendix B.
 */
#include <string.h>

char *strncpy(char *s, const char *t, size_t n)
{
    char *start = s;
    while (n > 0 && (*s = *t) != '\0') {
        s++;
        t++;
        n--;
    }
    while (n-- > 0)
        *s++ = '\0';
    return start;
}

char *strncat(char *s, const char *t, size_t n)
{
    char *start = s;
    while (*s)
        s++;
    while (n-- > 0 && (*s++ = *t++) != '\0')
        ;
    *s = '\0';
    return start;
}

int strncmp(const char *s, const char *t, size_t n)
{
    for (; n > 0; s++, t++, n--) {
        if (*s != *t)
            return *s - *t;
        if (*s == '\0')
            return 0;
    }
    return 0;
}
