#include <stdio.h>
#include <math.h>

int prime(int number)
{   int k,i,result;
  k=sqrt(number);
  for(i=2;i<=k;i++)
    if(number%i==0)break;
  if(i>k)
    result=1;
  else
    result=0;
  return result;
}

int prime_v1(int number) {
  if (number < 2) {
    return 0;
  }
  for (int i = 2; i <= sqrt(number); i++) {
    if (number % i == 0) {
      return 0;
    }
  }
  return 1;
}

int prime_v2(int number) {
  if (number < 2) {
    return 0;
  }
  if (number == 2) {
    return 1;
  } 
  if (number % 2 == 0) {
    return 0;
  }
  for (int i = 3; i <= sqrt(number); i += 2) {
    if (number % i == 0) {
      return 0;
    }
  }
  return 1;
}

int main() {
  printf("%d\t", prime(4));
}