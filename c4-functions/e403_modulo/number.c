#include "number.h"

RoyString *
add(      RoyString * dest,
    const RoyString * lhs,
    const RoyString * rhs) {
  double vlhs = roy_string_to_double(lhs);
  double vrhs = roy_string_to_double(rhs);
  return roy_string_assign_double(dest, vlhs + vrhs);
}

RoyString *
minus(      RoyString * dest,
      const RoyString * lhs,
      const RoyString * rhs) {
  double vlhs = roy_string_to_double(lhs);
  double vrhs = roy_string_to_double(rhs);
  return roy_string_assign_double(dest, vlhs - vrhs);
}

RoyString *
times(      RoyString * dest,
      const RoyString * lhs,
      const RoyString * rhs) {
  double vlhs = roy_string_to_double(lhs);
  double vrhs = roy_string_to_double(rhs);
  return roy_string_assign_double(dest, vlhs * vrhs);
}

RoyString *
divide(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs) {
  double vlhs = roy_string_to_double(lhs);
  double vrhs = roy_string_to_double(rhs);
  return ((vrhs == 0.0) ? NULL : roy_string_assign_double(dest, vlhs / vrhs));
}

RoyString *
modulo(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs) {
  int64_t vlhs = roy_string_to_int(lhs);
  int64_t vrhs = roy_string_to_int(rhs);
  return ((vrhs == 0LL) ? NULL : roy_string_assign_double(dest, vlhs % vrhs));
}

RoyString *
binary(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs,
       const RoyString * operator_) {
  switch (roy_string_at(operator_, 0)) {
  case '+': return    add(dest, lhs, rhs);
  case '-': return  minus(dest, lhs, rhs);
  case '*': return  times(dest, lhs, rhs);
  case '/': return divide(dest, lhs, rhs);
  case '%': return modulo(dest, lhs, rhs);
  default:  return NULL;
  }
}