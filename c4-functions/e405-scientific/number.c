#include "rpc.h"
#include <math.h>
#include <errno.h>

typedef double (* Binary)(double, double);
typedef double (* Unary)(double);

static double add   (double lhs, double rhs);
static double minus (double lhs, double rhs);
static double times (double lhs, double rhs);
static double divide(double lhs, double rhs);

static void pairDelete(RoyPair * pair);
static int  pairCompare(const RoyPair * lhs, const RoyPair * rhs);

RoyMap * operators = NULL;

void populateOperators(void) {
  operators = roy_map_new((RCompare)pairCompare, (ROperate)pairDelete);
  roy_map_insert(operators, roy_string_new("+"),     add);
  roy_map_insert(operators, roy_string_new("-"),     minus);
  roy_map_insert(operators, roy_string_new("*"),     times);
  roy_map_insert(operators, roy_string_new("/"),     divide);
  roy_map_insert(operators, roy_string_new("%"),     fmod);
  roy_map_insert(operators, roy_string_new("^"),     pow);

  roy_map_insert(operators, roy_string_new("sqrt"),  sqrt);
  roy_map_insert(operators, roy_string_new("cbrt"),  cbrt);
  roy_map_insert(operators, roy_string_new("sin"),   sin);
  roy_map_insert(operators, roy_string_new("cos"),   cos);
  roy_map_insert(operators, roy_string_new("tan"),   tan);
  roy_map_insert(operators, roy_string_new("asin"),  asin);
  roy_map_insert(operators, roy_string_new("acos"),  acos);
  roy_map_insert(operators, roy_string_new("atan"),  atan);
  roy_map_insert(operators, roy_string_new("exp"),   exp);
  roy_map_insert(operators, roy_string_new("exp2"),  exp2);
  roy_map_insert(operators, roy_string_new("log"),   log);
  roy_map_insert(operators, roy_string_new("log2"),  log2);
  roy_map_insert(operators, roy_string_new("log10"), log10);
}

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

bool
binary(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs,
             RoyString * operator_) {
  Binary func = roy_map_find(operators, operator_);
  if (!func) {
    /* Since 'rpc' call this function only if 'oper' is a valid binary operator,
       'func' would always be found in the map, (!func) would never happen. */
    return false;
  }
  errno = 0;
  double result = func(roy_string_to_double(lhs), roy_string_to_double(rhs));
  roy_string_assign_double(dest, result);
  return !errno;
}

bool
unary(      RoyString * dest,
      const RoyString * operand,
            RoyString * operator_) {
  Unary func = roy_map_find(operators, operator_);
  if (!func) {
    /* ditto */
    return false;
  }
  errno = 0;
  double result = func(roy_string_to_double(operand));
  roy_string_assign_double(dest, result);
  return !errno;
}

/* PRIVATE FUNCTIONS */

static double add(double lhs, double rhs) {
  return lhs + rhs;
}

static double minus(double lhs, double rhs) {
  return lhs - rhs;
}

static double times(double lhs, double rhs) {
  return lhs * rhs;
}

static double divide(double lhs, double rhs) {
  if (rhs == 0.0) {
    errno = (lhs == 0.0 ? EDOM : ERANGE);
  }
  return lhs / rhs;
}

static void pairDelete(RoyPair * pair) {
  roy_string_delete(pair->key);
  free(pair);
}

static int pairCompare(const RoyPair * lhs,
            const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}
