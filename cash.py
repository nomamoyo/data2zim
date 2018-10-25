from cs50 import get_float

# prompt user for change and make sure user provides a positive value
while True:
    change = get_float("Change owed: ")
    if change > 0.009:
        break

# convert change to cents, and round to the nearest cent
cents = round(change * 100)

# calculate number of coins and remainder based on Zamyla's % and // tip
# calculate number of quarters and remaining change
quarters = cents//25
remainder1 = cents % 25

# calculate number of dimes and remaining change
dimes = remainder1//10
remainder2 = remainder1 % 10

# calculate number of nickels and remaining change
nickels = remainder2//5
remainder3 = remainder2 % 5

# calculate number of pennies and remaining change
pennies = remainder3

# print number of coins for change, sum up various coins and round so it's an integer - voila!
print("I have", round(quarters + nickels + dimes + pennies), "coin(s).")