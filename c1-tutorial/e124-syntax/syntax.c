#include "syntax.h"

#define COLORIZE_HEAD \
    "<!DOCTYPE html><html><head><title>RoyEdit</title><style>" \
    "body{background-color:#272822}" \
    ".normal{color:#FFF}" \
    ".comment{color:#75715E}" \
    ".preprocessor{color:#F92672}" \
    ".text{color:#E6DB74}" \
    ".keyword{color:#F92672}" \
    ".type{color:#66D9EF;font-style:italic}" \
    ".variable{color:#FD971F;font-style:italic}" \
    ".number{color:#AE81FF}" \
    ".escape{color:#AE81FF}" \
    ".bracket1{color:lightgreen}" \
    ".bracket2{color:lightpink}" \
    ".bracket3{color:lightskyblue}" \
    ".error{color:red}" \
    "</style></head><body><code>"

static void color(int type, FILE * fp) {
  switch(type) {
  case NORMAL       : fputs("<span class=\"normal\">",       fp); break;
  case COMMENT      : fputs("<span class=\"comment\">",      fp); break;
  case PREPROCESSOR : fputs("<span class=\"preprocessor\">", fp); break;
  case TEXT         : fputs("<span class=\"text\">",         fp); break;
  case KEYWORD      : fputs("<span class=\"keyword\">",      fp); break;
  case TYPE         : fputs("<span class=\"type\">",         fp); break;
  case VARIABLE     : fputs("<span class=\"variable\">",     fp); break;
  case NUMBER       : fputs("<span class=\"number\">",       fp); break;
  case ESCAPE       : fputs("<span class=\"escape\">",       fp); break;
  case ERROR        : fputs("<span class=\"error\">",        fp); break;
  case BRACKET_1    : fputs("<span class=\"bracket1\">",     fp); break;
  case BRACKET_2    : fputs("<span class=\"bracket2\">",     fp); break;
  case BRACKET_3    : fputs("<span class=\"bracket3\">",     fp); break;
  default: break;
  }
}

static void put(int currCh, int prevCh, FILE * fp) {
  switch (currCh) {
  case '<'  : fputs("&lt;", fp); break;
  case '>'  : fputs("&gt;", fp); break;
  case '\n' : fputs("<br>", fp); break;
  case ' '  : isspace(prevCh) ? fputs("&nbsp;", fp) : fputc(' ', fp); break;
  default   : fputc(currCh, fp); break;
  }
}

void colorize(const char * fileName) {
  FILE * fp = fopen(fileName, "w+");
  if (!fp) {
    perror(fileName);
    exit(EXIT_FAILURE);
  }
  fputs(COLORIZE_HEAD, fp);
  
  const size_t len = roy_string_length(content);
  int prevType = shadow[0];
  color((((prevType))), fp); /* Test bracket colors */
  put(roy_string_at(content, 0), '\0', fp);
  for (size_t i = 1; i != len; i++) {
    if (shadow[i] != prevType) {
      fputs("</span>", fp);
      color(shadow[i], fp);
      prevType = shadow[i];
    }
    put(roy_string_at(content, i), roy_string_at(content, i - 1), fp);
  }

  fputs("</span></code></body></html>", fp);
  fclose(fp);
}

void lightup(const RoyMatch * match) {
  for (size_t i = match->begin; i != match->end; i++) {
    if (match->type == TEXT &&
        roy_string_find(content, "\\\\[\'\"\\?\\\\abfnrtv0]", i).begin == 0) {
    // Light escape sequences up.
      shadow[i++] = ESCAPE;
      shadow[i] = ESCAPE;
    } else if (match->type == BRACKET) {
    // Light brackets up colorfully.
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