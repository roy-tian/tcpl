#include "../roystring.h"

#define TAB_SIZE 4

int main(void) {
  char str[STRING_CAPACITY] =
    "def ask_ok(prompt, retries = 4, reminder = 'Please try again!'):\n"
    "while True:\n"
    "    ok = input(prompt)\n"
    "    if ok in ('y', 'ye', 'yes'):          \t        \n"
    "        return   True\n"
    "    if ok in ('n', 'no', 'nop', 'nope'):\t         \t\n"
    "        return   False\n"
    "    retries = retries - 1\n"
    "    if retries < 0:\n"
    "        raise\tValueError('invalid user response')\n"
    "    print(reminder)";
  const char * file_name = "e121.txt";

  roy_string_write_to_file("ORIGINAL CODE:\n=============\n", file_name);
  roy_string_append_to_file(str, file_name);
  roy_string_append_to_file("\n\nAFTER ENTAB:\n=============\n", file_name);
  roy_string_append_to_file(roy_string_entab(str, TAB_SIZE), file_name);
}
