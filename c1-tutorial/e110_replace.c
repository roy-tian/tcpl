#include <stdio.h>
#include "roystring.h"

int main(void) {
  char str[STRING_CAPACITY] = 
    "Let freedom ring from the mighty mountains of New York.\n"
    "Let	freedom	ring	from	the	heightening	Alleghenies	of	Pennsylvania.\n"
    "Let freedom ring from the snow-capped Rockies of Colorado.\n"
    "Let freedom ring from the curvaceous slopes of California.\n";
  printf("ORIGINAL STRING:\n%s\n", str);
  roy_string_replace_all(str, "	", "\\t");
  roy_string_replace_all(str, "\n", "\\n\n");
  printf("RESULT STRING:\n%s\n", str);
  roy_string_replace_all(str, "\\n\n", "\n");
  roy_string_replace_all(str, "\\t", " ");
  printf("REPLACE REVERSELY:\n%s\n", str);
}