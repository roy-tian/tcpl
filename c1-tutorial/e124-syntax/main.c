
#include "syntax.h"

int main(int argc, char ** argv) {
  RoyString * content = roy_string_new("");
  size_t size = read(content, argv[1]);
  if (size) {
    Type * shadow = calloc(size, sizeof(Type));
    tokenize(shadow, content);
    char out[BUFFER_SIZE] = "\0";
    strcpy(out, argv[1]);
    strcat(out, ".html");
    write(shadow, content, out);
    free(shadow);
  }
  roy_string_delete(content, NULL);
}