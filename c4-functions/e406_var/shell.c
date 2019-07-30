#include "shell.h"

void rpc(RoyShell * shell) {
  UnaryOperator unyOp;
  BinaryOperator binOp;
  for (int i = 1; i != roy_shell_argument_count(shell); i++) {
    RoyString * arg =
    roy_string_new_with_content(roy_shell_argument_at(shell, i));
    if (validNumber(arg)) {
      doNumber(arg);
    } else
    if (unyOp = validUnaryOperator(arg)) {
      doUnaryOperator(unyOp);
    } else
    if (binOp = validBinaryOperator(arg)) {
      doBinaryOperator(binOp);
    }
    /*
    if (strspn(arg, DIGIT) == strlen(arg)) {  // arg is a number
      double value = atof(arg);
      roy_stack_push(stackOperand, &value);
    } else
    if ((binOp = charToBinaryOperator(arg)) &&  // arg is a binary operator
        roy_stack_size(stackOperand) >= 2) {     // enough operands
      double operand1 = *roy_stack_top(stackOperand, double);
      roy_stack_pop(stackOperand);
      double operand2 = *roy_stack_top(stackOperand, double);
      roy_stack_pop(stackOperand);
      double result = binOp(operand2, operand1);
      roy_stack_push(stackOperand, &result);
    } else 
    if ((unyOp = charToUnaryOperator(arg)) &&   // arg is a unary operator
        !roy_stack_empty(stackOperand)) {        // has operand
      double operand = *roy_stack_top(stackOperand, double);
      double result = unyOp(operand);
      roy_stack_push(stackOperand, &result);
    }  */else {
      puts("Syntax error.");
      roy_stack_delete(stackOperand);
      return;
    }
  }
  roy_shell_log_append(shell, "%.16g", *roy_stack_top(stackOperand, double));
  roy_stack_delete(stackOperand);
}

void quit(RoyShell * shell) {
  exit(EXIT_SUCCESS);
}
