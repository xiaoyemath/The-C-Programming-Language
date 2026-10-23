/* Exercise 5-9: Rewrite the routines day_of_year and month_day with
 * pointers instead of indexing.
 */

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: set day of year from month & day.
 * Returns -1 on invalid input. */
int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));

    if (month < 1 || month > 12)
        return -1;
    if (day < 1 || day > *(daytab[leap] + month))
        return -1;

    /* p 从 1 月开始，走到第 month-1 个月为止 */
    for (p = daytab[leap] + 1; p < daytab[leap] + month; p++)
        day += *p;
    return day;
}

/* month_day: set month, day from day of year.
 * Sets *pmonth = *pday = -1 on invalid input. */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p;

    leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));

    if (yearday < 1 || yearday > (leap ? 366 : 365)) {
        *pmonth = -1;
        *pday = -1;
        return;
    }

    for (p = daytab[leap] + 1; yearday > *p; p++)
        yearday -= *p;
    *pmonth = p - daytab[leap];   /* 月号 = 指针偏移量 */
    *pday = yearday;
}
