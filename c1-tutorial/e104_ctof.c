#include <stdio.h>

const double CELSIUS_LOWER = 36.5;      // lower limit of temperature table in cels.
const double CELSIUS_UPPER = 38.5;      // upper limit
const double STEP = 0.1;                // #define versus const versus enum ?

double celsiusToFahrenheit(double celsius) {
  return celsius * 1.8 + 32.0;
}

void printTemprTable(double begin, double end, double step) {
  puts("CELSIUS FAHRENHEIT");
  puts("-------------------");
  for (double valuec = begin, valuef; valuec <= end; valuec += step) {
    valuef = celsiusToFahrenheit(valuec);
    printf("%5.1f\xE2\x84\x83  %5.1f\xE2\x84\x89\n", valuec, valuef);
  }
}

int main(void) {
  printTemprTable(CELSIUS_LOWER, CELSIUS_UPPER, STEP);
}
