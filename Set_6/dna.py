from sys import argv, exit
import re


if (len(argv) != 3):
# Command line arg, argv, index [0] start after the "python"
    print("Usage: python dna.py data.csv sequence.txt")
# re.search the file with the extension name as *.csv as the second argv
if not re.search('.*[.]csv$',argv[1]):
    print("Usage: Please include *.csv file as the second arument")
# re.search the file with the extension name as *.txt as the third argv
if not re.search('.*[.]txt$',argv[2]):
    print("Usage: Please include *.txt file as the third arument")


# Read and be as a memory in Python, require 3 objects: 
# File on Disk <--- Connection ---> Memory in Python program 
# First, save the path on the disk to a path var: csv_path
csv_path = "/Users/peteryo/Dev/CS50_probs/set_6/dna/{}".format(argv[1])
# Second, built a connection by open func with reading 'r' mode 
# and store the connection to a var: csv_con
csv_con = open(csv_path,'r')
# Third, use the connection to read lines of the file on the disk
# and store the contents as a list of strings in a Python var: database
database = csv_con.readlines()


# Build STR list from the first line of the database 
STR = []
# Breakdown the first string object separated by ',' into a list of strings: obj 
obj = database[0].split(',')
len_obj = len(obj)
# Append the desired data to the list var: STR
for i in range(1, len_obj,1):
    STR.append(obj[i])
# The last string object should be edited
# Replace '/n' with '' (an empty string)
STR[len(STR) - 1] = STR[len(STR) - 1].replace('\n','')


# open the DNA sequence (*.txt) and read its contents into memory
txt_path = "/Users/peteryo/Dev/CS50_probs/set_6/dna/{}".format(argv[2])
txt_con = open(txt_path, 'r')
sequence = txt_con.read()


len_STR = len(STR)
len_seq = len(sequence)
# Assign the counts of each STR into a dict 
count = {}
for i in range(len_STR):
    new = '{}'.format(i)
    # Replace STR with a new nums, which is the iterator: i
    # Due to string is an immutable data (a tuple)
    # make sure to assign the returned string to a var
    sequence = sequence.replace(STR[i], new)
    # beginning and ending index of the next for-loop
    # To save the iteration time, 
    # the index start with the first-appeared index of STR in the sequence
    # end with the last-appeared index
    beg = sequence.index(new)
    end = sequence.rindex(new) + 1
    # Initiate the value of key (which is STR) as an empty list 
    # Initiate the empty list with an int 0
    count[STR[i]] = []
    count[STR[i]].append(0)
    # Initiate the index of the list: ind
    ind = 0
    # tot = sequence.count(new)
    for u in range(beg, end, 1):
        # If the num is found in the iteration, Update the list in a dict
        if sequence[u] == new:
            count[STR[i]][ind] += 1
            # Avoid the iteration out of the range of string index
            if (u + 1) != len_seq:
                # If the next char in the sequence is not the desired num
                # append an int 0 as a new entry to the list
                if sequence[u + 1] != sequence[u]:
                    count[STR[i]].append(0)
                    ind += 1

rep = []
for i in range(len_STR):
    rep.append(str(max(count[STR[i]])))
rep = ','.join(rep)

len_database = len(database)
for i in range(1, len_database, 1):
    dnaId = database[i].split(',', 1)
    dnaId[1] = dnaId[1].replace('\n', '')
    if  rep == dnaId[1]:
        print(dnaId[0])
        exit(0)
print("No match")
exit(1)