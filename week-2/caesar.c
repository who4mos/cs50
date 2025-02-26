#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

bool isnumeric(string s);
void printCipher(string s, int key);
char rotate(char c, int key);

int main(int argc, string argv[]) {
  if (argc != 2) {
    printf("Usage: %s key\n", argv[0]);
    return 1;
  } 

  if (!isnumeric(argv[1])) {
    printf("Usage: %s key\n", argv[0]);
    return 1;
  }

  int key = atoi(argv[1]);
  string plaintext = get_string("plaintext:  ");

  printf("ciphertext: ");
  printCipher(plaintext, key);

  return 0;
}

bool isnumeric(string s) {
  for (int i = 0; s[i] != '\0'; i++) {
    if (!isdigit(s[i])) {
      return false;
    }
  }

  return true;
}

char rotate(char c, int key) {
  if (isupper(c)) {
    return 'A' + (c - 'A' + key) % 26;
  } else {
    return 'a' + (c - 'a' + key) % 26;
  }
}

void printCipher(string s, int key) {
  for (int i = 0; s[i] != '\0'; i++) {
    if (isalpha(s[i])) {
      printf("%c", rotate(s[i], key));
    } else {
      printf("%c", s[i]);
    }
  }
  printf("\n");
}
