#include <stdio.h>

#define FAHRENHEIT_LOWER  98.0   // lower limit of tempr table in cels.
#define FAHRENHEIT_UPPER  101.0  // upper limit
#define STEP 0.1

double fahrenheitToCelsius(double fahrenheit) {
  return 5.0 / 9.0 * (fahrenheit - 32.0);
}

void printTemprTable(double begin, double end, double step) {
  puts("FAHRENHEIT CELSIUS");
  puts("------------------");
  for (double valuef = begin, valuec; valuef <= end; valuef += step) {
    valuec = fahrenheitToCelsius(valuef);
    printf("%6.1f\xE2\x84\x83  %5.1f\xE2\x84\x89\n", valuef, valuec);
  }
}

int main(void) {
  printTemprTable(FAHRENHEIT_LOWER, FAHRENHEIT_UPPER, STEP);
}