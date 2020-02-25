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

void print(const char * str) {
  puts(str);
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
    ? SORT_INSENSITIVELY : 0) |
  ((roy_shell_argument_find(shell, "-\\w*d\\w*|--directory") != -1)
    ? SORT_DIRECTORY : 0);
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
  case SORT_STRING | SORT_DIRECTORY:
    comp = ROY_COMPARE(strcmpi);
    break;
  case SORT_STRING | SORT_REVERSELY | SORT_INSENSITIVELY:
    comp = ROY_COMPARE(strcmpri);
    break;
  case SORT_STRING | SORT_REVERSELY | SORT_DIRECTORY:
    comp = ROY_COMPARE(strcmprd);
    break;
  case SORT_STRING | SORT_INSENSITIVELY | SORT_DIRECTORY:
    comp = ROY_COMPARE(strcmpid);
    break;
  case SORT_STRING | SORT_REVERSELY | SORT_INSENSITIVELY | SORT_DIRECTORY:
    comp = ROY_COMPARE(strcmprid);
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

void error(RoyShell * shell) {
  printf("Unrecognised command: %s\n", roy_shell_argument_at(shell, 1));
}