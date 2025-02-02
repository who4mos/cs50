#include <cs50.h>
#include <stdio.h>

int sumDigits(int n);
void checkCardSum(int sum, int digits, int firstDigit, int secondDigit);

int main(void) {
  long number;
  do {
    number = get_long("Number: ");
  } while (number <= 0);

  int pos = 0;
  int sum = 0;
  int digit;

  int firstDigit, secondDigit;
  firstDigit = secondDigit = -1;
  
  while (number > 0) {
    digit = number % 10;
    
    if (pos % 2 == 0) {
      sum += digit;
    } else {
      sum += sumDigits(digit * 2);
    }

    if (number > 10 && number < 100) {
      secondDigit = digit;
    } else if (number < 10) {
      firstDigit = digit;
    }
    
    pos++;
    number /= 10;
  }

  checkCardSum(sum, pos, firstDigit, secondDigit);
}

// return the sum of the digits of positive integer n
// e.g.: 21 -> 2+1 = 3
int sumDigits(int n) {
  int sum = 0;
  while (n > 0) {
    int digit = n % 10;
    sum += digit;
    n /= 10;
  }
  return sum;
}
void checkCardSum(int sum, int digits, int firstDigit, int secondDigit) {
  if (sum % 10 == 0) {
    if (digits == 13 || digits == 16) {
      if (firstDigit == 4) {
        printf("VISA\n");
      } else if (digits == 16) {
        int firstTwo = firstDigit * 10 + secondDigit;
        if (firstTwo >= 51 && firstTwo <= 55) {
          printf("MASTERCARD\n");
        }
      }
    }
    else if (digits == 15) {
      int firstTwo = firstDigit*10 + secondDigit;
      if (firstTwo == 34 || firstTwo == 37) {
	printf("AMEX\n");        
      }
    } 
  } else {
    printf("INVALID\n");
  }
}
