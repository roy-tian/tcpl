#include "../roystring.h"
#include <stdio.h>

int main(void) {
  char str[] =
    "Monsieur Miroir marchand d’habits,"
    "est mort hier soir à Paris."
    "Il fait nuit,"
    "Il fait noir,"
    "Il fait nuit noire à Paris...";
  for (int i = 'a'; i <= 'z'; i++) {
    int count_cur = roy_string_count_char(str, i) +
                    roy_string_count_char(str, i - 32); // 'a' - 'A' == 32
    if (count_cur != 0) {
      printf("%c: %d\n", i, count_cur);
    }
  }
}