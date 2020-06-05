from cs50 import get_int

creditCard = get_int("Enter credit card number:\n")

stringCC = str(creditCard)
creditCardLength = len(stringCC)
sumDigits = 0
doubledSumDigits = 0

firstSet = stringCC[creditCardLength - 2::-2]

# meaning of this [::] is: slice, [starting at second to last digit : until end of string : every other digit moving backwards]
for n in firstSet:
    timesTwo = int(n) * 2
    doubledSumDigits += int(timesTwo / 10) + int(timesTwo % 10)
    
# meaning of this [::] is: slice, [starting at last digit : until end of string : every other digit moving backwards]
secondSet = stringCC[creditCardLength - 1::-2]
    
for n in secondSet:
    x = int(n)
    sumDigits += x

valid = "false" 
if ((sumDigits + doubledSumDigits) % 10) == 0:
    valid = "true"

if (int(str(creditCard)[:2]) == 34) or (int(str(creditCard)[:2]) == 37) and (creditCardLength == 15) and (valid == "true"):
    print("AMEX")
elif ((int(str(creditCard)[:2]) > 50) and (int(str(creditCard)[:2]) < 56)) and (creditCardLength == 16) and (valid == "true"):
    print("MASTERCARD")
elif (int(str(creditCard)[:1]) == 4) and ((creditCardLength == 13) or (creditCardLength == 16)) and (valid == "true"):
    print("VISA")
else:
    print("INVALID")