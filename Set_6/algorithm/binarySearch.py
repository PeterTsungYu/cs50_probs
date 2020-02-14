def main():
    # Ask for user input to create a list, which is in the ascendent order
    b = int(input("Begin a random list with: "))
    e = int(input("End a random list with: "))
    c = int(input("Increment in a random list with: "))
    lst = List(b, e, c)
    
    # Ask for an int to be searched
    n = int(input("Search int: "))
    binary(n, lst)


# Create a list based on user input
def List(beg, end, inc):
    # list comprehension to build a range of list
    numList = [num for num in range(beg, end, inc)]
    return numList


# Search for num: n with the binary search
def binary(n, lst):
    # Build a new list as the index list for to track index of n
    index = [ind for ind in range(len(lst))]

    # Repeat iteration till the size of list is 0 
    while len(lst) > 0:
        # The search start from the middle of the list or sublist
        half = round(len(lst) / 2)
        temp = lst[half]

        # If the target is hit, this is it.
        if temp == n:
            print("Found at index {}".format(index[half]))
            exit(0)

        # If the target is smaller than the middle point,
        # slice into the left half of list (exclude the middle point) This is the sublist.
        # and repeat the iteration.
        if temp > n:
            lst = lst[:half]
            index = index[:half]

        # If the target is greater than the middle point,
        # slice into the right half of list (exclude the middle point). This is the sublist.
        # and repeat the iteration.
        if temp < n:
            lst = lst[(half + 1):]
            index = index[(half + 1):]

    # After search, not found.
    print("Not found")
    exit(1)

main()