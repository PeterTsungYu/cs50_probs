import random

def main():
    # User type in a list ??
    """ ans = input("Auto? (y/n) ")
    if ans == 'y':
        # Ask for user input to create a list, which is in the ascendent order
        b = int(input("Begin a random list with: "))
        e = int(input("End a random list with: "))
        c = int(input("Increment in a random list with: "))
        randlst = randList(b, e, c)
        print(randlst)
    else:
        randlst = list(input("Input: ")) """

    # Like this...
    randlst = [3,5,6,6,6,1,3,8,9,3,4,5,9,10,2,6,7,4]

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