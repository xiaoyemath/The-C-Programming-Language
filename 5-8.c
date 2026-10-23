/* Exercise 5-8: There is no error checking in day_of_year or month_day.
 * Remedy this defect.
 */

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: set day of year from month & day.
 * Returns -1 on invalid input. */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));

    if (month < 1 || month > 12)
        return -1;
    if (day < 1 || day > daytab[leap][month])
        return -1;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year.
 * Sets *pmonth = *pday = -1 on invalid input. */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));

    if (yearday < 1 || yearday > (leap ? 366 : 365)) {
        *pmonth = -1;
        *pday = -1;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
/* month_name */
char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"};
    return (n < 1 || n > 12) ? name[0] : name[n];
}
