#include <stdio.h>
#define STRING_CAPACITY 1024

// Reveals all characters that 'iscntrl' .
// this function does the same things of 'roy_string_replace_all()' yet faster.
// The behavior is undefined if the capacity of 'dest' is insuffient.
char * escape(char * dest, const char * src) {
  char * pdest = dest;
  while (*src != '\0') {
    switch (*src) {
    case '\n':
      *pdest++ = '\\';
      *pdest++ = 'n';
      break;
    case '\t':
      *pdest++ = '\\';
      *pdest++ = 't';
      break;
    case '\'':  
      *pdest++ = '\\';
      *pdest++ = '\'';
      break;
    case '\"':  
      *pdest++ = '\\';
      *pdest++ = '\"';
      break;
    case '\\':  
      *pdest++ = '\\';
      *pdest++ = '\\';
      break;
    default:
      *pdest++ = *src;
      break;
    }
    src++;
  }
  *pdest = '\0';
  return dest;
}

int main(void) {
  const char str[STRING_CAPACITY] = 
    "During the late 1940s and through the 1950s, UFOs were often referred to "
    "popularly as \"flying saucers\" or \'flying discs\'. \n"
    "The term\tUFO\tbecame more widespread during the 1950s, "
    "at first in technical literature, but later in popular use. \n\t\n";
  puts("ORIGINAL STRING\n===============");
  puts(str);
  char esc_str[STRING_CAPACITY] = {'\0'};
  escape(esc_str, str);
  puts("ESCAPED STRING\n==============");
  puts(esc_str);
}