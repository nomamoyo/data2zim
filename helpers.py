from nltk.tokenize import sent_tokenize


def lines(a, b):
    # read through Discourse and Stackoverflow and figured I could create a list from a set
    # Discourse post: https://discourse.cs50.net/t/similarities-why-use-lists/13382/3
    # Stackoverflow post: https://stackoverflow.com/questions/1319338/combining-two-lists-and-removing-duplicates-without-removing-duplicates-in-orig
    # figured I could create 2 separate sets and use "&" to create a list of the intersection
    # Where I got the "&" idea from: https://docs.python.org/3/tutorial/datastructures.html#sets
    # Based on feedback from Elle (TA) on last problem set, I put all this in one line and skipped the intermediate outputs
    return list(set(a.split("\n")) & set(b.split("\n")))


def sentences(a, b):
    # apply same logic as lines
    return list(set(sent_tokenize(a)) & set(sent_tokenize(b)))


def substrings(a, b, n):
    # create list in which I'll store all substrings as I cut up the input a or b
    subs_a = []

    # iterate over all characters in a and get all possible substrings of length n
    # figured out formula in range based on trial and error, plus working it out on paper
    for char_a in range(len(a) - n + 1):
        each = a[char_a:char_a + n]
        # append each new substring to the list
        subs_a.append(each)

    # do the same thing I did for a to b
    subs_b = []

    for char_b in range(len(b) - n + 1):
        each = b[char_b:char_b + n]
        subs_b.append(each)

    return list(set(subs_a) & set(subs_b))
