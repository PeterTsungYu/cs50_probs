from sys import argv, exit
import re
import csv

def main():
    if (len(argv) != 3):
    # Command line arg, argv, index [0] start after the "python"
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    else: 
        # re.search the file with the extension name as *.csv as the second argv
        if not re.search('.*[.]csv$',argv[1]):
            print("Usage: Please include *.csv file as the second arument")
            exit(2)
        # re.search the file with the extension name as *.txt as the third argv
        if not re.search('.*[.]txt$',argv[2]):
            print("Usage: Please include *.txt file as the third arument")
            exit(2)

    # read a csv file and build a list of required STRs
    database, lstSTR = profile(argv[1])

    # read a txt file and build a string of DNA sequence
    Seq = strSeq(argv[2])

    # Count numbers of STRs in the DNA sequence and match with a person's DNA profile
    matchDNA(database, lstSTR, Seq)


def profile(csvFile):
    # Read and be as a memory in Python 
    csv_path = "/Users/peteryo/Dev/CS50_probs/set_6/dnaDir/dna/{}".format(csvFile)
    csv_con = open(csv_path, 'r')
    lst = csv_con.readline().replace('\n', '').split(',')
    lstSTR = []
    for i in lst:
        if i == 'name':
            continue
        lstSTR.append(i)
    
    # database = {'name':[list of STRs]}
    database = {}
    with open(csv_path, newline='') as csvfile:
        dnareader = csv.DictReader(csvfile)
        # the iterator: row is actually a dict object
        # for elements in each row, each element is a value
        # the keys are derived from the names of columns
        # row = {'name of a column' : <a value in a row>}
        for row in dnareader:
            # create a list of values using list comprehension with dict[key]
            database[row['name']] = [row[STR] for STR in lstSTR]

    # return values in the form of a tuple
    return (database, lstSTR)


def strSeq(txtFile):
    # open the DNA sequence (*.txt) and read its contents into memory
    # Read and be as a memory in Python, require 3 objects: 
    # File on Disk <--- Connection ---> Memory in Python program 
    # First, save the path on the disk to a path var: txt_path
    txt_path = "/Users/peteryo/Dev/CS50_probs/set_6/dnaDir/dna/{}".format(txtFile)
    # Second, built a connection by open func with reading 'r' mode 
    # and store the connection to a var: txt_con
    txt_con = open(txt_path, 'r')
    # Third, use the connection to read lines of the file on the disk
    # and store the contents as a list of strings in a Python var: sequence
    sequence = txt_con.read()

    return sequence


def matchDNA(database, lstSTR, sequence):
    # Assign the counts of each lstSTR into a dict 
    count = {}

    # Replace each STR with an iteration integer
    # Then, count the occurence of each integer and search the maximum value in the count dict 
    for i in range(len(lstSTR)):
        # Avoid the no occurence
        if lstSTR[i] not in sequence:
            continue

        # Replace lstSTR with a new nums, which is the iterator: i
        new = '{}'.format(i)

        # Due to string is an immutable data (a tuple)
        # make sure to assign the returned string to a var
        copy = sequence.replace(lstSTR[i], new)

        # beginning and ending index of the next for-loop
        # To save the iteration time, 
        # the index start with the first-appeared index of lstSTR in the sequence
        # end with the last-appeared index
        beg = copy.index(new)
        end = copy.rindex(new) + 1

        # Initiate the value of key (which is lstSTR) as an empty list 
        # Initiate the empty list with an int 0
        count[lstSTR[i]] = []
        count[lstSTR[i]].append(0)

        # Initiate the index of the list: ind
        ind = 0

        for u in range(beg, end, 1):
            # If the num is found in the iteration, Update the list in a dict
            if copy[u] == new:
                count[lstSTR[i]][ind] += 1

                # Avoid the iteration out of the range of string index
                if (u + 1) == len(copy):
                    continue

                # If the next char in the sequence is not the desired num
                # append an int 0 as a new entry to the list
                if copy[u + 1] != copy[u]:
                    count[lstSTR[i]].append(0)
                    ind += 1

    # Count the max and assign to a list of stings
    # Use string type to compare the name in the database
    rep = []
    for i in lstSTR:
        if i in count:
            rep.append(str(max(count[i])))
        # Avoid the zero occurence
        else:
            rep.append('0')

    # match the name in the dict of database
    for name in database:
        if  rep == database[name]:
            print(name)
            exit(0)

    print("No match")
    exit(1)


main()