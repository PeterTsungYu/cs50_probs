import random

def main():
    # Ask for user input to create a list, which is in the ascendent order
    b = int(input("Begin a random list with: "))
    e = int(input("End a random list with: "))
    c = int(input("Increment in a random list with: "))
    randlst = randList(b, e, c)
    print(randlst)

    # Insertion sort the random list
    sortlst = insertSort(randlst)
    print(sortlst)


# Create a list based on user input
def randList(beg, end, inc):
    # list comprehension to build a range of list
    List = [num for num in range(beg, end, inc)]
    random.shuffle(List)
    return List


def insertSort(lst):
    # Build a new list for inserting the sorted element from lst
    sort = []
    # Initiate the sort list with the first element of lst
    sort.append(lst[0])

    # Iterate thru the lst from the index = 1
    for i in range(1, len(lst), 1):
        # Initiate the insertion counter to 0
        counter = 0

        # insert the lower value from lst to the sort
        # shift backward from current index, in the usage of .insert method
        for u in range(0, len(sort), 1):
            if lst[i] <= sort[u]:
                # .insert method is going to insert into a list and shift one element backword
                # Thus, the length of list is increased 
                sort.insert(u, lst[i])
                counter = 1
                # After the insertion, break the current for-loop for u in sort
                # jump to the outter for-loop for i in lst
                break
        
        # if the insertion never happend, then append the greater value to the last
        if counter == 0:
            sort.append(lst[i])
        
    return sort

main()