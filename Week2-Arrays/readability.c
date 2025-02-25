#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>


int countLetters(string s);
int countWords(string s);
int countSentences(string s);

int main(void) {
  string s = get_string("Text: ");
  int letters, words, sentences;
  float index;
  
  letters = countLetters(s);
  words = countWords(s);
  sentences = countSentences(s);

  float letterPerWords = (float) letters / words * 100;
  float sentencesPerWords = (float) sentences / words * 100;
  
  index = 0.0588 * letterPerWords - 0.296 * sentencesPerWords - 15.8;
  int grade = round(index);

  if (grade < 1) {
    printf("Before Grade 1\n");
  } else if (grade >= 16) {
    printf("Grade 16+\n");
  } else {
    printf("Grade %d\n", grade);
  }
  
  return 0;
}

int countLetters(string s) {
  int count = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    if (isalpha(s[i])) {
      count++;
    }
  }

  return count;
}

int countWords(string s) {
  int words = 0;
  bool inWord = false;

  for (int i = 0; s[i] != '\0'; i++) {
    if (isalpha(s[i]) || s[i] == '\'') {
      if (!inWord) {
        inWord = true;
        words++;
      } else {
        continue;
      }
    } else {
      inWord = false;
    }
  }
  return words;
}

int countSentences(string s) {
  int sentences = 0;
  
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] == '.' || s[i] == '!' || s[i] == '?') {
      sentences++;
    }
  }

  return sentences;
}
