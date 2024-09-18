import re
import math

# Function to count the number of letters in text
def count_letters(text):
    count = 0
    for char in text:
        if char.isalpha():
            count += 1
    return count

# Function to count the number of words in text
def count_words(text):
    return len(text.split())

# Function to count the number of sentences in text
def count_sentences(text):
    count = 0
    for char in text:
        if char in ['.', '!', '?']:
            count += 1
    return count

def main():
    # Prompt the user for some text
    text = input("Text: ")

    # Count the number of letters, words, and sentences in the text
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Compute the Coleman-Liau index
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print the grade level
    if index >= 16:
        print("Grade 16+")
    elif index >= 1:
        print(f"Grade {index}")
    else:
        print("Before Grade 1")

if __name__ == "__main__":
    main()
