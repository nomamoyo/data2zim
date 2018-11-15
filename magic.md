# Like Magic

## Questions

4.1. BM

4.2. %PDF

4.3. The magic number may not indiciate the file type if someone deliberately edited the first few bytes to corrupt the file type.
     Sometimes, the bytes that define the file type are not right at the beginning of the file, but occur at specific offsets, and
     in that case, the first few bytes also do not indicate the file type, they only indicate the beginning of a file.

4.4. A bitwise AND operator compares two bits at a time (a bit from the conditional statement is compared to a bit read from the
     file in this case), and only returns 1 whenever both bits are 1, otherwise it always returns 0. Since the fourth byte in a
     JPEG always starts with 0xe i.e. 1110, Zamyla's code compares the individual bits in each byte of the file to 0xf0,
     i.e., 11110000 and after the third bit, this will always return zero for all the possible hexadecimal values 0-9 and a-f
     in the fourth bit of the byte because there is never an instance of 1 and 1 in the comparison, of which all of them indicate
     a JPEG.

4.5. Not sure, maybe using the logical OR would take longer as the computer has to convert the hex into binary before each
     comparison?

4.6. See `magic.c`.

## Debrief

a. Geeks for Geeks and my recover problem set

b. 60 minutes
