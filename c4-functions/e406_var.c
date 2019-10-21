#include "roy.h"
#include <math.h>

enum { STACK_CAPACITY = 128 };

static RoyShell * shell;
static RoyMap * variableMap;
static RoyMap * unaryOperatorMap;
static RoyMap * binaryOperatorMap;

typedef double (* BinaryOperator)(double, double);
typedef double (* UnaryOperator)(double);

void prepareMaps(void);

void rpc(RoyShell *);
void quit(RoyShell *);

bool validNumber(const RoyString *);
bool validVariable(const RoyString *);
bool validUnaryOperator(const RoyStack *, const RoyString *);
bool validBinaryOperator(const RoyStack *, const RoyString *);
bool validOperatorButTokenNotEnough(const RoyStack *, const RoyString *);

void doNumber(RoyStack *, const RoyString *);
void doVariable(RoyStack *, const RoyString *);
void doUnaryOperate(RoyStack *, UnaryOperator);
void doBinaryOperate(RoyStack *, BinaryOperator);
void doError(RoyStack *, RoyString *, const char *);

double plus(double, double);
double minus(double, double);
double times(double, double);
double divide(double, double);
double modulo(double, double);

void
prepareMaps(void) {
  RoyPointer pointer;
  binaryOperatorMap = roy_map_new(sizeof(char) * STACK_CAPACITY,
                                 sizeof(RoyPointer),
                                 (RCompare)strcmp);
  roy_map_insert(binaryOperatorMap, "+",   roy_pointer_set(&pointer, plus));
  roy_map_insert(binaryOperatorMap, "-",   roy_pointer_set(&pointer, minus));
  roy_map_insert(binaryOperatorMap, "*",   roy_pointer_set(&pointer, times));
  roy_map_insert(binaryOperatorMap, "/",   roy_pointer_set(&pointer, divide));
  roy_map_insert(binaryOperatorMap, "%",   roy_pointer_set(&pointer, modulo));
  roy_map_insert(binaryOperatorMap, "pow", roy_pointer_set(&pointer, pow));

  unaryOperatorMap = roy_map_new(sizeof(char) * STACK_CAPACITY,
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
  RoyStack * tokenStack = roy_stack_new(STACK_CAPACITY, sizeof(double));
  RoyString * currentToken = roy_string_new();
  for (size_t i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_string_assign(currentToken, roy_shell_argument_at(shell, i));
    if (validNumber(currentToken)) {
      doNumber(tokenStack, currentToken);
    } else if (validUnaryOperator(tokenStack, currentToken)) {
      doUnaryOperate(tokenStack,
                     roy_pointer_get(roy_map_at(unaryOperatorMap,
                                                RoyPointer,
                                                roy_string_cstr(currentToken))));
    } else if (validBinaryOperator(tokenStack, currentToken)) {
      doBinaryOperate(tokenStack,
                      roy_pointer_get(roy_map_at(binaryOperatorMap,
                                                 RoyPointer,
                                                 roy_string_cstr(currentToken))));
    } else if (validOperatorButTokenNotEnough(tokenStack, currentToken)) {
      doError(tokenStack, currentToken, "tokens not enough.");
      return;
    } else if (validVariable(currentToken)) {
      doVariable(tokenStack, currentToken);
    } else {
      roy_string_prepend_str(currentToken, "unrecgonised token - \'");
      roy_string_append_str(currentToken, "\'.");
      doError(tokenStack, currentToken, roy_string_cstr(currentToken));
      return;
    }
  }
  if (roy_stack_size(tokenStack) > 1) {
    doError(tokenStack, currentToken, "parsing ends but stack not empty.");
    return;
  }
  printf("%.16g\n", *roy_stack_top(tokenStack, double));
  roy_string_delete(currentToken);
  roy_stack_delete(tokenStack);
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
validVariable(const RoyString * token) {
  return (roy_map_find(unaryOperatorMap, roy_string_cstr(token)) == NULL) &&
         (roy_map_find(binaryOperatorMap, roy_string_cstr(token)) == NULL) &&
         roy_string_match(token, "[A-Za-z_]\\w*");
}

bool
validUnaryOperator(const RoyStack  * tokenStack,
                   const RoyString * token) {
  return
  (roy_map_find(unaryOperatorMap, roy_string_cstr(token)) != NULL) &&
  !roy_stack_empty(tokenStack);
}

bool
validBinaryOperator(const RoyStack  * tokenStack,
                    const RoyString * token) {
  return
  (roy_map_find(binaryOperatorMap, roy_string_cstr(token)) != NULL) &&
  (roy_stack_size(tokenStack) >= 2);
}

bool
validOperatorButTokenNotEnough(const RoyStack  * tokenStack,
                               const RoyString * token) {
  return
  ((roy_map_find(unaryOperatorMap, roy_string_cstr(token)) != NULL) &&
  roy_stack_empty(tokenStack)) ||
  ((roy_map_find(binaryOperatorMap, roy_string_cstr(token)) != NULL) &&
  (roy_stack_size(tokenStack) < 2));
}

void
doNumber(RoyStack        * tokenStack,
         const RoyString * token) {
  double value = atof(roy_string_cstr(token));
  roy_stack_push(tokenStack, &value);
}

void
doVariable(RoyStack        * tokenStack,
           const RoyString * token) {
             roy_string_println(token);
  // double value;
  // if (roy_map_find(variableMap, roy_string_cstr(token))) {
  //   value = *roy_map_at(variableMap, double, roy_string_cstr(token));
  // } else {
  //   value = atof(roy_shell_ohistory_at(shell, -1));
  //   roy_map_insert(variableMap, roy_string_cstr(token), &value);
  // }
  // roy_stack_push(tokenStack, &value);
}

void
doUnaryOperate(RoyStack      * tokenStack,
               UnaryOperator   operator_) {
  double operand = *roy_stack_top(tokenStack, double);
  roy_stack_pop(tokenStack);
  double result = operator_(operand);
  roy_stack_push(tokenStack, &result);
}

void
doBinaryOperate(RoyStack       * tokenStack,
                BinaryOperator   operator_) {
  double operand1 = *roy_stack_top(tokenStack, double);
  roy_stack_pop(tokenStack);
  double operand2 = *roy_stack_top(tokenStack, double);
  roy_stack_pop(tokenStack);
  double result = operator_(operand2, operand1);
  roy_stack_push(tokenStack, &result);
}

void
doError(RoyStack   * tokenStack,
        RoyString  * token,
        const char * errInfo) {
  printf("Syntax error: %s\n", errInfo);
  roy_string_delete(token);
  roy_stack_delete(tokenStack);
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
  variableMap = roy_map_new(sizeof(char) * STACK_CAPACITY,
                            sizeof(double),
                            (RCompare)strcmp);
  shell = roy_shell_new();
  roy_shell_default(shell, rpc);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}