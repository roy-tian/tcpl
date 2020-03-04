#include "syntax.h"

size_t read(RoyString * dest, const char * path) {
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

void write(const Type * shadow, const RoyString * content, const char * path) {
  FILE * fp = fopen(path, "w+");
  if (!fp) {
    perror(path);
    exit(EXIT_FAILURE);
  }
  fprintf(fp,
    "<!DOCTYPE html><html><head><title>e124.cpp</title><style>"
    "body{background-color:#292421;}"
    ".normal{color:antiquewhite;}"
    ".comment{color:forestgreen;}"
    ".text{color:chocolate;}"
    ".escape{color:cyan}"
    ".bracket1{color:lightgreen}"
    ".bracket2{color:lightpink}"
    ".bracket3{color:lightskyblue}"
    ".error{color:red}"
    "</style></head><body><code>");
  Type prevType = shadow[0];
  for (int i = 0; i != roy_string_length(content); i++) {
    if (shadow[i] != prevType || i == 0) {
      if (i != 0) {
        fprintf(fp, "</span>");
      }
      switch(shadow[i]) {
      case NORMAL    : fprintf(fp, "<span class=\"normal\">");   break;
      case COMMENT   : fprintf(fp, "<span class=\"comment\">");  break;
      case TEXT      : fprintf(fp, "<span class=\"text\">");     break;
      case ESCAPE    : fprintf(fp, "<span class=\"escape\">");   break;
      case BRACKET_1 : fprintf(fp, "<span class=\"bracket1\">"); break;
      case BRACKET_2 : fprintf(fp, "<span class=\"bracket2\">"); break;
      case BRACKET_3 : fprintf(fp, "<span class=\"bracket3\">"); break;
      case ERROR     : fprintf(fp, "<span class=\"error\">");    break;
      default: break;
      }
      prevType = shadow[i];
    }

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
