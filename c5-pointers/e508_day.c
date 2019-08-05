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

int month_day(int year, unsigned _day_of_year, int * pmonth, int * pday) {
  int leap = leap_year(year);
  if (leap && _day_of_year > 366 || !leap && _day_of_year > 365) {
    return 0;
  }
  int i = 1;
  for (; _day_of_year > daytab[leap][i]; i++) {
    _day_of_year -= daytab[leap][i];
  }
  *pmonth = i;
  *pday = _day_of_year;
  return 1;
}

int main() {
  for (int i = 1; i != 13; i++) {
    for (int j = 1; j != 32; j++) {
      printf("%d ", day_of_year(2016, i, j));
    }
    printf("\n");
  }
  for (int i = 1; i != 400; i++) {
    int year = 2019, month, day;
    if (month_day(year, i, &month, &day)) {
      printf("%d-%02d-%02d ", year, month, day);
    }
    if (i % 10 == 0) {
      puts("");
    }
  }
}