def sum_digits(n):
    res = 0
    while n > 0:
        res += n % 10
        n //= 10

    return res


while True:
    card = input("Number: ")
    if card.isnumeric():
        break


checksum = 0
for i in range(len(card) - 2, -1, -2):
    checksum += sum_digits(int(card[i]) * 2)

for i in range(len(card) - 1, -1, -2):
    checksum += int(card[i])
    
if checksum % 10 == 0:
    len_card = len(card)
    if len_card == 15 and card[:2] in ["34", "37"]:
        print("AMEX")
    elif len_card == 16 and card[0] == "5" and card[1] in "12345":
        print("MASTERCARD")
    elif len_card == 13 or len_card == 16 and card[0] == "4":
        print("VISA")
    else:
        print("INVALID")
else:
        print("INVALID")
