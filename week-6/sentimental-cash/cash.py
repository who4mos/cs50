while True:
    ans = input("Change: ")

    try:
        dollars = float(ans)
    except ValueError:
        continue

    if dollars > 0:
        break

cents = round(dollars * 100)
coins = [25, 10, 5, 1]
needed_coins = 0

for coin in coins:
    needed_coins += cents // coin
    cents %= coin

print(needed_coins)    

