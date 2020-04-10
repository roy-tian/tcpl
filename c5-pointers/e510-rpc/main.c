/* you will need roylib to compile this file, like this:
 * cc *.c -L"PATH_TO_ROYLIB" -lroylib lpcre2-8
 */

#include "rpc.h"

int main(int argc, char ** argv) {
  if (argc > 1) {
    populate();
    RoyDeque * args = roy_deque_new((ROperate)roy_string_delete);
    for (int i = 1; i < argc; i++) {
      roy_deque_push_back(args, roy_string_new(argv[i]));
    }
    rpc(args);
    roy_deque_delete(args, NULL);
    roy_map_delete(operators, NULL);
  }
}