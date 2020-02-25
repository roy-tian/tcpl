#include <stdio.h>
#include <string.h>

enum { BUFFER_SIZE = 1024 };

/* Reveals all characters that 'iscntrl' .
   this function does the same things of 'replaceAll' (e110), yet faster.
   The behavior is undefined if the capacity of 'dest' is insufficient. */
char *
escape(char       * dest,
       const char * src) {
  char * pDest = dest;
  while (*src != '\0') {
    switch (*src) {
    case '\n': *pDest++ = '\\'; *pDest++ = 'n';  break;
    case '\t': *pDest++ = '\\'; *pDest++ = 't';  break;
    case '\'': *pDest++ = '\\'; *pDest++ = '\''; break;
    case '\"': *pDest++ = '\\'; *pDest++ = '\"'; break;
    case '\\': *pDest++ = '\\'; *pDest++ = '\\'; break;
    default:   *pDest++ = *src; break;
    }
    src++;
  }
  *pDest = '\0';
  return dest;
}

// Do the opposite things of escape.
char *
grab(char       * dest,
     const char * src) {
  char * pDest = dest;
  while (*src != '\0') {
    if (*src == '\\') {
      switch (*(src + 1)) {
      case 'n':  *pDest++ = '\n'; break;
      case 't':  *pDest++ = '\t'; break;
      case '\"': *pDest++ = '\"'; break;
      case '\'': *pDest++ = '\''; break;
      case '\\': *pDest++ = '\\'; break;
      case '\0': *pDest = '\0';   return dest;
      default:   *pDest++ = '\\';
                 *pDest++ = *(src + 1);
                 break;
      }
      src += 2;
    } else {
      *pDest++ = *src++;
    }
  }
  *pDest = '\0';
  return dest;
}

int main(void) {
  const char src[] = 
    "During the late 1940s and through the 1950s, UFOs were often referred to "
    "popularly as \"flying saucers\" or \'flying discs\'. \n"
    "The term\tUFO\tbecame more widespread during the 1950s, "
    "at first in technical literature, but later in popular use. \n\t\n";
  puts("ORIGINAL STRING\n===============");
  puts(src);
  char dest[BUFFER_SIZE] = "\0";
  puts("ESCAPED STRING\n==============");
  puts(escape(dest, src));
  puts("RECOVERED STRING\n================");
  puts(grab(dest, src));
}