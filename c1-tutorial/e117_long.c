#include <string.h>
#include <stdio.h>

size_t
countChar(const char * str,
          int          ch) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == ch) {
      count ++;
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

char * lineContent(char       * lineContent,
                   const char * str,
                   size_t       lineNumber) {
  while ((lineNumber-- > 1) && strchr(str, '\n')) {
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  const char * strTail = strchr(str, '\n');
  if (!strTail) {
    strcpy(lineContent, str);
  } else {
    strncpy(lineContent, str, strTail - str);
  }
  return lineContent;
}

int main(void) {
  const char str[] =
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

  enum {
    BUFFER_SIZE = 512,
    WIDTH = 80
  };

  for (int i = 1; i < countLine(str); i++) {
    if (lineLength(str, i) > WIDTH) {
      char curLine[BUFFER_SIZE] = "\0";
      lineContent(curLine, str, i);
      printf("[LINE NO %d | LENGTH %zu]\n\t%s\n", i, strlen(curLine), curLine);
    }
  }
}