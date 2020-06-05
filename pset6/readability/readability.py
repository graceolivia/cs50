from cs50 import get_string

text = get_string("Text:")

words = text.count(" ") + 1

sentences = 0
sentences += text.count(".")
sentences += text.count("?")
sentences += text.count("!")

letters = 0

for n in text:
    if (n.isalpha()) == True:
        letters += 1
        

numerator = words * .01
L = letters / numerator
S = sentences / numerator

index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print('Before Grade 1')
elif index > 16:
    print('Grade 16+')
else:
    print('Grade', index)