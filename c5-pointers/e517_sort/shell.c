#include "shell.h"
#include "sort.h"

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
  ROY_STR(buf, STRING_CAPACITY)
  while (fgets(buf, sizeof buf, fp)) {
    if (*(buf + strlen(buf) - 1) == '\n') {
      *(buf + strlen(buf) - 1) = '\0';
    }
    roy_vector_push_back(elements, buf);
  }
  fclose(fp);
  printf("%zu lines added.\n", roy_vector_size(elements));
}

void print(const char * str) {
  puts(str);
}

void select(RoyShell * shell) {
  roy_vector_for_each(elements, ROY_OPERATE(print));
}

void sort(RoyShell * shell) {
  unsigned method = 
  ((roy_shell_argument_find(shell, "-\\w*P\\w*|--page") != -1)
    ? SORT_PAGE : 0) |  
  ((roy_shell_argument_find(shell, "-\\w*S\\w*|--section") != -1)
    ? SORT_SECTION : 0) |
  ((roy_shell_argument_find(shell, "-\\w*I\\w*|--index") != -1)
    ? SORT_INDEX : 0) |
  ((roy_shell_argument_find(shell, "-\\w*r\\w*|--reverse") != -1)
    ? SORT_REVERSELY : 0);
  int (*comp)(const void *, const void *) = NULL;

  switch (method) {
  case SORT_PAGE:
    comp = ROY_COMPARE(compPage);
    break;
  case SORT_SECTION: 
    comp = ROY_COMPARE(compSection);
    break;
  case SORT_INDEX:
    comp = ROY_COMPARE(compIndex);
    break;
  case SORT_PAGE | SORT_REVERSELY:
    comp = ROY_COMPARE(compPageReverse);
    break;
  case SORT_SECTION | SORT_REVERSELY:
    comp = ROY_COMPARE(compSectionReverse);
    break;
  case SORT_INDEX | SORT_REVERSELY:
    comp = ROY_COMPARE(compIndexReverse);
    break;
  default:
    puts("Unrecognised arguments.");
    return;
  }

  qsort(roy_vector_pointer(elements, 0),
        roy_vector_size(elements),
        sizeof(char) * (STRING_CAPACITY + 1),
        comp);
}

static int compShuffle(const char * str1, const char * str2) {
  return rand() - RAND_MAX / 2;
}

void shuffle(RoyShell * shell) {
  qsort(roy_vector_pointer(elements, 0),
        roy_vector_size(elements),
        sizeof(char) * (STRING_CAPACITY + 1),
        ROY_COMPARE(compShuffle));
}

void quit(RoyShell * shell) {
  roy_vector_delete(elements);
  roy_shell_delete(shell);
  exit(EXIT_SUCCESS);
}

void error(RoyShell * shell) {
  printf("Unrecognised command: %s\n", roy_shell_argument_at(shell, 1));
}