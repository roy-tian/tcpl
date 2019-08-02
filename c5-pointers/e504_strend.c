#include <stdio.h>

int strend(const char * str1, const char * str2) {
  const char * ptail1 = str1;
  const char * ptail2 = str2;
  while (*ptail1 != '\0') { ptail1++; } // end of str1
  while (*ptail2 != '\0') { ptail2++; } // end of str2
  // tail pointers keep moving backward, until they are unequal or one of them reaches its head.
  while (*ptail1 == *ptail2 && ptail1 != str1 && ptail2 != str2) { 
    ptail1--;
    ptail2--;
  }
  return (*ptail1 == *ptail2 && ptail2 == str2);
}

int strcmp_(const char * str1, const char * str2) {
  while (*str1 && *str2 && *str1 == *str2) { 
    str1++;
    str2++;
  }
  return *str1 - *str2;
}

size_t strlen_(const char * str) {
  const char * ptail = str;
  while (*ptail != '\0') { ptail++; }
  return ptail - str;
}

// This version is easier to understand but slower.
int strend_(const char * str1, const char * str2) {
  const char * psub = str1 + (strlen_(str1) - strlen_(str2));
  return strcmp_(psub, str2) == 0;
}

int main() {
  const char * str = "Thunder always comes after lightenning.";
  printf("%d ", strend_(str, "lightenning."));
  printf("%d ", strend_(str, "lighten"));
  printf("%d ", strend_(str, "lightenning mcqueen."));
  printf("%d ", strend_(str, ""));
  printf("%d ", strend_(str, str));
  printf("%d\n", strend_(str, "The Thunder always comes after lightenning"));

  printf("%d ", strend_(str, "lightenning."));
  printf("%d ", strend_(str, "lighten"));
  printf("%d ", strend_(str, "lightenning mcqueen."));
  printf("%d ", strend_(str, ""));
  printf("%d ", strend_(str, str));
  printf("%d\n", strend_(str, "The Thunder always comes after lightenning."));
}