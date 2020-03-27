#include "rpc.h"
#include <math.h>

typedef double (* Binary)(double, double);
typedef double (* Unary)(double);

bool validNumber(const RoyString * token) {
  return 
  roy_string_match(token, "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?");
}

bool validBinary(const RoyString * token) {
  return roy_string_match(token, "[\\+\\-\\*/%%\\^]");
}

bool validUnary(const RoyString * token) {
  return roy_string_match(token, "a?sin|a?cos|a?tan|(sq|cb)rt|exp2?|log(2|10)?");
}

bool validVariable(const RoyString * token) {
  return roy_string_match(token, "\\$[A-Za-z_]\\w*");
}

void
binary(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs,
       const RoyString * operator_) {
  Binary func = roy_map_find(operators, operator_);
  /* Since 'rpc' call this function only if 'oper' is a valid binary operator,
     'func' would always be found in the map, (!func) would never happen. */
  double result = ( func ?
                    func(roy_string_to_double(lhs), roy_string_to_double(rhs)) :
                    NAN );
  roy_string_assign_double(dest, result);
}

void
unary(      RoyString * dest,
      const RoyString * operand,
      const RoyString * operator_) {
  Unary func = roy_map_find(operators, operator_);
  /* ditto */
  double result = ( func ? func(roy_string_to_double(operand)) : NAN );
  roy_string_assign_double(dest, result);
}
