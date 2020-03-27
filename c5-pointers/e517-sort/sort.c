#include "sort.h"

static int comps(const RoyString * lhs, const RoyString * rhs) {
  // compare the pure content without the page/section number.
  return strcmp(
    roy_string_cstr(lhs, roy_string_find(lhs, "\\(.+\\] ", 0).end),
    roy_string_cstr(rhs, roy_string_find(rhs, "\\(.+\\] ", 0).end)
  );
}

static int compsr(const RoyString * lhs, const RoyString * rhs) {
  return -comps(lhs, rhs);
}

static int compsi(const RoyString * lhs, const RoyString * rhs) {
  // compare the pure content without the page/section number.
  return strcmpi(
    roy_string_cstr(lhs, roy_string_find(lhs, "\\(.+\\] ", 0).end),
    roy_string_cstr(rhs, roy_string_find(rhs, "\\(.+\\] ", 0).end)
  );
}

static int compsir(const RoyString * lhs, const RoyString * rhs) {
  return -compsi(lhs, rhs);
}

static int compn(const RoyString * lhs, const RoyString * rhs) {
  // The page number comes after the firse char - '(', ends with a ')'.
  int lval = strtol(roy_string_cstr(lhs, 1), NULL, 0);
  int rval = strtol(roy_string_cstr(rhs, 1), NULL, 0);
  return (lval > rval) - (lval < rval);
}

static int compnr(const RoyString * lhs, const RoyString * rhs) {
  return -compn(lhs, rhs);
}

RCompare comp(Sort sort_) {
  switch (sort_) {
  case STRING:
    return (RCompare)comps;
  case STRING | REVERSE:
    return (RCompare)compsr;
  case STRING | INSENSE:
    return (RCompare)compsi;
  case STRING | INSENSE | REVERSE:
    return (RCompare)compsir;
  case NUMBER:
    return (RCompare)compn;
  case NUMBER | REVERSE:
    return (RCompare)compnr;  
  default:
    return NULL;
  }
}