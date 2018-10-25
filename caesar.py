import sys
from cs50 import get_string

# check that user provided exactly one key in command line or print error and end program
if len(sys.argv) != 2:
    print("Usage: ./caesar key")
    sys.exit(1)

# assume input will always be a positive integer & store sys.argv[1] as integer shiftkey
shiftkey = int(sys.argv[1])

# prompt user for input
plaintext = get_string("plaintext: ")

# print beginning part of output and make sure it doesn't go to next line afterwards
print("ciphertext: ", end="")

# iterate character by character through plaintext input
for character in plaintext:
    # check if character is an uppercase letter
    if character.isupper():
        # Sources I consulted to figure out how to use chr() and ord()
        # for chr() https://www.geeksforgeeks.org/chr-in-python/
        # for ord() https://www.geeksforgeeks.org/ord-function-python/
        # ord returns the ASCII value of a character, so I +/- 65 i.e. 'A' and use % to wrap around alphabet
        # chr returns the letter corresponding to an ASCII value, i.e. ord()'s output
        # print shifted letter
        print(chr((ord(character) + shiftkey - 65) % 26 + 65), end="")
    elif character.islower():
        # I +/- 97 i.e. 'a' in ASCII and use % to wrap around alphabet for lower case letters then print
        print(chr((ord(character) + shiftkey - 97) % 26 + 97), end="")
    else:
        # I used based on Elle's (TA) feedback on my caesar.c - more efficient than checking more character types
        # just print non-alphanumeric plaintext as is, and add end="" in case plaintext has many words
        print(character, end="")
# print new line after ciphertext
print()