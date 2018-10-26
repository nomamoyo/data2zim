from cs50 import get_string
import sys


def main():
    # check that user provided just one argument in the command line
    if len(sys.argv) != 2:
        # read this from discource and updated my code so it'll look different from psets I've turned in
        # https://discourse.cs50.net/t/pset6-caesar-bleep/13334/2
        sys.exit("Provide filename for banned words.")
    else:
        # store argv[1] as banned and create a list/set called "words" to store banned words
        banned = sys.argv[1]
        words = set()

        # open txt file & if error,close file, print error message, & exit program
        file = open(banned, "r", encoding="latin_1")
        if not file:
            file.close()
            sys.exit("Could not open file.")
        else:
            # loop through each line (i.e. each word) in text file
            for line in file:
                # load banned words into words list in memory & strip/clean word for comparison later
                words.add(line.rstrip())
            file.close()

    # prompt user for message to censor
    text = get_string("What message would you like to censor? ")

    # split message into separate words if there's a space in between them, and store them in list called "message"
    message = text.split(" ")

    # loop through each word in message list and check against banned words set
    for usersaid in message:
        # check if lower case version of usersaid i.e. one word in the message
        if usersaid.lower() in words:
            # bleep out any banned words based on the length of the word
            print("*" * len(usersaid), end=" ")
        else:
            # just print the word as is
            print(usersaid, end=" ")

    # print new line
    print()


if __name__ == "__main__":
    main()