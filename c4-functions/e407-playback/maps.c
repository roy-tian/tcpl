#include "rpc.h"
#include <math.h>

RoyMap * operators = NULL;
RoyMap * variables = NULL;

static double add   (double lhs, double rhs);
static double minus (double lhs, double rhs);
static double times (double lhs, double rhs);
static double divide(double lhs, double rhs);

static void pairDelete(RoyPair * pair);
static int  pairCompare(const RoyPair * lhs, const RoyPair * rhs);

void populate(void) {
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

  variables = roy_map_new((RCompare)pairCompare, (ROperate)pairDelete);
}

/* PRIVATE FUNCTIONS */

static double add   (double lhs, double rhs) { return lhs + rhs; }

static double minus (double lhs, double rhs) { return lhs - rhs; }

static double times (double lhs, double rhs) { return lhs * rhs; }

static double divide(double lhs, double rhs) { return lhs / rhs; }

static void pairDelete(RoyPair * pair) {
  roy_string_delete(pair->key, NULL);
  free(pair);
}

static int pairCompare(const RoyPair * lhs, const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}
