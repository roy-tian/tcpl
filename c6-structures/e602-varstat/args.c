#include "varstat.h"

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

bool
parseArgs(int           argc, 
          char       ** restrict argv, 
          const char ** restrict fileName, 
          int         * restrict nsame_) {
  if (argc == 2 && argv[1][0] != '-') {
    *fileName = argv[1];
    *nsame_ = DEFAULT_NSAME;
    return true;
  }
  if (argc == 3 && (*nsame_ = tail(argv[1])) != -1) {
    *fileName = argv[2];
    return true;
  }
  if (argc == 3 && (*nsame_ = tail(argv[2])) != -1) {
    *fileName = argv[1];
    return true;
  }
  return false;
}