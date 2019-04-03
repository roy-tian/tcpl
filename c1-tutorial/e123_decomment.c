#include "roystring.h"

int main() {
  ROY_STRING(str, STRING_CAPACITY_HUGE)
  roy_string_read_from_file(str, "e123.java");
  roy_string_replace_between(str, "/*", "*/", "");
  roy_string_replace_between(str, "//", "\n", "\n");
  roy_string_write_to_file(str, "e123dc.java");
}