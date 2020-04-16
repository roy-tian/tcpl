#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum {
  BUFFER_SIZE = 128
};

typedef struct Stream {
  struct Stream * (*ostr )(struct Stream * this_, const char * str);
  struct Stream * (*ostrw)(struct Stream * this_, int width, const char * str);
  struct Stream * (*oint )(struct Stream * this_, int64_t value);
  struct Stream * (*ointw)(struct Stream * this_, int width, int64_t value);
  struct Stream * (*odbl )(struct Stream * this_, double value);
  struct Stream * (*odblw)(struct Stream * this_, int width, double value);
} Stream;

Stream * stream_new(void);