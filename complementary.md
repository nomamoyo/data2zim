# Complementary Questions

## Questions

1.1. 10000011

1.2. 11111100

1.3. I'll use the Psy example to explain. According to the article provided, Youtube may have been using 32 bits to store the
     counter, of which the maximum positive integer than 32 bits can hold is 2,147,483,647, which is 01111111.
     So when the 2,147,483,648th viewer watched Gangnam Style, the computer tried to find a way to express that in binary using
     just 8 bits, and this led to the first digit 0 to turn into a 1, and all the values thereafter were read as negatives because
     of sign-magnitude notation.

1.4. I ran the code provided and noticed that the code breaks when we get to 1073741824 * 2. This happens because the computation
     results in a value greater than 2,147,483,647 and since the computer only has 8 bits, the binary expression for the value starts
     afresh from the smallest possible value, i.e., it wraps around to 00000000 in binary, and that prints 0, which when doubled
     continues to return zero and since the loop is infinite, it just keeps doubling and printing 0.

1.5. It sounds like Ariane 5's software was supposed to log its speed and make some other hardware respond based on the speed logged.
     However, the people writing the software understimated how fast Ariane would accelerate, and did not assign enough bits for
     Ariane 5's software to accurately log the speed, so the rocket malfunctioned.


## Debrief

a. Lecture videos, Wikipedia, and the Quiz review video.

b. Not sure, because I'm doing this while watching the quiz review video and pausing.
