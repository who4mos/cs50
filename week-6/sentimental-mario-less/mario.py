while True:
    ans = input("Height: ")

    try:
        h = int(ans)
    except ValueError:
        continue

    if 1 <= h <= 8:
        break


for i in range(1, h+1):
    print(" "*(h - i) + "#"*i)
    
