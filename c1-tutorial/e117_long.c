#include <stdio.h>
#include "roystring.h"

#define WIDTH 80

int main(void) {
  char str[] =
    "The C language also exhibits the following characteristics:\n"
    "There is a small, fixed number of keywords, including a full set of control flow primitives: for, if/else, while, switch, and do/while. User-defined names are not distinguished from keywords by any kind of sigil.\n"
    "There are a large number of arithmetical and logical operators, such as +, +=, ++, &, ~, etc.\n"
    "More than one assignment may be performed in a single statement.\n"
    "Function return values can be ignored wheWIDTH needed.\n"
    "Typing is static, but weakly enforced: all data has a type, but implicit conversions may be performed.\n"
    "Declaration syntax mimics usage context. C has no \"define\" keyword; instead, a statement beginning with the name of a type is taken as a declaration. There is no \"function\" keyword; instead, a function is indicated by the parentheses of an argument list.\n"
    "User-defined (typedef) and compound types are possible.\n"
    "Low-level access to computer memory is possible by converting machine addresses to typed pointers.\n"
    "Procedures are a special case of function, with an untyped return type void.";
    for (int i = 1; i < roy_string_count_line(str); i++) {
      if (roy_string_line_length(str, i) > WIDTH) {
        char cur_line[STRING_CAPACITY] = {'\0'};
        printf("[%2d]%s\n", i, roy_string_get_line(cur_line, str, i));
      }
    }
}