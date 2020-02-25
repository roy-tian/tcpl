#include <stdio.h>

const struct EscapeSequence {
  int sequenceNumber;
  char * sequenceString;
  char * description;
} sequences[] = {
  '\'', "\\'",	"single quote",
  '\"', "\\\"",	"double quote",
  '\?', "\\?",	"question mark",
  '\\', "\\\\",	"backslash itself",
  '\a', "\\a",	"audible bell",
  '\b', "\\b",	"backspace",
  '\f', "\\f",	"form feed - new page",
  '\n', "\\n",	"line feed - new line",
  '\r', "\\r",	"carriage return",
  '\t', "\\t",	"horizontal tab",
  '\v', "\\v",	"vertical tab",
  '\047', "\\047", "arbitrary octal value",
  '\x47', "\\x47", "arbitrary hexadecimal value",
  '\0'
};

/* LOOK DEEP AND THINK:
 * how structs organize there data.
 */

int main(void) {
  puts("------+------+------------------------------");
  puts("VALUE | FORM | DESCRIPTION");
  puts("------+------+------------------------------");
  size_t length = sizeof(sequences) / sizeof(struct EscapeSequence) - 1;  
  for (int i = 0; i != length; i++) {
    printf("   %2d | %4s | %s\n", 
           sequences[i].sequenceNumber,
           sequences[i].sequenceString,
           sequences[i].description);
  }
  puts("------+------+------------------------------");
  // printf("\c");    // complie warning: unknown escape sequence. (undefined behavior)
}
