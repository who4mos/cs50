#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  // Check for command line args
  if (argc != 2)
    {
      printf("Usage: ./read infile\n");
      return 1;
    }

  // Create buffer to read into
  char buffer[7];

  // Create array to store plate numbers
  char *plates[8];

  FILE *infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("Couldn't open %s\n", argv[1]);
    return 1;
  }
  int idx = 0;

  while (fread(buffer, 1, 7, infile) == 7)
    {
      // Replace '\n' with '\0'
      buffer[6] = '\0';

      // Save plate number in array
      plates[idx] = malloc(7 * sizeof(char));
      if (plates[idx] == NULL) {
        // more robust memory leak check, not included because the program will
        // terminate immediately and valgrind doesn't complain

        // for (int i = 0; i < idx; i++) {
        // free(plates[idx]);
	// }
        return 1;
      }
      
      strcpy(plates[idx], buffer);
      idx++;
    }

  fclose(infile);
  
  for (int i = 0; i < 8; i++)
    {
      printf("%s\n", plates[i]);
      free(plates[i]);
    }

  return 0;
}
