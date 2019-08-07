#include "roy.h"

RoyShell * shell;
RoyVector * elements;

enum {
  VECTOR_START_CAPACITY = 10,
  STRING_CAPACITY = 256
};

void create(RoyShell * shell) {
  if (roy_shell_argument_find(shell, "(-n|--number)")) {
    roy_vector_delete(elements);
    elements = roy_vector_new(VECTOR_START_CAPACITY, sizeof(double));
  } else {
    roy_vector_delete(elements);
    elements = roy_vector_new(VECTOR_START_CAPACITY,
                              sizeof(char) * STRING_CAPACITY);
  }
}

void insert(RoyShell * shell) {
  double elemNum;
  ROY_STR(elemStr, STRING_CAPACITY)
  // Inconvinience of lack of polymorphism
  switch(elements->element_size) {
  case sizeof(double):
    for (int i = 1; i != roy_shell_argument_count(shell); i++) {
      elemNum = atof(roy_shell_argument_at(shell, i));
      roy_vector_push_back(elements, &elemNum);
    }
    break;
  case sizeof(char) * STRING_CAPACITY:
    for (int i = 1; i != roy_shell_argument_count(shell); i++) {
      strcpy(elemStr, roy_shell_argument_at(shell, i));
      roy_vector_push_back(elements, &elemStr);
    }
    break;
  default:
    break;
  }
}

void read(RoyShell * shell) {

}

void printDouble(const double * number) {
  printf("%.16g\n", *number);
}

void printStr(const char * str) {
  puts(str);
}

void select(RoyShell * shell) {
  switch(elements->element_size) {
  case sizeof(double):
    roy_vector_for_each(elements, ROY_OPERATE(printDouble));
    break;
  case sizeof(char) * STRING_CAPACITY:
    roy_vector_for_each(elements, ROY_OPERATE(printStr));
    break;
  default:
    break;
  }
}

void quit(RoyShell * shell) {
  roy_vector_delete(elements);
  roy_shell_delete(shell);
  quit(EXIT_SUCCESS);
}

int main(void) {
  shell = roy_shell_new();
  elements = roy_vector_new(0, 0);
  roy_shell_command_add(shell, "create", create);
  roy_shell_command_add(shell, "insert", insert);
  roy_shell_command_add(shell, "select", select);
  roy_shell_command_add(shell, "quit", quit);
  roy_shell_start(shell);
}