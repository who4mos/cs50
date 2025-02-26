#include <cs50.h>
#include <ctype.h>
#include <stdio.h>


int getScore(string s);

int main(void) {
  string s1, s2;
  int p1, p2;
  
  s1 = get_string("Player 1: ");
  s2 = get_string("Player 2: ");

  p1 = getScore(s1);
  p2 = getScore(s2);

  if (p1 > p2) {
    printf("Player 1 wins!\n");
  } else if (p2 > p1) {
    printf("Player 2 wins!\n");
  } else {
    printf("Tie!\n");
  }
  
  
  return 0;
}

int getScore(string s) {
  int score = 0;
  int points[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                    1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
  
  for (int i = 0; s[i] != '\0'; i++) {

    if (isalpha(s[i])) {
      int pos;
      if (isupper(s[i])) {
        pos = s[i] - 'A';
      } else {
        pos = s[i] - 'a';
      }
      score += points[pos];
    }
  }

  return score;
}
