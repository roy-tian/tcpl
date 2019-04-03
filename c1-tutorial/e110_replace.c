#include "roystring.h"
#include <stdio.h>

int main(void) {
  char str[STRING_CAPACITY] = 
    "Let freedom ring from the mighty mountains of New York.\n"
    "Let	freedom	ring	from	the	heightening	Alleghenies	of	Pennsylvania.\n"
    "Let freedom ring from the snow-capped Rockies of Colorado.\n"
    "Let freedom ring from the curvaceous slopes of California.\n";
  printf("ORIGINAL STRING:\n%s\n", str);
  roy_string_replace_all(str, "	", "\\t", true);
  roy_string_replace_all(str, "\n", "\\n\n", true);
  printf("RESULT STRING:\n%s\n", str);
  roy_string_replace_all(str, "\\n\n", "\n", true);
  roy_string_replace_all(str, "\\t", " ", true);
  printf("REPLACE REVERSELY:\n%s\n", str, true);
}