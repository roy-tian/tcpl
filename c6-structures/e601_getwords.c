#include "roy.h"

enum TokenType {
  SPACE     = 0U,
  WORD      = 1U,
  KEYWORD   = 1U << 2U,
  VARIABLE  = 1U << 3U,
  PUNCT     = 1U << 4U,
  OPERATOR  = 1U << 5U, // + - * / < > etc.
  DILIMITER = 1U << 6U, // () [] {}
  LITERAL   = 1U << 7U,
  NUMBER    = 1U << 8U,
  CHAR      = 1U << 9U,
  STRING    = 1U << 10U,
  COMMENT   = 1U << 11U, 
};

enum {
  STR_CAPACITY = 127
};

typedef struct Token_ {
  char content[STR_CAPACITY + 1];
  unsigned type;
} Token;

Token tokenMake(const char * content, unsigned type);

size_t getWord(char * dest, const char * src);
size_t getNumber(char * dest, const char * src);
size_t getPunct(char * dest, const char * src);
size_t getChar(char * dest, const char * src);
size_t getString(char * dest, const char * src);
size_t getComment(char * dest, const char * src);
void tokenize(RoyVector * dest, const char * src);

Token tokenMake(const char * content, unsigned type) {
  Token ret;
  strcpy(ret.content, content);
  ret.type = type;
  return ret;
}

void tokenize(RoyVector * dest, const char * src) {
  while (*src != '\0') {
    ROY_STR(buf, STR_CAPACITY)
    unsigned type = SPACE;
    if (isalpha(*src) || *src == '_') { // a word beginning detected.
      src += getWord(buf, src);
      type = WORD;
    } else if (isnumber(*src) || strchr("+-.", *src)) {
      src += getNumber(buf, src);
      type = NUMBER;
    } else if (ispunct(*src) && !strchr("_\"\'", *src)) {
      src += getPunct(buf, src);
      type = PUNCT;
    } else if (*src == '\'') {
      src += getChar(buf, src);
      type = CHAR;
    } else if (*src == '\"') {
      src += getString(buf, src);
      type = STRING;
    } else if (*src == '/' &&
               *(src + 1) && (*(src + 1) == '*' ||*(src + 1) == '/')) {
      src += getComment(buf, src);
      type = COMMENT;
    } else {
      src ++;
      type = SPACE;
    }
    if (buf) {
      Token token = tokenMake(buf, type);
      roy_vector_push_back(dest, &token);
    }
  }
}

size_t getWord(char * dest, const char * src) {}
size_t getNumber(char * dest, const char * src) {}
size_t getPunct(char * dest, const char * src) {}

int main(void) {
  printf("%d\n", 1 - -+-+ 1);
}