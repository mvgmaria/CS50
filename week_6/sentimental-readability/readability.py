# index = 0.0588 * L - 0.296 * S - 15.8
# L = averege number of letters per 100 words, and S = average number of sentences per 100 words

from cs50 import get_string
import math

text = get_string("Please, input the text: ")

words = 1
for _ in text:
    if _ in (" "):
        words += 1

W = 100/words

letter_counter = 0

for letter in text:
    if letter.isalpha():
        letter_counter += 1

L = letter_counter*W

sentence_counter = 0

for char in text:
    if char in (".", "?", "!"):
        sentence_counter += 1

S = sentence_counter*W

indx = (0.0588 * L) - (0.296 * S) - 15.8

index = round(indx)

if index in range(1, 17):
    print(f"Grade {index}")
elif index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
