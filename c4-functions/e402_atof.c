#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define STR_TO_INT(num, str)      \
        while (isdigit(*str)) {   \
          num *= 10.0;            \
          num += *str++ - '0';    \
        }

#define STR_INC(set, str)         \
        if (strchr(set, *str)) {  \
          str++;                  \
        }

double roy_parse_double(const char * str) {
  str += strspn(str, " \t");
  double result = 0.0;
  int pn = (*str == '-' ? -1 : 1);
  STR_INC("+-", str)
  STR_TO_INT(result, str)
  STR_INC(".", str)
  const char * pstr = str;
  double expo = 1.0;
  STR_TO_INT(result, str)
  expo /= pow(10, str - pstr);
  STR_INC("eE", str)
  int pn_expo = (*str == '-' ? -1 : 1);
  STR_INC("+-", str)
  double nexpo = 0.0;
  STR_TO_INT(nexpo, str)
  expo *= pow(10.0, pn_expo * nexpo);
  return pn * result * expo;
}

int main(void) {
  printf("%.10g\n", atof(" 1234.5678e-9"));
  printf("%.10g", roy_parse_double(" 1234.5678e-9"));
}