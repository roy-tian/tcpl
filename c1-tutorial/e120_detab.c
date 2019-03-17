#include <stdio.h>
#include <stdlib.h>
#include "roystring.h"
#define STRING_CAPACITY 1024

int main(void) {
  FILE* fp = fopen("e120.txt", "w+");
  char str[STRING_CAPACITY] = 
    "Fly,\tfly,\tfly\tyour\tkite,\n"
    "High  \t  in   \tthe\t sky;\t\n"
    "\t  \t \t\n"
    "\tUp and \t\t down,\n"
    "   \tRound and round,\n"
    "Let \tyour\t kite fly high.";
  fprintf(fp, "ORIGINAL STRING\n");
  fprintf(fp, "=============\n");
  fprintf(fp, "%s", str);
  fprintf(fp, "\n\nDETABED STRING\n");
  fprintf(fp, "============\n");
  fprintf(fp, "%s", roy_string_detab(str, 8));
}
