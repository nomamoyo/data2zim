from cs50 import get_int

n = get_int("Give me length: ")
print(n)

# testing indexing for substring
a = "abcde"

# print(subs_all)

subs_a = []


for char_a in range(len(a) - n + 1):
    each = a[char_a:char_a+n]
    subs_a.append(each)


# print list BUT MY LIST INCLUDES SUBSTRINGS WITH LESS THAN TWO CHARACTERS - WHY - OK SOLVED
print(subs_a)

# this is what I did to get rid of characters but this is sooooooo long!
# subs_all = subs_a

# for subs in subs_all:
#    howmany = len(subs)
#    if howmany !=n:
#        subs_all.remove(subs)

# print(subs_all)