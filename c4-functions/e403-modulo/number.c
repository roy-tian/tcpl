#include "rpc.h"
#include <fenv.h>
#include <math.h>

typedef double (* Binary)(double, double);

static double add   (double lhs, double rhs);
static double minus (double lhs, double rhs);
static double times (double lhs, double rhs);
static double divide(double lhs, double rhs);
static double modulo(double lhs, double rhs);

static void pairDelete(RoyPair * pair);
static int  pairCompare(const RoyPair * lhs, const RoyPair * rhs);

static RoyMap * binaryOperators = NULL;

bool
validNumber(const RoyString * string) {
  return 
  roy_string_match(string, "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?");
}

bool
validBinaryOperator(const RoyString * string) {
  return roy_string_match(string, "[\\+\\-\\*/%%]");
}

void populateBinaryOperators(void) {
  binaryOperators = roy_map_new((RCompare)pairCompare, (ROperate)pairDelete);
  roy_map_insert(binaryOperators, roy_string_new("+"), add);
  roy_map_insert(binaryOperators, roy_string_new("-"), minus);
  roy_map_insert(binaryOperators, roy_string_new("*"), times);
  roy_map_insert(binaryOperators, roy_string_new("/"), divide);
  roy_map_insert(binaryOperators, roy_string_new("%"), modulo);
}

bool
binary(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs,
             RoyString * oper) {
  Binary func = roy_map_find(binaryOperators, oper);
  if (!func) {
    /* Since 'rpc' call this function only if 'oper' is a valid binary operator,
       'func' would always be found in the map, (!func) would never happen. */
    return false;
  }
  feclearexcept(FE_ALL_EXCEPT);
  double result = func(roy_string_to_double(lhs), roy_string_to_double(rhs));
  roy_string_assign_double(dest, result);
  return fetestexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW) == 0;
}

/* PRIVATE FUNCTIONS */

static double add(double lhs, double rhs) {
  return lhs + rhs;
}

static double minus(double lhs, double rhs) {
  return lhs - rhs;
}

static double times (double lhs, double rhs) {
  return lhs * rhs;
}

static double divide(double lhs, double rhs) {
  if (rhs == 0.0) {
    (lhs == 0.0) ? feraiseexcept(FE_INVALID) : feraiseexcept(FE_DIVBYZERO);
  }
  return lhs / rhs;
}

static double modulo(double lhs, double rhs) {
  if (rhs == 0.0) {
    if (lhs == 0.0) {
      feraiseexcept(FE_INVALID);
      return NAN;
    } else {
      feraiseexcept(FE_DIVBYZERO);
      return INFINITY;
    }
  }
  return (int)lhs % (int)rhs; 
}

static void pairDelete(RoyPair * pair) {
  roy_string_delete(pair->key);
  free(pair);
}

static int pairCompare(const RoyPair * lhs,
            const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}
