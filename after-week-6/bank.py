greeting = input("Greeting: ")
greeting = greeting.lower().strip()

amount = 100

if greeting.startswith('h'):
    amount = 20
    if greeting.startswith("hello"):
        amount = 0

print(f"${amount}")
