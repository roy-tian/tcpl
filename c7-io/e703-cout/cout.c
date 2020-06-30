#include "cout.h"

static Stream *
ostr(Stream * this_, const char * str) {
  printf("%s", str);
  return this_;
}

static Stream *
ostrw(Stream * this_, int width, const char * str) {
  printf("%*s", width, str);
  return this_;
}

static Stream *
oint(Stream * this_, int64_t value) {
  printf("%lld", value);
  return this_;
}

static Stream *
ointw(Stream * this_, int width, int64_t value) {
  printf("%*lld", width, value);
  return this_;
}

static Stream *
odbl(Stream * this_, double value) {
  printf("%.16g", value);
  return this_;
}

static Stream *
odblw(Stream * this_, int width, double value) {
  printf("%*.16g", width, value);
  return this_;
}

void
destruct(Stream * this_) {
  free(this_);
  this_ = NULL;
}


Stream * stream_new(void) {
  Stream * ret = malloc(sizeof(Stream));
  ret->ostr  = ostr;
  ret->ostrw = ostrw;
  ret->oint  = oint;
  ret->ointw = ointw;
  ret->odbl  = odbl;
  ret->odblw = odblw;
  ret->destruct = destruct;
  return ret;
}
