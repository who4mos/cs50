// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
  string password = get_string("Enter your password: ");
  if (valid(password))
    {
      printf("Your password is valid!\n");
    }
  else
    {
      printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
  bool hasUpper, hasLower, hasNumber, hasSymbol;
  hasUpper = hasLower = hasNumber = hasSymbol = false;

  for (int i = 0; password[i] != '\0'; i++) {
    char c = password[i];

    if (isupper(c)) {
      hasUpper = true;
    } else if (islower(c)) {
      hasLower = true;
    } else if (isdigit(c)) {
      hasNumber = true;
    } else if (ispunct(c)) {
      hasSymbol = true;
    }
  }

  return (hasUpper && hasLower && hasNumber && hasSymbol);
}
