#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s FILE\n", argv[0]);
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL) {
        
        return 1;
    }

    const int SIG_SIZE = 4;
    
    BYTE sig_start[] = {0xff, 0xd8, 0xff};
    BYTE buf[512];

    int counter = 0;

    // start out file pointer as null (no jpgs found yet)
    FILE *out = NULL;
    
    while (fread(&buf, sizeof(BYTE), 512, card) == 512) {
        int sig_found = 1;
        for (int i = 0; i < SIG_SIZE - 1; i++) {
            if (buf[i] != sig_start[i])
                sig_found = 0;
        }

        BYTE last_sig = buf[SIG_SIZE - 1];
        if (last_sig < 0xe0 || last_sig > 0xef)
            sig_found = 0;


        if (sig_found) {
            char file_name[8];
            sprintf(file_name, "%03d.jpg", counter);

            // check if already opened a jpg
            if (out != NULL)
                fclose(out);

            // open a new one and start writing
            out = fopen(file_name, "w");
            if (out == NULL) {
                fclose(card);
                return 1;
            }
            
            counter++;
            fwrite(&buf, sizeof(BYTE), 512, out);
        } else if (out != NULL) {
            // if not found a signature, keep writing, unless
            // we didn't found any jpgs yet
            fwrite(&buf, sizeof(BYTE), 512, out);
        }
    }

    fclose(card);
    fclose(out);
    return 0;
}
