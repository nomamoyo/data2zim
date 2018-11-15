import sys
from cs50 import get_string


def main():

    # Ensure proper usage
    if len(sys.argv) != 2 or not sys.argv[1].isdigit():
        exit("Usage: python slanted.py depth")
    depth = int(sys.argv[1])

    # Encrypt message
    message = get_string("Message: ")
    if len(message) >= depth:
        print("Slanted:", slant(message, depth))


def slant(message, depth):
    # based on https://stackoverflow.com/questions/113655/is-there-a-function-in-python-to-split-a-word-into-a-list
    characters = list(message);
    # list where I'll store ciphered message, later, I used this as kind of a list of lists and maybe that's where my problem is
    cipher = []

    # I need to read across the message characters, and print characters downwards 'depth' number of times
    for move_across in range(depth):
        # each time I move to the next character, I should put it in a row below, i.e., move down
        # e.g. when I get to the third character, I should read it and move down to the 3rd row and store it there
        # so I want to set moving across and moving down equal to each other
        move_down = move_across;

        # repeat this process as long as the number of rows is less than the length of the message otherwise I won't be changing
        # the message
        while move_down < len(message):
            # this is where I run into issues, I have just completed one iteration/ loop, and I want to append new characters
            # that have just been sorted, as I stated in lines 26-27,
            # each time I move to the next character, I should put it in a row below, i.e., move down
            # so technically, my rows are a list of ciphered_char which I add to the cipher list I declared before
            # I'm trying to make sure I'm moving across, then down in the next three lines but it's not working right
            ciphered_char = characters[move_across] + characters[move_down];
            cipher.append(ciphered_char);
            move_down = move_down + depth;

    # convert list to string https://stackoverflow.com/questions/21355248/how-to-collapse-a-list-into-a-string-in-python
    output = ''.join(cipher)
    # I noticed that if I delete every other character from output my ciphered message is kind of right. I know I should be
    # solving the problem somewhere else though
    # where I learnt this notation https://stackoverflow.com/questions/20847205/program-to-extract-every-alternate-letters-from-a-string-in-python
    final = output[1::2];

    return final

if __name__ == "__main__":
    main()
