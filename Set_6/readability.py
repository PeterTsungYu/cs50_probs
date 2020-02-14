text = input("Text: ")

letters = 0
# Check every object in the user input
# If it is an alphabetical character, add as an increment to the letters var 
for i in text:
    if i.isalpha() == True:
        letters += 1
# print("{} letter(s)".format(letters))

# split the text by space (a default setting of the string.split() method)
# Count the words by the length of the return list
"""Special cases: 
    "sister-in-law" should be considered one word
    "You're" should be considered one word"""
words = len(text.split())
# print("{} word(s)".format(words))

# split the text by '.' or '!' or '?' to count the sentences
"""Special cases: 
    "Mr." should be considered one sentence
    "Mrs." should be considered one sentence"""
sentences = 0
for u in [".", "!", "?"]:
    # the '-1' here at the end is to deduct the last non-used obj in the list
    sentences += len(text.split(u)) - 1
# print(f"{sentences} sentence(s)")

# Coleman-Liau index for calculating levels of grades
index = (0.0588 * letters - 0.296 * sentences) / words * 100 - 15.8

# round the float with the round func by default to the 0 digit after the decimal point.
grade = round(index)

# Some conditions to be eva
if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print("Grade {}".format(grade))