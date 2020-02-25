#include <stdio.h>
#include <stdlib.h>
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

// Why #define, not inline function?

// Deprecated: 'atof' / 'strtod' are more effective.
double parseDouble(const char * str) {
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
  int pnExpo = (*str == '-' ? -1 : 1);
  STR_INC("+-", str)
  double nexpo = 0.0;
  STR_TO_INT(nexpo, str)
  expo *= pow(10.0, pnExpo * nexpo);
  return pn * result * expo;
}

int main(void) {
  const char buf[] = "  1234.5678e-09";
  printf("%.10g\n", atof(buf));
  printf("%.10g\n", strtod(buf, NULL));
  printf("%.10g\n", parseDouble(buf));
}