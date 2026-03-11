#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string replace(string text);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: %s word\n", argv[0]);
        return 1;
    }
    
    string leet = replace(argv[1]);

    printf("%s\n", leet);
}

string replace(string text) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        switch (tolower(text[i])) {
        case 'a':
            text[i] = '6';
            break;
        case 'e':
            text[i] = '3';
            break;
        case 'i':
            text[i] = '1';
            break;
        case 'o':
            text[i] = '0';
            break;
        }
    }

    return text;
}
