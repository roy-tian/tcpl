#include <stdio.h>

static unsigned daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int leap_year(int year) {
  return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

// Returns day of year [1-366] according to month & day,
// returns 0 if month or day is invalid.
unsigned day_of_year(int year, unsigned month, unsigned day) {
  if (month < 1 || month > 12) {
    return 0;
  }
  int leap = leap_year(year);
  if (day < 1 || day > daytab[leap][month]) {
    return 0;
  }
  for (int i = 1; i != month; i++) {
    day += daytab[leap][i];
  }
  return day;
}

void month_day(int year, unsigned _day_of_year, int * pmonth, int * pday) {
  
}