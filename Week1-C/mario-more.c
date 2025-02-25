#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

void print_left(int bricks, int spaces);
void print_right(int bricks, int spaces);
void print_row(int bricks, int spaces);

int main(void) {
  int n;

  do {
    n = get_int("n: ");
  } while (n <= 0);

  for (int i = 1; i <= n; i++) {
    print_row(i, n - i);
  }
}

void print_left(int bricks, int spaces) {
  for (int i = 0; i < spaces; i++) {
    printf(" ");
  }

  for (int i = 0; i < bricks; i++) {
    printf("#");
  }
}

void print_right(int bricks, int spaces) {
  for (int i = 0; i < bricks; i++) {
    printf("#");
  }

  for (int i = 0; i < spaces; i++) {
    printf(" ");
  }
  printf("\n");
}


void print_row(int bricks, int spaces) {
  print_left(bricks, spaces);
  printf("  ");
  print_right(bricks, spaces);
}
