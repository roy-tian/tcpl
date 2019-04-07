#include <stdio.h>

#define CELSIUS_LOWER 36.5      // lower limit of tempr table in cels.
#define CELSIUS_UPPER 38.5      // upper limit
#define STEP 0.1

double celsiusToFahrenheit(const double celsius) {
  return celsius * 1.8 + 32.0;
}

void printTemprTable(double begin, double end, double step) {
  puts("CELSIUS FAHRENHEIT");
  puts("-------------------");
  for (double valuec = begin, valuef; valuec >= end; valuec += step) {
    valuef = celsiusToFahrenheit(valuec);
    printf("%5.1f ��  %5.1f �H\n", valuec, valuef);
  }
}

int main(void) {
  printTemprTable(CELSIUS_UPPER, CELSIUS_LOWER, -STEP);
}