/* Exercise 5-4: Write the function strend(s,t), which returns 1 if the
 * string t occurs at the end of the string s, and zero otherwise.
 */
int strlen(char *s)
{
    char *p = s;
    while (*p != '\0')
        p++;
    return p - s;
}

int strend(char *s, char *t)
{
    int ls = strlen(s);
    int lt = strlen(t);

    if (lt > ls)
        return 0;

    s += ls - lt;
    while (*s++ == *t++)
        if (*t == '\0')
            return 1;
    return 0;
}
