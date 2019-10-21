#include "roy.h"
#include <math.h>

enum { CAPACITY = 128 };

static RoyShell * shell;
static RoyMap * variableMap;
static RoyMap * unaryOperatorMap;
static RoyMap * binaryOperatorMap;

typedef double (* BinaryOperator)(double, double);
typedef double (* UnaryOperator)(double);

void rpc(RoyShell *);
void quit(RoyShell *);

UnaryOperator unaryOperator(const RoyString *);
BinaryOperator binaryOperator(const RoyString *);

bool validNumber(const RoyString *);
bool validUnaryOperator(const RoyStack *, const RoyString *);
bool validBinaryOperator(const RoyStack *, const RoyString *);
bool validVariable(const RoyStack *, const RoyString *);
bool tokenNotEnough(const RoyStack *, const RoyString *);

void doNumber(RoyStack *, const RoyString *);
void doUnaryOperate(RoyStack *, const RoyString *);
void doBinaryOperate(RoyStack *, const RoyString *);
void doVariable(RoyStack *, const RoyString *);
void doError(RoyStack *, RoyString *, const char *);

double plus(double, double);
double minus(double, double);
double times(double, double);
double divide(double, double);
double modulo(double, double);

void
prepareMaps(void) {
  RoyPointer pointer;
  binaryOperatorMap = roy_map_new(sizeof(char) * CAPACITY,
                                 sizeof(RoyPointer),
                                 (RCompare)strcmp);
  roy_map_insert(binaryOperatorMap, "+",   roy_pointer_set(&pointer, plus));
  roy_map_insert(binaryOperatorMap, "-",   roy_pointer_set(&pointer, minus));
  roy_map_insert(binaryOperatorMap, "*",   roy_pointer_set(&pointer, times));
  roy_map_insert(binaryOperatorMap, "/",   roy_pointer_set(&pointer, divide));
  roy_map_insert(binaryOperatorMap, "%",   roy_pointer_set(&pointer, modulo));
  roy_map_insert(binaryOperatorMap, "pow", roy_pointer_set(&pointer, pow));

  unaryOperatorMap = roy_map_new(sizeof(char) * CAPACITY,
                                 sizeof(RoyPointer),
                                 (RCompare)strcmp);
  roy_map_insert(unaryOperatorMap, "sin",   roy_pointer_set(&pointer, sin));
  roy_map_insert(unaryOperatorMap, "cos",   roy_pointer_set(&pointer, cos));
  roy_map_insert(unaryOperatorMap, "tan",   roy_pointer_set(&pointer, tan));
  roy_map_insert(unaryOperatorMap, "asin",  roy_pointer_set(&pointer, asin));
  roy_map_insert(unaryOperatorMap, "acos",  roy_pointer_set(&pointer, acos));
  roy_map_insert(unaryOperatorMap, "atan",  roy_pointer_set(&pointer, atan));
  roy_map_insert(unaryOperatorMap, "exp",   roy_pointer_set(&pointer, exp));
  roy_map_insert(unaryOperatorMap, "exp2",  roy_pointer_set(&pointer, exp2));
  roy_map_insert(unaryOperatorMap, "log",   roy_pointer_set(&pointer, log));
  roy_map_insert(unaryOperatorMap, "log10", roy_pointer_set(&pointer, log10));
  roy_map_insert(unaryOperatorMap, "log2",  roy_pointer_set(&pointer, log2));
}

void
rpc(RoyShell * shell) {
  RoyStack * tokens = roy_stack_new(CAPACITY, sizeof(double));
  RoyString * token = roy_string_new();
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(token, roy_shell_argument_at(shell, i));
    if (validNumber(token)) {
      doNumber(tokens, token);
    } else if (validUnaryOperator(tokens, token)) {
      doUnaryOperate(tokens, token);
    } else if (validBinaryOperator(tokens, token)) {
      doBinaryOperate(tokens, token);
    } else if (tokenNotEnough(tokens, token)) {
      doError(tokens, token, "tokens not enough.");
      return;
    } else if (validVariable(tokens, token)) {
      doVariable(tokens, token);
    }
    else {
      roy_string_prepend_str(token, "unrecgonised token - \'");
      roy_string_append_str(token, "\'.");
      doError(tokens, token, roy_string_cstr(token));
      return;
    }
  }
  if (roy_stack_size(tokens) != 1) {
    doError(tokens, token, "parsing ends but stack error.");
    return;
  }
  printf("%.16g\n", *roy_stack_top(tokens, double));
  roy_string_delete(token);
  roy_stack_delete(tokens);
}

