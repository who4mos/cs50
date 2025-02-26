#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

bool checkSig(BYTE buf[], int size);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  FILE *input = fopen(argv[1], "rb");
  if (input == NULL) {
    printf("Failed to open %s", argv[1]);
    return 1;
  }
  
  const int BUFFER_SIZE = 512;
  BYTE buffer[BUFFER_SIZE];

  bool inJPG = false;
  int count = 0;
  FILE *jpg;
  
  while (fread(buffer, sizeof(BYTE), BUFFER_SIZE, input)) {

    if (checkSig(buffer, 512)) {
      // if a jpg signature is found we need to create a new jpg file
      char jpgname[8];
      sprintf(jpgname, "%03d.jpg", count);

      if (inJPG) {
        // jpg already points to the past image
        fclose(jpg);
      } else {
        inJPG = true;
      }

      jpg = fopen(jpgname, "wb");
      if (jpg == NULL) {
        printf("Failed to create %s\n", jpgname);
	fclose(input);
        return 1;
      }
      fwrite(buffer, sizeof(BYTE), BUFFER_SIZE, jpg);

      count++;
    } else {
      // if no signature is found there are two possibilities
      // 1. we're already in a jpeg, so just write a block
      if (inJPG) {
	fwrite(buffer, sizeof(BYTE), BUFFER_SIZE, jpg);
      }
      
      // 2. we didn't found our first jpg, keep looking
    }
  }

  // close last image
  if (inJPG) {
    fclose(jpg);
  }

  // close input file
  fclose(input);
  
  return 0;
}

bool checkSig(BYTE buf[], int size) {
  if (size < 4) {
    return false;
  }
  
  const int SIG_START = 3; // length of signature start
  const int SIG_TOTAL = 4; // total length of signature
  const int SIG_END = 16;  // last signature byte options
  
  BYTE signatureStart[] = {0xff, 0xd8, 0xff};
  BYTE signatureEnd[] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
                         0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};

  int i;
  for (i = 0; i < SIG_START; i++) {
    if (buf[i] != signatureStart[i]) {
      return false;
    }
  }

  for (int j = 0; j < SIG_END; j++) {
    if (buf[i] == signatureEnd[j]) {
      return true;
    }
  }

  return false;
}
