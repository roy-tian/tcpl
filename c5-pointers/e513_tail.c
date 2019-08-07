
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char * readFromFile(const char * filePath);
size_t strCountLine(const char * str);
char * strTail(char * str, int index);
const char * parseFilePath(int argc, char * argv[]);
int parseLine(int argc, char * argv[]);


// string must be freed when it's done.
char * readFromFile(const char * filePath) {
  FILE * fp = fopen(filePath, "r");

  if (!fp) {
    printf("File not found: %s\n", filePath);
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char * ret = calloc(size + 1, sizeof(char));
  fread(ret, sizeof(char), size, fp);
  fclose(fp);
  return ret;
}

size_t strCountLine(const char * str) {
  size_t count = 0;
  while (*str != '\0') {
    if (*str++ == '\n') {
      count++;
    }
  }
  str--;
  if (*str != '\n') {
    // When last char is not '\n', that line still needs to be counted.
    count++;
  }
  return count;
}

char * strTail(char * str, int index) {
  if (index < 1 || index > strCountLine(str)) {
    printf("Invalid line number detected.\n",
           strCountLine(str),
           index);
    exit(EXIT_FAILURE);
  }
  while ((index-- > 1) && strchr(str, '\n')) {    
    str = strchr(str, '\n') + 1; // excludes the '\n' right before the line.
  }
  if (index >= 1 && !strchr(str, '\n')) { // index exceeds, returns nothing.
    return NULL;
  }
  return str;
}

const char * parseFilePath(int argc, char * argv[]) {
  while (--argc) {
    *argv++;
    if (**argv != '-') {
      return *argv;
    }
  }
  printf("File name parsing failed.\n");
  exit(EXIT_FAILURE);
}

int parseLine(int argc, char * argv[]) {
  while (--argc) {
    *argv++;
    if (**argv == '-') {
      return atoi(*argv + 1);
    }
  }
  // line number starts from 1, 0 indecates line is not given.
  printf("Line number parsing failed.\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]) {
  int index;
  char * str = readFromFile(parseFilePath(argc, argv));
  if (argc == 2 && parseFilePath(argc, argv)) {
    index = 1;
  } else if (argc == 3) {
    index = strCountLine(str) - parseLine(argc, argv) + 1;
  } else {
    printf("Unrecognised command.\nPossible usage: tail -n \"file_name\"\n");
    exit(EXIT_FAILURE);
  }
  puts(strTail(str, index)); 
  free(str);
}