void
quit(RoyShell * shell) {
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}

bool
validNumber(const RoyString * token) {
  return
  roy_string_match(token, "[+-]?(\\d+\\.?\\d*|\\d*\\.?\\d+)([Ee][+-]?\\d+)?");
}

bool
validUnaryOperator(const RoyStack  * tokens,
                   const RoyString * token) {
  return unaryOperator(token) && !roy_stack_empty(tokens);
}

bool
validBinaryOperator(const RoyStack  * tokens,
                    const RoyString * token) {
  return binaryOperator(token) && (roy_stack_size(tokens) >= 2);
}

bool
validVariable(const RoyStack  * tokens,
              const RoyString * token) {
  return roy_string_match(token, "[A-Za-z_]\\w*") &&
         !unaryOperator(token) &&
         !binaryOperator(token);
}

bool
tokenNotEnough(const RoyStack  * tokens,
               const RoyString * token) {
  return ( unaryOperator(token) && roy_stack_empty(tokens)) || 
         (binaryOperator(token) && (roy_stack_size(tokens) < 2));
}

UnaryOperator
unaryOperator(const RoyString * token) {
  RoyPointer * pointer = roy_map_at(unaryOperatorMap,
                                    RoyPointer,
                                    roy_string_cstr(token));
  return pointer ? roy_pointer_get(pointer) : NULL;
}

BinaryOperator
binaryOperator(const RoyString * token) {
  RoyPointer * pointer = roy_map_at(binaryOperatorMap,
                                    RoyPointer,
                                    roy_string_cstr(token));
  return pointer ? roy_pointer_get(pointer) : NULL;
}

void
doNumber(RoyStack        * tokens,
         const RoyString * token) {
  double value = atof(roy_string_cstr(token));
  roy_stack_push(tokens, &value);
}

void
doUnaryOperate(RoyStack        * tokens,
               const RoyString * token) {
  double operand = *roy_stack_top(tokens, double);
  roy_stack_pop(tokens);
  double result = unaryOperator(token)(operand);
  roy_stack_push(tokens, &result);
}

void
doBinaryOperate(RoyStack        * tokens,
                const RoyString * token) {
  double operand1 = *roy_stack_top(tokens, double);
  roy_stack_pop(tokens);
  double operand2 = *roy_stack_top(tokens, double);
  roy_stack_pop(tokens);
  double result = binaryOperator(token)(operand2, operand1);
  roy_stack_push(tokens, &result);
}

void
doVariable(RoyStack        * tokens,
           const RoyString * token) {
  double value;
  if (roy_map_find(variableMap, roy_string_cstr(token))) {
    value = *roy_map_at(variableMap, double, roy_string_cstr(token));
  } else {
    value = atof(roy_shell_ohistory_at(shell, -1));
    roy_map_insert(variableMap, roy_string_cstr(token), &value);
  }
  roy_stack_push(tokens, &value);
  printf("![%s]\n", roy_shell_ohistory_at(shell, -1));
}

void
doError(RoyStack   * tokens,
        RoyString  * token,
        const char * errInfo) {
  printf("Syntax error: %s\n", errInfo);
  roy_string_delete(token);
  roy_stack_delete(tokens);
}

double plus(double operand1, double operand2) {
  return operand1 + operand2;
}

double minus(double operand1, double operand2) {
  return operand1 - operand2;
}

double times(double operand1, double operand2) {
  return operand1 * operand2;
}
double divide(double operand1, double operand2) {
  return operand1 / operand2;
}

double modulo(double operand1, double operand2) {
  return (double)((int)operand1 % (int)operand2);
}

int main(void) {
  prepareMaps();
  variableMap = roy_map_new(sizeof(char) * CAPACITY,
                            sizeof(double),
                            (RCompare)strcmp);
  shell = roy_shell_new();
  roy_shell_default(shell, rpc);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}