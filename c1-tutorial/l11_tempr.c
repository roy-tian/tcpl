#include <wchar.h>
#include "l11_tempr.h"

double celsiusToFahrenheit(double celsius) {
  return celsius * 1.8 + 32.0;
}

double fahrenheitToCelsius(double fahrenheit) {
  return 5.0 / 9.0 * (fahrenheit - 32.0);
}

void printTemprTableFC(double begin, double end, double step) {
  wprintf(L"FAHRENHEIT CELSIUS");
  wprintf(L"-------------------");
  for (double valuef = begin, valuec; valuef <= end; valuef += step) {
    valuec = fahrenheitToCelsius(valuef);
    wprintf(L"%5.1f\xE2\x84\x83  %4.1f\xE2\x84\x89\n", valuef, valuec);
  }
}

void printTemprTableCF(double begin, double end, double step) {
  puts("FAHRENHEIT CELSIUS");
  puts("-------------------");
  for (double valuec = begin, valuef; valuec <= end; valuec += step) {
    valuef = celsiusToFahrenheit(valuec);
    wprintf(L"%.1f\xE2\x84\x89  %.1f\xE2\x84\x83\n", valuec, valuef);
  }
}
