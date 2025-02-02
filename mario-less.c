#include <cs50.h>
#include <stdio.h>

void print_bricks(int bricks);
void print_row(int bricks, int spaces);

int main(void) {
  int n;

  do {
    n = get_int("Height: ");
  } while (n <= 0);

  for (int i = 1; i <= n; i++) {
    print_row(i, n - i);
  }
}

void print_bricks(int bricks) {
  for (int i = 0; i < bricks; i++) {
    printf("#");
  }
  printf("\n");
}

void print_row(int bricks, int spaces) {
  for (int i = 0; i < spaces; i++) {
    printf(" ");
  }
  print_bricks(bricks);
}
