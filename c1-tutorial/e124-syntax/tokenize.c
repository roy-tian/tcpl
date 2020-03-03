#include "syntax.h"

static void comments   (Type * shadow, const RoyString * content);
static void text       (Type * shadow, const RoyString * content);
static void escapes    (Type * shadow, const RoyString * content);
static void parentheses(Type * shadow, const RoyString * content);
static void brackets   (Type * shadow, const RoyString * content);
static void braces     (Type * shadow, const RoyString * content);

void tokenize(Type * shadow, const RoyString * content) {
  comments   (shadow, content);
  text       (shadow, content);
  escapes    (shadow, content);
  parentheses(shadow, content);
  brackets   (shadow, content);
  braces     (shadow, content);
}

static void comments(Type * shadow, const RoyString * content) {
  RoyDeque * deque = roy_deque_new((ROperate)free);
  roy_string_tokenize(deque, content, "(?<!:)\\/\\/.*|\\/\\*(\\s|.)*?\\*\\/");
  for (int i = 0; i != roy_deque_size(deque); i++) {
    RMatch match = *roy_deque_at(deque, i, RMatch);
    setTypeRange(shadow, match.begin, match.end, COMMENT);
  }
  roy_deque_delete(deque);
}

static void text(Type * shadow, const RoyString * content) {
  RoyDeque * deque = roy_deque_new((ROperate)free);
  roy_string_tokenize(deque, content, "\"(\\s|.)*?\"|\'\\\\?\\w\'");
  for (int i = 0; i != roy_deque_size(deque); i++) {
    RMatch match = *roy_deque_at(deque, i, RMatch);
    if (findType(shadow, match.begin, match.end, COMMENT) == -1) {
      setTypeRange(shadow, match.begin, match.end, TEXT);
    }
  }
  roy_deque_delete(deque);
}

static void escapes(Type * shadow, const RoyString * content) {
  RoyDeque * deque = roy_deque_new((ROperate)free);
  roy_string_tokenize(deque, content, "\\\\\\w");
  for (int i = 0; i != roy_deque_size(deque); i++) {
    RMatch match = *roy_deque_at(deque, i, RMatch);
    if (testTypeRange(shadow, match.begin, match.end, TEXT)) {
      setTypeRange(shadow, match.begin, match.end, ESCAPE);
    }
  }
  roy_deque_delete(deque);
}

static void parentheses(Type * shadow, const RoyString * content) {

}
static void brackets(Type * shadow, const RoyString * content) {

}
static void braces(Type * shadow, const RoyString * content) {
  
}
