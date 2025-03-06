def count_letters(text):
    letters = 0
    for c in text:
        if c.isalpha():
            letters += 1
    return letters

def count_words(text):
    return len(text.split())

def count_sentences(text):
    sentences = 0
    for c in text:
        if c in ".!?":
            sentences += 1
    return sentences

while True:
    text = input("Text: ")
    if len(text) > 0:
        break
    

letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)

letter_per_words = letters / words * 100
sentences_per_words = sentences / words * 100

grade = round(0.0588 * letter_per_words - 0.296 * sentences_per_words - 15.8)
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
