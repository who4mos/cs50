#include <cs50.h>
#include <stdio.h>

int main(void) {
  int change;

  do {
    change = get_int("Change owed: ");
  } while (change <= 0);

  int c1, c5, c10, c25;
  c1 = c5 = c10 = c25 = 0;
  
  int left = change;
  c25 = left / 25; left %= 25;
  c10 = left / 10; left %= 10;
  c5 = left / 5; left %= 5;
  c1 = left;

  int totalCoins = c1 + c5 + c10 + c25;
  printf("%d\n", totalCoins);

  
}
