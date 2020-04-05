#include "syntax.h"

static int * parentheses;
static int * brackets;
static int * braces;

void lightup(const RoyMatch * match) {
  for (size_t i = match->begin; i != match->end; i++) {
    if (match->type == TEXT &&
        roy_string_find(content, "\\\\[\'\"\\sab0]", i).begin == 0) {
      shadow[i++] = ESCAPE;
      shadow[i] = ESCAPE;
    } else if (match->type == BRACKET) {
      switch (roy_string_at(content, i)) {
      case '(' : shadow[i] = push(parentheses); break;
      case ')' : shadow[i] = pop (parentheses); break;
      case '[' : shadow[i] = push(brackets);    break;
      case ']' : shadow[i] = pop (brackets);    break;
      case '{' : shadow[i] = push(braces);      break;
      case '}' : shadow[i] = pop (braces);      break;
      default  : shadow[i] = ERROR;             break;
      }
    } else {
      shadow[i] = match->type;
    }
  }
}

void map(void) {
  parentheses = newStack();
  brackets    = newStack();
  braces      = newStack();
  roy_deque_for_each(matches, (ROperate)lightup, NULL);
  deleteStack(braces);
  deleteStack(brackets);
  deleteStack(parentheses);
}