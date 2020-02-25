#include "roy.h"

RoyShell * shell;
RoyVector * elements;

enum {
  VECTOR_START_CAPACITY = 10,
  BUFFER_SIZE = 256,
  SORT_STRING = 0,
  SORT_NUMBER = 1,
  SORT_REVERSELY = 1 << 1,
  SORT_INSENSITIVELY = 1 << 2,
};

void insert(RoyShell * shell);
void read(RoyShell * shell);
void select(RoyShell * shell);
void sort(RoyShell * shell);
void quit(RoyShell * shell);
void print(const char * str);
int numcmp(const char * str1, const char * str2);
int numcmpr(const char * str1, const char * str2);
int strcmpi(const char * str1, const char * str2);
int strcmpr(const char * str1, const char * str2);
int strcmpri(const char * str1, const char * str2);

void insert(RoyShell * shell) {
  for (int i = 1; i != roy_shell_argument_count(shell); i++) {
    roy_vector_push_back(elements,
                         roy_shell_argument_at(shell, i));
  }
}

void read(RoyShell * shell) {
  FILE * fp = fopen(roy_shell_argument_at(shell, 1), "r");
  if (!fp) {
    printf("File '%s' open error.\n", roy_shell_argument_at(shell, 1));
    return;
  }
  ROY_STR(buf, BUFFER_SIZE)
  while (fgets(buf, sizeof buf, fp)) {
    if (*(buf + strlen(buf) - 1) == '\n') {
      *(buf + strlen(buf) - 1) = '\0';
    }
    roy_vector_push_back(elements, buf);
  }
  fclose(fp);
  printf("%zu lines added.\n", roy_vector_size(elements));
}

void select(RoyShell * shell) {
  roy_vector_for_each(elements, ROY_OPERATE(print));
}

void sort(RoyShell * shell) {
  unsigned method =
  ((roy_shell_argument_find(shell, "-\\w*n\\w*|--number") != -1)
    ? SORT_NUMBER : 0) |  
  ((roy_shell_argument_find(shell, "-\\w*r\\w*|--reverse") != -1)
    ? SORT_REVERSELY : 0) |
  ((roy_shell_argument_find(shell, "-\\w*i\\w*|--insensitive") != -1)
    ? SORT_INSENSITIVELY : 0);
  int (*comp)(const void *, const void *) = NULL;

  switch (method) {
  case SORT_NUMBER:
    comp = ROY_COMPARE(numcmp);
    break;
  case SORT_NUMBER | SORT_REVERSELY:
    comp = ROY_COMPARE(numcmpr);
    break;
  case SORT_STRING | SORT_REVERSELY:
    comp = ROY_COMPARE(strcmpr);
    break;
  case SORT_STRING | SORT_INSENSITIVELY:
    comp = ROY_COMPARE(strcmpi);
    break;
  case SORT_STRING | SORT_REVERSELY | SORT_INSENSITIVELY:
    comp = ROY_COMPARE(strcmpri);
    break;
  case SORT_STRING:
    comp = ROY_COMPARE(strcmp);
    break;
  default:
    puts("Unrecognised arguments.");
    break;
  }
  qsort(elements->data,
        roy_vector_size(elements),
        sizeof(char) * (BUFFER_SIZE),
        comp);
}

void quit(RoyShell * shell) {
  roy_vector_delete(elements);
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}

void print(const char * str) {
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

char * str_tolower(char * str) {
  char * pstr = str;
  while (*pstr != '\0') {
    *pstr = tolower(*pstr);
    pstr++;
  }
  return str;
}

int strcmpi(const char * str1, const char * str2) {
  ROY_STR(str1u, strlen(str1))
  strcpy(str1u, str1);
  ROY_STR(str2u, strlen(str2))
  strcpy(str2u, str2);
  return strcmp(str_tolower(str1u), str_tolower(str2u));
}

int strcmpr(const char * str1, const char * str2) {
  return -strcmp(str1, str2);
}

int strcmpri(const char * str1, const char * str2) {
  return -strcmpi(str1, str2);
}

int main(void) {
  shell = roy_shell_new();
  elements = roy_vector_new(VECTOR_START_CAPACITY,
                            sizeof(char) * (BUFFER_SIZE));
  roy_shell_add(shell, insert);
  roy_shell_add(shell, read);
  roy_shell_add(shell, select);
  roy_shell_add(shell, sort);
  roy_shell_add(shell, quit);
  roy_shell_start(shell);
}