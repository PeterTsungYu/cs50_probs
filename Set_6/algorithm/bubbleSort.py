import random

def main():
    # Ask for user input to create a list, which is in the ascendent order
    b = int(input("Begin a random list with: "))
    e = int(input("End a random list with: "))
    c = int(input("Increment in a random list with: "))
    randlst = randList(b, e, c)
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