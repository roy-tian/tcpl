#include "roy.h"

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
    *ntail = 10;
  }
  int ret = 0;
  if (argc == 3 && (ret = tail(argv[1])) != -1) {
    *fileName = argv[2];
    *ntail = ret;
  }
  if (argc == 3 && (ret = tail(argv[2])) != -1) {
    *fileName = argv[1];
    *ntail = ret;
  }
  return *fileName;
}

int main(int argc, char ** argv) {
  const char * fileName = NULL;
  int ntail = 0;
  if ( !parseArgs(argc, argv, &fileName, &ntail) ) {
    perror(fileName);
    exit(EXIT_FAILURE);
  }
  RoyString * str = roy_string_read_file(fileName);
  RoyDeque * deque = roy_deque_new((ROperate)roy_string_delete);
  roy_string_split(deque, str, "\n");

  size_t lineCount = roy_deque_size(deque);
  if (ntail > lineCount) {
    ntail = lineCount;
  }
  for (int i = lineCount - ntail; i != lineCount; i++) {
    roy_string_println(roy_deque_at(deque, i, RoyString));
  }
}