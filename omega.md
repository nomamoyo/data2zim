# Omega Directive

## Questions

6.1. Say you're sorting values in ascending order, the algorithm first scans the entire array looking for the smallest value, and
     then swaps it with the number in the first position, to the correct fixed position. The two values switch positions regardless
     of whether they were consecutive on the array or not. In the subsequent iterations, the algorithm scans through all the
     remaining values to the right of the one in a fixed position, and again swaps the smallest value in that subset to the second
     fixed position in the entire array. With each iteration, the algorithm scans all the remaining values and swaps smaller values
     with the larger ones even if they were not consecutive, so this takes longer than bubble sort, hence selection sort is not Ω(n).
     It takes more steps.

6.2. Merge sort involves a repititive process of dissecting the array to be sorted until we get to a point where each array only
     contains one value, then combines the smallest arrays in doubles until we get the full array again. This continuous
     dissecting and reassembling increases the number of steps exponentially so we end up with ϴ(n log n) in both the best and
     worst case scenarios.

6.3. strlen iterates through an array, and with each iterattion, when it encounters a pointer to another value or string or
     character, it  stops, increases the length of the array by 1, and loops through the array again until it gets to the end, then
     it reports the final array length, so it takes ϴ(n) steps.

6.4. len() in python does not iterate through a list and incrementally increase the length, instead, it accesses the array length
     attribute in the array struct. *I found this on the Python Software Foundation site.

6.5. It probably takes the ASCII value of just the first charaacter and checks whether it lies between 65 and 90 inclusive. If it is,
     it confirms that the char is capitalized.

## Debrief

a. Quiz prep video and Python Software Foundation website.

b. 40 minutes
