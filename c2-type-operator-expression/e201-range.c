#include <limits.h>
#include <math.h>
#include <stdio.h>



int main(void) {
  printf(" CHAR_BIT:  2 ^ %-2g     = %d\n", log2(CHAR_BIT),      CHAR_BIT);
  printf(" CHAR_MIN: -2 ^ %-2g     = %d\n", log2(-CHAR_MIN),     CHAR_MIN);
  printf(" CHAR_MAX:  2 ^ %-2g - 1 = %d\n", log2(CHAR_MAX + 1),  CHAR_MAX);
  printf("SCHAR_MIN: -2 ^ %-2g     = %d\n", log2(-SCHAR_MIN),    SCHAR_MIN);
  printf("SCHAR_MAX:  2 ^ %-2g - 1 = %d\n", log2(SCHAR_MAX + 1), SCHAR_MAX);
  printf("UCHAR_MAX:  2 ^ %-2g - 1 = %d\n", log2(UCHAR_MAX + 1), UCHAR_MAX);
  printf(" SHRT_MIN: -2 ^ %-2g     = %d\n", log2(-SHRT_MIN),     SHRT_MIN);
  printf(" SHRT_MAX:  2 ^ %-2g - 1 = %d\n", log2(SHRT_MAX + 1),  SHRT_MAX);
  printf("USHRT_MAX:  2 ^ %-2g - 1 = %d\n", log2(USHRT_MAX + 1), USHRT_MAX);
  printf("  INT_MIN: -2 ^ %-2Lg     = %d\n", log2l(-(INT_MIN+1)),     INT_MIN);
  printf("  INT_MAX:  2 ^ %-2Lg - 1 = %d\n", log2l(INT_MAX),  INT_MAX);
  printf(" UINT_MAX:  2 ^ %-2Lg - 1 = %u\n", log2l(UINT_MAX),  UINT_MAX);
  printf(" LONG_MIN: -2 ^ %-2Lg     = %ld\n", log2l(-(LONG_MIN+1)),     LONG_MIN);
  printf(" LONG_MAX:  2 ^ %-2Lg - 1 = %ld\n", log2l(LONG_MAX),  LONG_MAX);
  printf("ULONG_MAX:  2 ^ %-2Lg - 1 = %lu\n", log2l(ULONG_MAX),  ULONG_MAX);
  printf("LLONG_MIN: -2 ^ %-2Lg     = %ld\n", log2l(-(LLONG_MIN+1)),     LLONG_MIN);
  printf("LLONG_MAX:  2 ^ %-2Lg - 1 = %ld\n", log2l(LLONG_MAX),  LLONG_MAX);
  printf("ULLONG_MAX:  2 ^ %-2Lg - 1 = %lu\n", log2l(ULLONG_MAX),  ULLONG_MAX);
}