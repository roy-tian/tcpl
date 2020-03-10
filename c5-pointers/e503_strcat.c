#include <stdio.h>
#include <stdlib.h>

enum { BUFFER_SIZE = 128 };

// Deprecated: this version won't be more effective than the std one.
char * strcat_(char * dest, const char * src) {
  char * ptail = dest;
  while (*ptail != '\0') { ptail++; }
  while ((*ptail++ = *src++) != '\0') { }
  return dest;
}

size_t strlen_(const char * str) {
  const char * ptail = str;
  while (*ptail != '\0') { ptail++; }
  return ptail - str;
}

char * stralloc_(const char * src) {
  char * dest = calloc(strlen_(src) + 1, sizeof(char));
  char * pdest = dest;
  while ((*pdest++ = *src++) != '\0') { }
  return dest;
}

// This version won't be bothered with undefined behavior.
char * strcat_m(char ** dest, const char * src) {
  char * temp = stralloc_(*dest);
  char * ptemp = temp;
  *dest = realloc(*dest, strlen_(*dest) + strlen_(src) + 1);
  char * pdest = *dest;
  while ((*pdest = *ptemp) != '\0') {
    pdest++;
    ptemp++;
  }

  while ((*pdest++ = *src++) != '\0') { }
  free(temp);
  return *dest;
}

int main(void) {
  char str1[BUFFER_SIZE] = "Chinese is ";
  char str2[BUFFER_SIZE] = "the most beautiful language in the world.";

  puts(strcat_(str1, str2));

  char * str3 = stralloc_("Le chinois est ");
  char * str4 = stralloc_("la plus belle langue du monde.");
  
  puts(strcat_m(&str3, str4)); 
}