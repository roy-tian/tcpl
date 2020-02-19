#include "rpc.h"

#define ERR_DIV_0      "#DIV/0"
#define ERR_OP_UNKNOWN "#NAME!"

typedef RoyString * (* Binary)(RoyString *, const RoyString *, const RoyString *);

static RoyString * add   (RoyString * dest, const RoyString * lhs, const RoyString * rhs);
static RoyString * minus (RoyString * dest, const RoyString * lhs, const RoyString * rhs);
static RoyString * times (RoyString * dest, const RoyString * lhs, const RoyString * rhs);
static RoyString * divide(RoyString * dest, const RoyString * lhs, const RoyString * rhs);
static RoyString * modulo(RoyString * dest, const RoyString * lhs, const RoyString * rhs);
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

RoyString *
binary(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs,
             RoyString * op) {
  Binary func = roy_map_find(binaryOperators, op);
  if (!func) {
    return roy_string_assign(dest, ERR_OP_UNKNOWN);
  }
  func(dest, lhs, rhs);
  return dest;
}

/* PRIVATE FUNCTIONS */

static RoyString *
add(      RoyString * dest,
    const RoyString * lhs,
    const RoyString * rhs) {
  double vlhs = roy_string_to_double(lhs);
  double vrhs = roy_string_to_double(rhs);
  return roy_string_assign_double(dest, vlhs + vrhs);
}

static RoyString *
minus(      RoyString * dest,
      const RoyString * lhs,
      const RoyString * rhs) {
  double vlhs = roy_string_to_double(lhs);
  double vrhs = roy_string_to_double(rhs);
  return roy_string_assign_double(dest, vlhs - vrhs);
}

static RoyString *
times(      RoyString * dest,
      const RoyString * lhs,
      const RoyString * rhs) {
  double vlhs = roy_string_to_double(lhs);
  double vrhs = roy_string_to_double(rhs);
  return roy_string_assign_double(dest, vlhs * vrhs);
}

static RoyString *
divide(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs) {
  double vlhs = roy_string_to_double(lhs);
  double vrhs = roy_string_to_double(rhs);
  return ((vrhs == 0.0) ? 
         roy_string_assign(dest, ERR_DIV_0) :
         roy_string_assign_double(dest, vlhs / vrhs));
}

static RoyString *
modulo(      RoyString * dest,
       const RoyString * lhs,
       const RoyString * rhs) {
  int64_t vlhs = roy_string_to_int(lhs);
  int64_t vrhs = roy_string_to_int(rhs);
  return ((vrhs == 0LL) ?
         roy_string_assign(dest, ERR_DIV_0) :
         roy_string_assign_double(dest, vlhs % vrhs));
}

static void
pairDelete(RoyPair * pair) {
  roy_string_delete(pair->key);
  free(pair);
}

static int
pairCompare(const RoyPair * lhs,
            const RoyPair * rhs) {
  return roy_string_compare(lhs->key, rhs->key);
}
