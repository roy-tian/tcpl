#include <locale.h>
#include "l11_tempr.h"

int main(void) {
  setlocale(LC_ALL, "zh-CN.utf8");
  printTemprTableFC(FAHRENHEIT_LOWER, FAHRENHEIT_UPPER, STEP);
}