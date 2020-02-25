#include <stdio.h>
#include <string.h>
#include <math.h>

// Inspiration of polymophysm.
#define swap(t, x, y) { t temp = x; x = y; y = temp; }

enum {
  BUFFER_SIZE = 128
};

typedef struct Animal {
  char name[BUFFER_SIZE];
  char say[BUFFER_SIZE];
  char can[BUFFER_SIZE];
} Animal;

Animal animalMake(const char * name, const char * say, const char * can);
void animalPrint(const Animal * animal);

Animal
animalMake(const char * name,
           const char * say,
           const char * can) {
  Animal ret;
  strcpy(ret.name, name);
  strcpy(ret.say, say);
  strcpy(ret.can, can);
  return ret;
}

void
animalPrint(const Animal * animal) {
  printf("A %s says '%s', it can %s.\n",
         animal->name, animal->say, animal->can);
}

int main(void) {
  int int1 = 250, int2 = 380;
  printf("x: %d | y: %d\n", int1, int2);
  swap(int, int1, int2);
  printf("x: %d | y: %d\n", int1, int2);

  double dec1 = atan(1.0) * 4, dec2 = exp(1.0);
  printf("x: %.16g | y: %.16g\n", dec1, dec2);
  swap(double, dec1, dec2);
  printf("x: %.16g | y: %.16g\n", dec1, dec2);

  Animal animal1 = animalMake("cat", "meow", "catch mouse");
  Animal animal2 = animalMake("fox", "ringdingding", "cheat");
  animalPrint(&animal1);
  animalPrint(&animal2);
  swap(Animal, animal1, animal2);
  animalPrint(&animal1);
  animalPrint(&animal2);
}