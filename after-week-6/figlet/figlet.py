import sys
import random
from pyfiglet import Figlet

argc = len(sys.argv)
if argc not in [1, 3]:
    print("Invalid usage")
    sys.exit(1)    

figlet = Figlet()
fonts = figlet.getFonts()

if argc == 1:
    font = random.choice(fonts)
else:
    if sys.argv[1] in  ["-f", "--font"]:
        font = sys.argv[2]
    else:
        print("Invalid usage")
        sys.exit(1)

if font not in fonts:
    print("Invalid usage")
    sys.exit(1)

figlet.setFont(font=font)
text = input("Input: ")
print(figlet.renderText(text))
