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
    # 3, 5.3, -6,6,60, 1, -3, 73, -4.9, 131.56, 156.78, -54.32, 56.879, 75.89, 34...5 
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
    
    # Merge sort the random list
    sortlst = mergeSort(randlst)
    print(sortlst)


# Create a list based on user input
def randList(beg, end, inc):
    # list comprehension to build a range of list
    List = [num for num in range(beg, end, inc)]
    random.shuffle(List)
    return List


# How to debug a recursive function? 
# Set a reasonable breakpoint will be a challenge...
def mergeSort(lst):
    len_lst = len(lst)

    # if the size of list is equal to 1 (with only one element)
    # then return the list itself 
    if len_lst == 1:
        return lst

    # slice the original input (lst) into right and left halves 
    half = round(len_lst / 2)
    left = lst[:half]
    right = lst[half:]

    # Recursive function to sort the left and right halves
    # the returned (sort) list should be assigned back to the halves
    # so that the recursive is making use of the nesting or nutshell module
    left = mergeSort(left)
    right = mergeSort(right)


    # the last sorting part
    # sorted elements is put in a sort list
    # Initiate the sort list with all int 0
    sort = [0] * len_lst
    # i, the index for the left
    # u, the index for the right
    i = 0
    u = 0

    # Iteration over the sort list to put elements into
    for v in range(len_lst):
        # if the left elements all has  been looked through
        # then the rest of the right elements could be all put into the rest position of sort list
        # and break the loop
        if i == half:
            sort[v:] = right[u:]
            break

        # if the right elements all has  been looked through
        # then the rest of the left elements could be all put into the rest position of sort list
        # and break the loop
        if u == (len_lst - half):
            sort[v:] = left[i:]
            break
        # the break condition should be put on the top of loop
        # otherwise the index of list could be out of range

        # put the smallest element first
        # remembering the list are sorted in order before this loop
        # if the element haven't be put into sort list, the next iteration should start from the same index
        # thus, the comparation should not be for-loops, but require two var (i, u) to process
        if left[i] >= right[u]:
            sort[v] = right[u]
            u += 1
            continue
        else:
            sort[v] = left[i]
            i += 1
            continue

    # return the sort list    
    return sort

main()