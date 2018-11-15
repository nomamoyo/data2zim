# Song that Never Ends

## Questions

8.1. RecursionError: maximum recursion depth exceeded while calling a Python object

8.2. See `song.c`.

8.3. Segmentation fault

8.4. The program eventually tries to access an invalid location in memory. Since the function is recursive, it keeps taking up more
     memory in the stack until it overflows.

8.5. See `song.py`.

8.6. David's phone book search was a recursive merge sort algorithm, the idea is to open the phone book in half, check whether
     Mike Smith (that's whose number he was looking for) is on the left-hand or right-hand side half based on the alphabet, pick
     the correct half and repeat the whole process again, open the appropriate half in half, check, repeat until you find the page
     with Mike Smith.

## Debrief

a. Notes from lecture that mentioned stack overflow and Week 0 notes

b. 20 minutes
