# AMEX - 15 digits - starts with 34 or 37
# MASTERCARD - 16 digits - starts with 51, 52, 53, 54 or 55
# VISA - 13/16 digits - starts with 4

# 378282246310005 AMEX.
# 371449635398431 AMEX.
# 5555555555554444 MASTERCARD.
# 5105105105105100 MASTERCARD.
# 4111111111111111 VISA.
# 4012888888881881 VISA.
# 1234567890 INVALID.

import re

def check_type(card):
    n = len(card)
    if n < 13:
        return "INVALID"

    card_type = "INVALID"
    if card.startswith("34") or card.startswith("37"):
        if n == 15:
            card_type = "AMEX"
    elif card.startswith("5") and card[1] in "12345":
        if n == 16:
            card_type = "MASTERCARD"
    elif card.startswith("4"):
        if n == 13 or n == 16:
            card_type = "VISA"

    return card_type

def sum_digits(n):
    sum = 0
    while n > 0:
        sum += n % 10
        n //= 10

    return sum

def check_sum(card):
    sum = 0
    pos = 0

    for digit in reversed(card):
        if pos % 2 == 0:
            sum += int(digit)
        else:
            sum += sum_digits(int(digit)*2)
        pos += 1

    if sum % 10 == 0:
        return True
    else:
        return False
        

card_number = input("Number: ")

card_type = check_type(card_number)

if card_type != "INVALID" and check_sum(card_number):
    print(card_type)
else:
    print("INVALID")


    

