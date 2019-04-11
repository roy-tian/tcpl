#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c =s[i];
    s[i]=s[j];
    s[j] =c;
  }
}

void itoa(int n, char s[]) {
  int i, sign;
  if ((sign = n) < 0) /* record sign */
    n = -n; /* make n positive */
  i = 0;
  do { /* generate digits in reverse order */
    s[i++] =n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] ='\0';
  reverse(s);
}

int main(void) {
  char str[200];
  itoa(INT_MIN, str);
  printf("%lld", LLONG_MIN);
  puts(str);
}