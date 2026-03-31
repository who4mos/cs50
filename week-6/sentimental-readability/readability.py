def count_letters(text):
    letters = 0
    for c in text:
        if c.isalpha():
            letters += 1

    return letters

def count_sentences(text):
    in_punct = False
    sentences = 0
    
    for c in text:
        if c in ".!?":
            if not in_punct:
                sentences += 1
            in_punct = True
        else:
            in_punct = False
                
    return sentences

text = input("Text: ")

letters = count_letters(text)
words = len(text.split())
sentences = count_sentences(text)

l = letters / words * 100
s = sentences / words * 100
index = round(0.0588 * l - 0.296 * s - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
