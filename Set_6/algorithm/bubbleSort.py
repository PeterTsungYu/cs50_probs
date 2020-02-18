import random
import re

# Sort an num list, optional for int and float nums
def main():
    # Ask user to type in a random list or automatically build a list by the program
    ans = input("Auto? (y/n) ")

    # Automatically build a list by the program
    if ans == 'y':
        # Ask for user input to create a list, which is in the ascendent order
        b = int(input("Begin a random list with: "))
        e = int(input("End a random list with: "))
        c = int(input("Increment in a random list with: "))
        randlst = randList(b, e, c)
        
    # User types in a random list
    # Like this...
    # 3, 5.3, -6,6,60, 1, -3,8,9.2,3,4,5,9, 10,2,6,73, -4.9
    else:
        # re.findall method to find all (more than one: +) the digit numbers ([0-9])
        # optioinal for positive and negative numbers ([-+]?) 
        # return a list of strings containing all the numbers
        usrlst = input("Input: (Sepearate your number with comma ',') ")
        randlst = re.findall(r"[-+]?\d+\.\d+|[-+]?\d+", usrlst)
        # iterate the list to convert elements from string into int
        for i in range(len(randlst)):
            randlst[i] = float(randlst[i])

    print(randlst)

    # bubble sort the random list
    sortlst = bubbleSort(randlst)
    print(sortlst)


# Create a list based on user input
def randList(beg, end, inc):
    # list comprehension to build a range of list
    List = [num for num in range(beg, end, inc)]
    random.shuffle(List)
    return List


# "bubbling" large elements to the right and the smaller one to the left
def bubbleSort(lst):
    len_lst = len(lst)

    # Initiate the counter with a non-zero int
    counter = 1

    # Repeat iteratioin till the swap counter is 0
    # meaning no swap in the last iteration, thus it is sorted.
    while counter != 0:
        # Reset the swap counter back to 0
        counter = 0

        # when len_str = 1, range(1, 1, 1) = [], which is an empty list
        # Resulted in end of for-loop iteratioin
        for i in range(1, len_lst, 1):
            # Swap the smaller with the greater, in the usage of a temp var
            if lst[i] <= lst[i - 1]:
                temp = lst[i - 1]
                lst[i - 1] = lst[i]
                lst[i] = temp
                # increase the swap counter by 1 if the pair is out if order
                counter += 1
        len_lst -= 1
        
    return lst

main()