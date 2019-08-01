#include <stdio.h>

int strend(const char * str1, const char * str2) {
  const char * pTailStr1 = str1;
  const char * pTailStr2 = str2;
  while (*++pTailStr1 != '\0') { } // end of str1
  while (*++pTailStr2 != '\0') { } // end of str2
  // tail pointers keep moving backward, until they are unequal or one of them reaches the head.
  while (*pTailStr1-- == *pTailStr2-- && pTailStr1 != str1 && pTailStr2 != str2) { }
  return (*pTailStr1 == *pTailStr2 && pTailStr2 == str2 && *pTailStr1 != '\0');
}

int main() {
  enum { STRING_CAPACITY = 255 };
  const char * str1 = "Thunder always comes after lightenning.";
  const char * str2 = "lightenning.";
  const char * str3 = "lightenning McQueen.";
  const char * str4 = "lighten";
  const char * str5 = "";
  printf("%d ", strend(str1, str2));
  printf("%d ", strend(str1, str3));
  printf("%d ", strend(str1, str4));
  printf("%d ", strend(str1, str5));
}