#include "sort.h"
#include "roy.h"

int numcmp(const char * str1, const char * str2) {
  double num1 = atof(str1);
  double num2 = atof(str2);
  return (num1 > num2) - (num1 < num2);
}

int numcmpr(const char * str1, const char * str2) {
  return -numcmp(str1, str2);
}

char * str_tolower(char * str) {
  char * pstr = str;
  while (*pstr != '\0') {
    *pstr = tolower(*pstr);
    pstr++;
  }
  return str;
}

int strcmpi(const char * str1, const char * str2) {
  ROY_STR(str1u, strlen(str1))
  strcpy(str1u, str1);
  ROY_STR(str2u, strlen(str2))
  strcpy(str2u, str2);
  return strcmp(str_tolower(str1u), str_tolower(str2u));
}

int strcmpr(const char * str1, const char * str2) {
  return -strcmp(str1, str2);
}

int strcmpri(const char * str1, const char * str2) {
  return -strcmpi(str1, str2);
}
