from cs50 import get_int

# prompt user for half pyramid height until they provide a value between 1 and 8 inclusive
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# print spaces and hashes based on height provided
# calculated formula using drawings on paper & adjusted it based on my output & check50 feedback
for row in range(height):
    # no for end="" because I want a hard enter
    print(" " * (height - row - 1) + "#" * (row + 1))