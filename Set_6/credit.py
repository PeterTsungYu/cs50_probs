# get a string from user input
# Re-prompt if not all the user input are numeric values
while True:
    num = input("Number: ")
    # break if the str.isnumeric() method shows all numeric input
    if num.isnumeric() == True:
        break
length = len(num)
""" print(num[0:2])
print(type(num[0:2])) """

# .join() method to merge all of the characters resulting from the reversed iteration into a new string.
# built-in func reversed(arg) has no return value, thus need another method to join.
revNum = "".join(reversed(num))

def main():
    """ if length == 16:
            print("True")
        if num[0:2] == ("34" or "37"): 
            # It would be a tuple expression. Wrong syntax. 
            print("True")
        if num[0:2] == ("51" or "52" or "53" or "54" or "55"): 
            # It would be a tuple expression. Wrong syntax. 
            print("True") """

    if luhn(revNum) == True:
        # For the str comparation, check if the desired str is in the set which is in the form of a list
        if length == 15 and num[0:2] in ["34", "37"]:
            print("AMEX")
        elif (length == 16) and num[0:2] in ["51", "52", "53", "54", "55"]:
            print("MASTERCARD")
        elif length in [13, 16] and num[0] == "4":
            print("VISA")
    else:
        print("INVALID")

def luhn(n):
    sum = 0
    # Iteration start from the second-to-last digit
    for i in range(1, length, 2):
        double = int(n[i]) * 2
        # If it is the double figure, sum up those two digits
        if (double % 100) >= 10:
            # Max digit in tens is 1
            sum += 1 + (double % 10)
        else:
            sum += double
    # Iteration start from the last digit  
    for u in range(0, length, 2):
        sum += int(n[u])
    if (sum % 10) == 0:
        return True

main()