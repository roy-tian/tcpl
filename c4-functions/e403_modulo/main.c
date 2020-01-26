/* you will need roylib to compile this file, like this:
 * cc *.c -L"PATH_TO_ROYLIB" -lroylib
 */

#include "number.h"
#include "math.h"

int main(void) {
  RoyString * s1 = roy_string_new_double(5);
  RoyString * s2 = roy_string_new_double(0);
  RoyString * s3 = roy_string_new(NULL);
  modulo(s3, s1, s2);
  roy_string_println(s3);
}