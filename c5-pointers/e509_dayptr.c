#include <stdio.h>

static unsigned daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int leap_year(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 1 : 0;
}

// Returns day of year [1-366] according to month & day,
// returns 0 if month or day is invalid.
unsigned day_of_year(int year, unsigned month, unsigned day) {
  if (month < 1 || month > 12) {
    return 0;
  }
  unsigned * p = daytab[leap_year(year)];
  if (day < 1 || day > *(p + month)) {
    return 0;
  }
  while (--month) {
    day += *++p;
  }
  return day;
}

// Sets month/day according to 'year' and 'yearday'(the day of year),
// returns whether the operation is successful or not.
int month_day(int year, unsigned yearday, int * pmonth, int * pday) {
  int leap = leap_year(year);
  unsigned * p = daytab[leap];
  if ((leap && yearday > 366) || (!leap && yearday > 365)) {
    return 0;
  }
  while (yearday > *++p) {
    yearday -= *p;
  }
  *pmonth = p - daytab[leap];
  *pday = yearday;
  return 1;
}

int main(void) {
  for (int i = 1; i != 13; i++) {
    for (int j = 1; j != 32; j++) {
      printf("%3d ", day_of_year(2016, i, j));
    }
    putchar('\n');
  }
  for (int i = 1; i != 400; i++) {
    int year = 2019, month, day;
    if (month_day(year, i, &month, &day)) {
      printf("%d-%02d-%02d ", year, month, day);
    }
    if (i % 10 == 0) {
      putchar('\n');
    }
  }
}