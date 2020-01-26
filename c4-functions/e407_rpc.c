#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// gets a (possibly pushed back) character
int getch(void);
// pushes character back on input
void ungetch(int);
// pushes 'f' onto value stack
void push(double);
// pops and returns top value from stack
double pop(void);
// gets next operator or numeric operand
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

#define MAX_VALUE 100     // maximum depth of val stack

static double val[MAX_VALUE];
static int pstack = 0;

void push(double f) {
  if (pstack < MAX_VALUE) {
    val[pstack++] = f;
  } else {
    printf("push: stack full, push %g failed.\n", f);
  }
}

double pop(void) {
  if (pstack > 0) {
    return val[--pstack];
  } else {
    puts("pop: stack empty.");
    return 0.0;
  }
}

/*****************************************************************/

#define NUMBER '0'    // signal that a number was found

int getop(char * str) {
  int ch;
  while ((str[0] = ch = getch()) == ' ' || ch == '\t') { }
  str[1] = '\0';
  if (!isdigit(ch) && ch != '.') { // not a number
    return ch; 
  }

  int i = 0;
  if (isdigit(ch)) { // collects integer part
    while (isdigit(str[++i] = ch = getch())) { }
  }
  if (ch == '.') {    // collects fractions part
    while (isdigit(str[++i] = ch = getch())) { }
  }
  str[i] = '\0';
  if (ch != EOF) {
    ungetch(ch);
  }
  return NUMBER;
}

/*****************************************************************/

#define MAX_OP 100   // maximum size of operand / operator

// the reverse Polish calculator
int main(void) {
  int type;
  char str[MAX_OP];

  while ((type = getop(str)) != EOF) {
    double op2;
    switch (type) {
    case NUMBER:
      push(strtod(str, NULL));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '*':
      push(pop() * pop());
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0) {
        push(pop() / op2);
      } else {
        puts("exception: divide by zero.");
      }
      break;
    case '\n':
      printf("\t%.16g\n", pop());
      break;
    default:
      puts("exception: unrecognise token.");
      break;
    }
  }
}