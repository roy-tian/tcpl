#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int getch(void);
void ungetch(int);
void push(double);
double pop(void);
int getop(char *);

#define BUFFER_SIZE 100

static char buf[BUFFER_SIZE];
static int pbuf = 0;

int getch(void) {
  return (pbuf > 0) ? buf[--pbuf] : getchar();
}

void ungetch(int ch) {
  if (pbuf >= BUFFER_SIZE) {
    puts("ungetch: too many characters.");
  } else {
    buf[pbuf++] = ch;
  }
}

/*****************************************************************/

#define MAX_VALUE 100

static double val[MAX_VALUE];
static int pstack = 0;

void push(double f) {
  if (pstack < MAX_VALUE) {
    val[pstack++] = f;
  } else {
    printf("push: ");
  }
}


int main(void) {

}