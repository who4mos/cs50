// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

string replace(string s);

int main(int argc, string argv[])
{
  if (argc != 2) {
    printf("Usage: %s word\n", argv[0]);
    return 1;
  }

  string result = replace(argv[1]);
  printf("%s\n", result);

  return 0;
}

/*
  I think this is what's expected at this point in the course
  but the function overwrites the string passed.

  The solution would be accept that and return void, or allocate memory
  for the return string using malloc
 */
string replace(string s) {

  string new = s;
  int i;
  for (i = 0; s[i] != '\0'; i++) {
    switch (tolower(s[i])) {
    case 'a':
      new[i] = '6';
      break;
    case 'e':
      new[i] = '3';
      break;
    case 'i':
      new[i] = '1';
      break;
    case 'o':
      new[i] = '0';
      break;
    default:
      new[i] = s[i];
    }
  }

  new[i] = '\0';
  
  return new;
}
