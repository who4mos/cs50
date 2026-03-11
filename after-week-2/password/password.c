#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

bool valid(string password);

int main(void) {
    string password = get_string("Enter your password: ");

    if (valid(password)) {
        printf("Your password is valid!\n");
    } else {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

bool valid(string password) {
    bool haslower, hasupper, hasletter, hasnumber, hassymbol;

    for (int i = 0; password[i] != '\0'; i++) {
        if (islower(password[i])) {
            haslower = true;
            hasletter = true;
        } else if (isupper(password[i])) {
            hasupper = true;
            hasletter = true;
        } else if (isdigit(password[i])) {
            hasnumber = true;
        } else if (ispunct(password[i])) {
            hassymbol = true;
        }
    }

    if (haslower && hasupper && hasletter && hasnumber && hassymbol) {
        return true;
    }

    return false;
}
