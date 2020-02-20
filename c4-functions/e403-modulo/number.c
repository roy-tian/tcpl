#include "rpc.h"
#include <math.h>
#include <errno.h>

typedef double (* Binary)(double, double);

static double add   (double lhs, double rhs);
static double minus (double lhs, double rhs);
static double times (double lhs, double rhs);
static double divide(double lhs, double rhs);
static double modulo(double lhs, double rhs);

static void pairDelete(RoyPair * pair);
static int  pairCompare(const RoyPair * lhs, const RoyPair * rhs);

static RoyMap * operators = NULL;

void populateOperators(void) {
  operators = roy_map_new((RCompare)pairCompare, (ROperate)pairDelete);
  roy_map_insert(operators, roy_string_new("+"), add);
  roy_map_insert(operators, roy_string_new("-"), minus);
  roy_map_insert(operators, roy_string_new("*"), times);
  roy_map_insert(operators, roy_string_new("/"), divide);
  roy_map_insert(operators, roy_string_new("%"), modulo);
}

bool validNumber(const RoyString * token) {
  return 
  roy_string_match(token, "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?");
}

bool validBinary(const RoyString * token) {
  return roy_string_match(token, "[\\+\\-\\*/%%]");
}

bool
binary(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs,
             RoyString * oper) {
  Binary func = roy_map_find(operators, oper);
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
    errno = (lhs == 0.0 ? EDOM : ERANGE);
  }
  return lhs / rhs;
}

static double modulo(double lhs, double rhs) {
  if (rhs == 0.0) {
    if (lhs == 0.0) {
      errno = EDOM;
      return NAN;
    } else {
      errno = ERANGE;
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
