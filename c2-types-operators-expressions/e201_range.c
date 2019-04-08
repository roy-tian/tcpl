#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

void integer_limits(void);
void integer_bitwise(void);
void float_limits(void);

void integer_limits(void) {
  printf("  CHAR_BIT |  2 ^ %2g     | %20d | %16X\n",
         log2(CHAR_BIT), CHAR_BIT, CHAR_BIT);
  printf("  CHAR_MIN | -2 ^ %2g     | %20d | %16X\n",
         log2(-CHAR_MIN), CHAR_MIN, CHAR_MIN);
  printf("  CHAR_MAX |  2 ^ %2g - 1 | %20d | %16X\n",
         log2(CHAR_MAX + 1), CHAR_MAX, CHAR_MAX);
  printf(" UCHAR_MAX |  2 ^ %2g - 1 | %20d | %16X\n",
         log2(UCHAR_MAX + 1), UCHAR_MAX, UCHAR_MAX);
  printf("  SHRT_MIN | -2 ^ %2g     | %20d | %16X\n",
         log2(-SHRT_MIN), SHRT_MIN, SHRT_MIN);
  printf("  SHRT_MAX |  2 ^ %2g - 1 | %20d | %16X\n",
         log2(SHRT_MAX + 1), SHRT_MAX, SHRT_MAX);
  printf(" USHRT_MAX |  2 ^ %2g - 1 | %20d | %16X\n",
         log2(USHRT_MAX + 1), USHRT_MAX, USHRT_MAX);
  printf("   INT_MIN | -2 ^ %2g     | %20d | %16X\n",
         log2(-(INT_MIN+1)), INT_MIN, INT_MIN);
  printf("   INT_MAX |  2 ^ %2g - 1 | %20d | %16X\n",
         log2(INT_MAX), INT_MAX, INT_MAX);
  printf("  UINT_MAX |  2 ^ %2g - 1 | %20u | %16X\n",
         log2(UINT_MAX),  UINT_MAX, UINT_MAX);
  printf("  LONG_MIN | -2 ^ %2g     | %20ld | %16lX\n",
         log2(-(LONG_MIN + 1)), LONG_MIN, LONG_MIN);
  printf("  LONG_MAX |  2 ^ %2g - 1 | %20ld | %16lX\n",
         log2(LONG_MAX), LONG_MAX, LONG_MAX);
  printf(" ULONG_MAX |  2 ^ %2g - 1 | %20lu | %16lX\n",
         log2(ULONG_MAX), ULONG_MAX, ULONG_MAX);
  printf(" LLONG_MIN | -2 ^ %2g     | %20lld | %16llX\n",
         log2(-(LLONG_MIN+1)), LLONG_MIN, LLONG_MIN);
  printf(" LLONG_MAX |  2 ^ %2g - 1 | %20lld | %16llX\n",
         log2(LLONG_MAX), LLONG_MAX, LLONG_MAX);
  printf("ULLONG_MAX |  2 ^ %2g - 1 | %20llu | %16llX\n",
         log2(ULLONG_MAX), ULLONG_MAX, ULLONG_MAX);
}

void integer_bitwise(void) {
  printf("   INT_MIN | -(~0U   >> 1) - 1 | %20d | %16X\n",
         -(~0U >> 1) - 1, -(~0U >> 1) - 1);
  printf("   INT_MAX |   ~0U   >> 1      | %20d | %16X\n",
         ~0U >> 1, ~0U >> 1);
  printf("  UINT_MAX |   ~0U             | %20u | %16X\n",
         ~0U, ~0U);
  printf("  LONG_MIN | -(~0UL  >> 1) - 1 | %20ld | %16lX\n",
         -(~0UL >> 1) - 1, -(~0UL >> 1) - 1);
  printf("  LONG_MAX |   ~0UL  >> 1      | %20ld | %16lX\n",
         ~0UL >> 1, ~0UL >> 1);
  printf(" ULONG_MAX |   ~0UL            | %20lu | %16lX\n",
         ~0UL, ~0UL);
  printf(" LLONG_MIN | -(~0ULL >> 1) - 1 | %20lld | %16llX\n",
         -(~0ULL >> 1) - 1, -(~0ULL >> 1) - 1);
  printf(" LLONG_MAX |   ~0ULL >> 1      | %20lld | %16llX\n",
         ~0ULL >> 1, ~0ULL >> 1);
  printf("ULLONG_MAX |   ~0ULL           | %20llu | %16llX\n",
         ~0ULL, ~0ULL);
}

void float_limits(void) {
  printf(" FLT_MIN | %.36g\n", FLT_MIN);
  printf(" FLT_MAX | %.36g\n", FLT_MAX);
  printf(" DBL_MIN | %.36g\n", DBL_MIN);
  printf(" DBL_MAX | %.36g\n", DBL_MAX);
  printf("LDBL_MIN | %.36Lg\n", LDBL_MIN);
  printf("LDBL_MAX | %.36Lg\n", LDBL_MAX);
}

int main(void) {
  integer_limits();
  printf("\n");
  integer_bitwise();
  printf("\n");
  float_limits();
}