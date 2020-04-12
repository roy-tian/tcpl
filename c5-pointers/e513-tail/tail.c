#include "roy.h"

#define DEFAULT_NLINE 10

int tail(const char * arg) {
  if (*arg != '-') {
    return -1;
  }
  char * end;
  int ret = strtol(arg + 1, &end, 0);
  if (arg + 1 == end) {
    return -1;
  }
  return ret;
}

bool parseArgs(int argc, char ** argv, const char ** fileName, int * ntail) {
  if (argc == 2 && argv[1][0] != '-') {
    *fileName = argv[1];
    *ntail = DEFAULT_NLINE;
    return true;
  }
  if (argc == 3 && (*ntail = tail(argv[1])) != -1) {
    *fileName = argv[2];
    return true;
  }
  if (argc == 3 && (*ntail = tail(argv[2])) != -1) {
    *fileName = argv[1];
    return true;
  }
  return false;
}

int main(int argc, char ** argv) {
  const char * fileName;
  int ntail = 0;
  RoyString * str;
  if ( !parseArgs(argc, argv, &fileName, &ntail) ||
       !(str = roy_string_read_file(fileName)) ) {
    perror("Error");
    exit(EXIT_FAILURE);
  }
  RoyDeque * deque = roy_deque_new((ROperate)roy_string_delete);
  roy_string_split(deque, str, "\n");

  size_t lineCount = roy_deque_size(deque);
  if (ntail > lineCount) {
    ntail = lineCount;
  }
  for (int i = lineCount - ntail; i != lineCount; i++) {
    roy_string_println(roy_deque_at(deque, i, RoyString));
  }
  roy_deque_delete(deque, NULL);
}