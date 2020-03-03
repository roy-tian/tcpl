#include "roy.h"

typedef enum {
  NORMAL    = 0,
  COMMENT   = 32,
  STRING    = 33,
  CHAR      = 43,
  ESC_SQ    = 43,
  BRACKET_1 = 34,
  BRACKET_2 = 35,
  BRACKET_3 = 36,
  ERROR     = 31
} Type;

enum {
  BUFFER_SIZE = 0x100
};

size_t readFile(RoyString * dest, const char * path) {
  FILE * fp = fopen(path, "r");

  if (!fp) {
    perror(path);
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char buf[size];
  memset(buf, '\0', size);
  fread(buf, sizeof(char), size, fp);
  roy_string_assign(dest, buf);

  fclose(fp);
  return size;
}

void setType(Type * shadow, size_t position, Type type) {
  *(shadow + position) = type;
}

void setTypeRange(Type * shadow, size_t from, size_t to, Type type) {
  for (size_t i = from; i < to; i++) {
    setType(shadow, i, type);
  }
}

Type getType(const Type * shadow, size_t position) {
  return *(shadow + position);
}

bool testType(const Type * shadow, size_t position, Type type) {
  return getType(shadow, position) == type;
}

bool testTypeRange(const Type * shadow, size_t from, size_t to, Type type) {
  for (size_t i = from; i < to; i++) {
    if (getType(shadow, i) != type) {
      return false;
    }
  }
  return true;
}

void comments(Type * shadow, const RoyString * content) {
  RoyDeque * deque = roy_deque_new((ROperate)free);
  roy_string_tokenize(deque, content, "(?<!:)\\/\\/.*|\\/\\*(\\s|.)*?\\*\\/");
  for (int i = 0; i != roy_deque_size(deque); i++) {
    RMatch match = *roy_deque_at(deque, i, RMatch);
    setTypeRange(shadow, match.begin, match.end, COMMENT);
  }
}

void strings(Type * shadow, const RoyString * content);
void chars(Type * shadow, const RoyString * content);
void escapes(Type * shadow, const RoyString * content);
void parentheses(Type * shadow, const RoyString * content);
void brackets(Type * shadow, const RoyString * content);
void braces(Type * shadow, const RoyString * content);

void printw(const Type * shadow, const RoyString * content, const char * path) {
  FILE * fp = fopen(path, "w+");
  if (!fp) {
    perror(path);
    exit(EXIT_FAILURE);
  }
  fprintf(fp,
    "<!DOCTYPE html><html><head><title>e124.cpp</title>"
    "<style>.normal{color:black;} .comment{color:forestgreen;}</style>"
    "</head><body><code>");
  Type prev = shadow[0];
  switch(prev) {
  case NORMAL  : fprintf(fp, "<span class=\"normal\">"); break;
  case COMMENT : fprintf(fp, "<span class=\"comment\">"); break;
  default: break;
  } 
  for (int i = 0; i != roy_string_length(content); i++) {
    if (i != 0 && shadow[i] != prev) {
      switch(shadow[i]) {
      case NORMAL : fprintf(fp, "</span><span class=\"normal\">"); break;
      case COMMENT : fprintf(fp, "</span><span class=\"comment\">"); break;
      default: break;
      }
    }
    prev = shadow[i];
    int prevCh = roy_string_at(content, i - 1);
    int currCh = roy_string_at(content, i);
    switch (currCh) {
    case '<'  : fprintf(fp, "&lt;"); break;
    case '>'  : fprintf(fp, "&gt;"); break;
    case '\n' : fprintf(fp, "<br>"); break;
    case ' '  :
      isspace(prevCh) ? fprintf(fp, "&nbsp;") : fprintf(fp, " ");
      break;
    default : fprintf(fp, "%c", currCh); break;
    }
  }
  fprintf(fp, "</span></code></body></html>");
  fclose(fp);
}

int main(int argc, char ** argv) {
  RoyString * content = roy_string_new("");
  size_t size = readFile(content, argv[1]);
  if (size) {
    Type * shadow = calloc(size, sizeof(Type));
    comments(shadow, content);
    char out[BUFFER_SIZE] = "\0";
    strcpy(out, argv[1]);
    strcat(out, ".html");
    printw(shadow, content, out);
  }
}