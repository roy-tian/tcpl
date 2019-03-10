#include <stdio.h>

const double CELSIUS_LOWER = 36.5; // lower limit of tempr table in cels.
const double CELSIUS_UPPER = 38.5; // upper limit
const double STEP = 0.1;            

double celsiusToFahrenheit(const double celsius) {
  return celsius * 1.8 + 32.0;
}

void printTemprTable(void) {
  puts("CELSIUS FAHRENHEIT");
  puts("-------------------");
  for (double celsius = CELSIUS_LOWER;
       celsius <= CELSIUS_UPPER;
       celsius += STEP) {
    printf("%5.1f\xE2\x84\x83 %5.1f\xE2\x84\x89\n",
           celsius,
           celsiusToFahrenheit(celsius));
  }
}

int main(void) {
  printTemprTable();
}