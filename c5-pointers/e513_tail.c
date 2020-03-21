#include "roy.h"

const char * fileName(int argc, char ** argv) {
  if (argc == 2 && *argv[1] != '-') {
    return (const char *)argv[1];
  }
  if (argc == 3) {
    if (*argv[1] == '-' && *argv[2] != '-') {
      return (const char*)argv[2];
    }
    if (*argv[1] != '-' && *argv[2] == '-') {
      return (const char*)argv[1];
    }
  }
  return NULL;
}

int ntail(int argc, char ** argv) {
  if (argc == 2 && *argv[1] != '-') {
    return 10;
  }
  if (argc == 3) {
    if (*argv[1] == '-') {
      return (int)strtol(argv[1] + 1, NULL, 0);
    }
    if (*argv[2] == '-') {
      return (int)strtol(argv[2] + 1, NULL, 0);
    }
  }
  return 0;
}

int main(int argc, char ** argv) {
  RoyString * str = roy_string_read_file(fileName(argc, argv));
  RoyDeque * deque = roy_deque_new((ROperate)roy_string_delete);
  roy_string_split(deque, str, "\n");
  size_t lineCount = roy_deque_size(deque);
  for (int i = lineCount - ntail(argc, argv); i != lineCount; i++) {
    roy_string_println(roy_deque_at(deque, i, RoyString));
  }
}