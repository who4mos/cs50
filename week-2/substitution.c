#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

bool keyValid(string key);
char substituteChar(char c, string key);
void printSubstitutetext(string plaintext, string key);

int main(int argc, string argv[]) {
  if (argc != 2) {
    printf("Usage: %s key\n", argv[0]);
    return 1;
  }

  if (!keyValid(argv[1])) {
    return 1;
  }

  string key = argv[1];
  string plaintext = get_string("plaintext:  ");

  printf("ciphertext: ");
  printSubstitutetext(plaintext, key);

  return 0;
}

bool keyValid(string key) {
  int length = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    if (!isalpha(key[i])) {
      printf("Key must only contain alphabetic characters\n");
      return false;
    }
    length++;
  }

  if (length == 26) {
    return true;
  } else {
    printf("Key must contain 26 characters");    
    return false;
  }
}

char substituteChar(char c, string key) {
  if (islower(c)) {
    return tolower(key[c-'a']);
  } else {
    return toupper(key[c-'A']);
  }

}

void printSubstitutetext(string plaintext, string key) {
  for (int i = 0; plaintext[i] != '\0'; i++) {
    char c = plaintext[i];
    if (isalpha(c)) {
      printf("%c", substituteChar(c, key));
    } else {
      printf("%c", c);
    }
  }
  printf("\n");
}
