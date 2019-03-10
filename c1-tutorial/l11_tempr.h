#ifndef TEMPR_H
#define TEMPR_H

#include "l12_string.h"

#define FAHRENHEIT_LOWER  97.7   // lower limit of tempr table in cels.
#define FAHRENHEIT_UPPER  101.3  // upper limit
#define CELSIUS_LOWER  36.5      // lower limit of tempr table in cels.
#define CELSIUS_UPPER 38.5      // upper limit
#define STEP 0.1

double celsiusToFahrenheit(double celsius);
double fahrenheitToCelsius(double fahrenheit);

void printTemprTableFC(double begin, double end, double step);
void printTemprTableCF(double begin, double end, double step);

#endif // TEMPR_H