import sys
from pyfiglet import Figlet

if len(sys.argv) not in [1, 3]:
    print("Invalid usage")
    sys.exit(1)

font = ""
if len(sys.argv) == 3:
    if sys.argv[1] not in ["-f", "--font"]:
            print("Invalid usage")
            sys.exit(1)

    font = sys.argv[2]
        
figlet = Figlet()
if font:
    try:
        figlet.setFont(font=font)
    except:
        print("Invalid usage")
        sys.exit(1)

text = input("Input: ")
print(figlet.renderText(text))

