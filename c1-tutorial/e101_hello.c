// include <stdio.h>          // expected '=', ',', ';', 'asm' or '__attribute__'
                              // before '<' token

// #include stdio.h>          // #include expects "FILENAME" or <FILENAME>

// #include <stdio.h          // missing terminating > character

#include <stdio.h>

//int main(void {             // expected ';', ',' or ')' before '{' token

//int main(void)              // expected declaration specifiers before 'printf'
                              // expected declaration specifiers before '}' token
                              // expected '{' at end of input
int main(void) {
  // printf"Hello world\n");  // expected ';' before string constant
                              // expected statement before ')' token

  // printf(Hello world\n");  // 'hello' undeclared (first use in this function)
                              // expected ')' before 'world'
                              // stray '\' in program
                              // missing terminating " character
                              // expected ';' before '}' token

  // printf("Hello world\n);  // missing terminating " character
                              // expected expression before '}' token
                              // expected ';' before '}' token

  // printf("Hello world\");  // missing terminating " character
                              // expected expression before '}' token
                              // expected ';' before '}' token

  // printf("Hello world\n";   // expected ')' before ';' token
                               // expected ';' before '}' token

  // printf("Hello world\n")   // expected ';' before '}' token
  
  printf("Hello the fantasy world\n");

// without }                   //  expected declaration or statement at end of input
}

/* EXTRA: you can printf a string literal,
 * but printf a string variable directly seems not to be a good idea,
 * for the variable may contains a '%' which will lead it to undefined behaviors,
 * or someone else using your function will take advantage of it.
 */