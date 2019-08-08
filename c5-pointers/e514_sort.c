#include "roy.h"

RoyShell * shell;
RoyVector * elements;

enum {
  VECTOR_START_CAPACITY = 10,
  STRING_CAPACITY = 255
};

void insert(RoyShell * shell);
void read(RoyShell * shell);
void select(RoyShell * shell);
void sort(RoyShell * shell);
void quit(RoyShell * shell);
void printDouble(const char * str);
void printStr(const char * str);
int numcmp(const char * str1, const char * str2);
int numcmpr(const char * str1, const char * str2);
int strcmpr(const char * str1, const char * str2);

void insert(RoyShell * shell) {
  for (int i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_vector_push_back(elements,
                         roy_shell_argument_at(shell, i));
  }
}

void read(RoyShell * shell) {
  FILE * fp = fopen(roy_shell_argument_at(shell, 1), "r");
  ROY_STR(buf, STRING_CAPACITY)
  while (fgets(buf, sizeof buf, fp)) {
    if (*(buf + strlen(buf) - 1) == '\n') {
      *(buf + strlen(buf) - 1) = '\0';
    }
    roy_vector_push_back(elements, buf);
  }
  fclose(fp);
}

void select(RoyShell * shell) {
  if (roy_shell_argument_find(shell, "-\\w*n\\w*|--number") != -1) {
    roy_vector_for_each(elements, ROY_OPERATE(printDouble));
  } else {
    roy_vector_for_each(elements, ROY_OPERATE(printStr));
  }
}

void sort(RoyShell * shell) {
  bool reverse = roy_shell_argument_find(shell, "-\\w*r\\w*|--reverse") != -1;
  bool number = roy_shell_argument_find(shell, "-\\w*n\\w*|--number") != -1;
  int (*comp)(const void *, const void *);
  if (reverse && number) {
    comp = ROY_COMPARE(numcmpr);
  } else if (!reverse && number) {
    comp = ROY_COMPARE(numcmp);
  } else if (reverse && !number) {
    comp = ROY_COMPARE(strcmpr);
  } else /* (!reverse && !number) */ {
    comp = ROY_COMPARE(strcmp);
  }
  qsort(elements->data,
        roy_vector_size(elements),
        sizeof(char) * (STRING_CAPACITY + 1),
        comp);
}

void quit(RoyShell * shell) {
  roy_vector_delete(elements);
  roy_shell_delete(shell);
  quit(EXIT_SUCCESS);
}

void printDouble(const char  * str) {
  printf("%.16g\n", atof(str));
}

void printStr(const char * str) {
  puts(str);
}

int numcmp(const char * str1, const char * str2) {
  double num1 = atof(str1);
  double num2 = atof(str2);
  return (num1 > num2) - (num1 < num2);
}

int numcmpr(const char * str1, const char * str2) {
  return -numcmp(str1, str2);
}

int strcmpr(const char * str1, const char * str2) {
  return -strcmp(str1, str2);
}

int main(void) {
  shell = roy_shell_new();
  elements = roy_vector_new(VECTOR_START_CAPACITY,
                            sizeof(char ) * (STRING_CAPACITY + 1));
  roy_shell_command_add(shell, "insert", insert);
  roy_shell_command_add(shell, "read", read);
  roy_shell_command_add(shell, "select", select);
  roy_shell_command_add(shell, "sort", sort);
  roy_shell_command_add(shell, "quit", quit);
  roy_shell_start(shell);
}