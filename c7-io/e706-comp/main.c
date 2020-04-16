#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { BUFFER_SIZE = 1024 };

/**
 * @param line - the first different line found. (0 if two files are identical, -1 if one of them is nil)
 */
void
filecmp(FILE * restrict lfile,
        FILE * restrict rfile,
        char * restrict lline,
        char * restrict rline,
        int  * restrict line) {
  char lbuf[BUFFER_SIZE] = { '\0' };
  char rbuf[BUFFER_SIZE] = { '\0' };
  *line  = 1;
  while (fgets(lbuf, BUFFER_SIZE, lfile) &&
         fgets(rbuf, BUFFER_SIZE, rfile) &&
         strcmp(lbuf, rbuf) == 0) {
        
    (*line)++;
  }
  if (feof(lfile) && feof(rfile)) {
    *line = 0;
  } else {
    strcpy(lline, lbuf);
    strcpy(rline, rbuf);
  }
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fputs("Bad command.\n", stderr);
    return EXIT_FAILURE;
  }
  FILE * lfile = fopen(argv[1], "rb");
  FILE * rfile = fopen(argv[2], "rb");
  if (!lfile || !rfile) {
    fputs("File opening failed.\n", stderr);
    return EXIT_FAILURE;
  }
  char lline[BUFFER_SIZE] = { '\0' };
  char rline[BUFFER_SIZE] = { '\0' };
  int line;
  filecmp(lfile, rfile, lline, rline, &line);
  printf("FIRST DIFER LINE %d\n %s %s", line, lline, rline);
}