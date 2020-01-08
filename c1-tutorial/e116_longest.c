#include <stdio.h>
#include <string.h>

size_t countChar(const char * str, int ch);
size_t countLine(const char * str);
size_t lineLength(const char * str, size_t lineNumber);
char * lineContent(char * dest, const char * str, size_t lineNumber);

size_t
countChar(const char * str,
          int          ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count++;
    }
  }
  return count;
}

size_t
countLine(const char * str) {
  size_t strLength = strlen(str);
  size_t count = countChar(str, '\n');
  if (strLength != 0 && *(str + strLength - 1) != '\n') {
    // last char is not '\n', but that line still needs to be counted.
    count++;
  }
  return count;
}

size_t
lineLength(const char * str,
           size_t       lineNumber) {
  while ((lineNumber-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  const char * strTail = strchr(str, '\n');
  if (!strTail) {
    return strlen(str);
  } else {
    return strTail - str;
  }
}

char *
lineContent(char       * dest,
            const char * str,
            size_t       lineNumber) {
  while ((lineNumber-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  const char * strTail = strchr(str, '\n') ;
  strncpy(dest, str, strTail - str);
  return dest;
}

int main(void) {
  const char str[] =
    "I have a cat,\n"
    "Its name is Tit;\n"
    "And by this fire\n"
    "It Loves to sit.\n"
    "\n"
    "From off the rug\n"
    "It scarce will stir,\n"
    "But there will sit\n"
    "All day and purr.\n"
    "\n"
    "Each day I bring\n"
    "Its dish of milk,\n"
    "And smooth its coat\n"
    "To shine like silk.\n"
    "\n"
    "And on my knee\n"
    "It oft will sit;\n"
    "And I love it.";
  int maxLength = 0, maxLine = 1;
  for (int i = 1; i <= countLine(str); i++) {
    int currentLength = lineLength(str, i);
    if (currentLength > maxLength) {
      maxLength = currentLength;
      maxLine = i;
    }
    printf("WORDS OF LINE %2d: %2d\n", i, currentLength);
  }
  char longest[maxLength + 1];
  printf("\nLONGEST LINE [%d]: ", maxLine);
  printf("%s\n", lineContent(longest, str, maxLine));
  printf("   ITS LENGTH IS: %2d\n", maxLength);
}