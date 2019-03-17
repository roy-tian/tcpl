#include <stdio.h>
#include <stdlib.h>
#include "roystring.h"

#define STRING_CAPACITY 1024

int main(void) {
  
  FILE* fp = fopen("e118_out.txt", "w+");
  char str[STRING_CAPACITY] =
    "#include <iostream>    \n"
    "\n"
    "int main(int argc, char * argv[]) { \t  \n"
    "\tstd::cout << \"Hello world\"\n"
    "\t\t  << std::endl;\n"
    "\t\n"
    "}\n"
    "   \n";
  fprintf(fp, "ORIGINAL CODE\n");
  fprintf(fp, "=============\n");
  fprintf(fp, "%s", str);
  fprintf(fp, "\nTRIMMED CODE\n");
  fprintf(fp, "============\n");
  fprintf(fp, "%s", roy_string_trim(str));

  fclose(fp);
}