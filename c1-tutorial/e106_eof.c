#include <stdio.h>

int main(void) {
  int c;
  while ((c = getchar()) != EOF) {
    printf("'%c' : %d\t'%c' == EOF : %d\n", c, c, c, c == EOF);
  }
}