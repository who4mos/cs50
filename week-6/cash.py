def get_float(prompt):
    while True:
        try:
            return float(input(prompt))
        except ValueError:
            continue


while True:
    change = get_float("Change: ")
    if change >= 0:
        break

coins = [25, 10, 5, 1] # in cents
count = 0

change_cents = change * 100

for coin in coins:
    count += change_cents // coin
    change_cents %= coin

print(int(count))
