#include <string.h>
#include <stdio.h>
#include <ctype.h>

void decrypt(char * text, int key) {
    for (int i = 0; i != strlen(text); i++) {
        if (islower(text[i])) {
            text[i] = (text[i] - 'a' + key) % 26 + 'a';
        } else if (isupper(text[i])) {
            text[i] = (text[i] - 'A' + key) % 26 + 'A';
        }
    }
}

void encrypt(char * text, int key) {
    for (int i = 0; i != strlen(text); i++) {
        if (islower(text[i])) {
            text[i] = 'z' - ('z' - text[i] + key) % 26;
        } else if (isupper(text[i])) {
            text[i] = 'Z' - ('Z' - text[i] + key) % 26;
        }
    }
}

int main() {
    char string[] = "The quick brown fox jumps over the lazy dog.";
    puts(string);
    encrypt(string, 3);
    puts(string);
    decrypt(string, 3);
    puts(string);
}