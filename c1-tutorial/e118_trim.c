#include "../roystring.h"

int main(void) {
  char str[STRING_CAPACITY] =
    "#include <iostream>    \n"
    "\n"
    "int main(int argc, char * argv[]) { \t          \n"
    "\tstd::cout << \"Hello world\"    \t    \n"
    "\t\t  << std::endl;      \t\n"
    "\t\n"
    "}"
    "   \n\t\n\n\n   \n\n\n    ";
  const char * file_name = "e118.txt";

  roy_string_write_to_file("ORIGINAL CODE\n=============\n", file_name);
  roy_string_append_to_file(str, file_name);
  roy_string_append_to_file("\nTRIMMED CODE\n============\n", file_name);
  roy_string_append_to_file(roy_string_trim(str), file_name);
}