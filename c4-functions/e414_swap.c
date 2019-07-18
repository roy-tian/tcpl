#include <stdio.h>
#include <string.h>

// Inspiration of polymophysm.
#define swap(t, x, y) { t temp = x; x = y; y = temp; }

enum {
  STRING_CAPACITY = 127
};

typedef struct Animal {
  char name[STRING_CAPACITY + 1];
  char say[STRING_CAPACITY + 1];
  char can[STRING_CAPACITY + 1];
} Animal;

Animal AnimalMake(const char * name, const char * say, const char * can);
void AnimalPrint(const Animal * animal);

Animal
AnimalMake(const char * name,
           const char * say,
           const char * can) {
  Animal ret;
  strcpy(ret.name, name);
  strcpy(ret.say, say);
  strcpy(ret.can, can);
  return ret;
}

void
AnimalPrint(const Animal * animal) {
  printf("A %s says '%s', it can %s.\n",
         animal->name, animal->say, animal->can);
}

int main(void) {
  int int1 = 250, int2 = 380;
  printf("x: %d | y: %d\n", int1, int2);
  swap(int, int1, int2);
  printf("x: %d | y: %d\n", int1, int2);

  double dec1 = 3.1415926, dec2 = 2.7182818;
  printf("x: %.8g | y: %.8g\n", dec1, dec2);
  swap(double, dec1, dec2);
  printf("x: %.8g | y: %.8g\n", dec1, dec2);

  Animal animal1 = AnimalMake("cat", "meow", "catch mouse");
  Animal animal2 = AnimalMake("fox", "ringdingding", "cheat");
  AnimalPrint(&animal1);
  AnimalPrint(&animal2);
  swap(Animal, animal1, animal2);
  AnimalPrint(&animal1);
  AnimalPrint(&animal2);
}