#include "cout.h"

int main(void) {
  Stream * s = stream_new();
  int i = 1;
  for (; i != 10; i++) {
    s->oint(s, i)->ostr(s, " little ");
    if (i % 3 == 0) {
      s->ostr(s, "Indians.\n");
    }
  }
  s->oint(s, i)->ostr(s, " little Indian boys.\n");
}