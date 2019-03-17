#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roystring.h"
#define STRING_CAPACITY 1024

int main(void) {
  FILE* fp = fopen("e121.txt", "r+");
  if(!fp) {
    perror("File opening failed.");
    return EXIT_FAILURE;
  }
  char str[STRING_CAPACITY] = {'\0'};
  char cur_line[STRING_CAPACITY] = {'\0'};
  while (fgets(cur_line, STRING_CAPACITY, fp) != NULL) {
    strcat(str, cur_line);
  }
  printf("%s", str);
  fp = freopen("e121.txt", "a+", fp);
  fprintf(fp, "\n\nAFTER ENTAB:\n%s", str);
}
