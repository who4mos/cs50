def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            continue

def print_row(n, h):
    for i in range(h-n):
        print(" ", end="")
    for i in range(n):
        print("#", end="")
    print()
    
def print_pyramid(h):
    for i in range(1, h+1):
        print_row(i, h)

while True:
    h = get_int("Height: ")
    if h >= 1 and h <= 8:
        break

print_pyramid(h)
