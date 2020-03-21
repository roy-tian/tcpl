#include "rpc.h"
#include <math.h>

RoyMap * operators = NULL;

typedef double (* Binary)(double, double);

static double add   (double lhs, double rhs);
static double minus (double lhs, double rhs);
static double times (double lhs, double rhs);
static double divide(double lhs, double rhs);
static double modulo(double lhs, double rhs);

static void pairDelete(RoyPair * pair);
static int  pairCompare(const RoyPair * lhs, const RoyPair * rhs);

void populate(void) {
  operators = roy_map_new((RCompare)pairCompare, (ROperate)pairDelete);
  roy_map_insert(operators, roy_string_new("+"), add);
  roy_map_insert(operators, roy_string_new("-"), minus);
  roy_map_insert(operators, roy_string_new("*"), times);
  roy_map_insert(operators, roy_string_new("/"), divide);
  roy_map_insert(operators, roy_string_new("%"), fmod);
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

static int pairCompare(const RoyPair * lhs,
            const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}
