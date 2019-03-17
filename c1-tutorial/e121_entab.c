#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roystring.h"
#define STRING_CAPACITY 1024

int main(void) {
  FILE* fp = fopen("e121.txt", "r+");
  char str[STRING_CAPACITY] =
    "def ask_ok(prompt, retries = 4, reminder = 'Please try again!'):\n"
    "while True:\n"
    "    ok = input(prompt)\n"
    "    if ok in ('y', 'ye', 'yes'):\n"
    "        return   True\n"
    "    if ok in ('n', 'no', 'nop', 'nope'):\n"
    "        return   False\n"
    "    retries = retries - 1\n"
    "    if retries < 0:\n"
    "        raise    ValueError('invalid user response')\n"
    "    print(reminder)";
  fprintf(fp, "ORIGINAL CODE:\n%s", str);
  fprintf(fp, "\n\nAFTER ENTAB:\n%s", roy_string_entab(str, 4));
}
