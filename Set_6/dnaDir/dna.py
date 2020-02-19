from sys import argv, exit
import re

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
    database, STRs = lstSTR(argv[1])

    # read a txt file and build a string of DNA sequence
    Seq = strSeq(argv[2])

    # Count numbers of STRs in the DNA sequence and match with a person's DNA profile
    matchDNA(database, STRs, Seq)


def lstSTR(csvFile):
    # Read and be as a memory in Python, require 3 objects: 
    # File on Disk <--- Connection ---> Memory in Python program 
    # First, save the path on the disk to a path var: csv_path
    csv_path = "/Users/peteryo/Dev/CS50_probs/set_6/dnaDir/dna/{}".format(csvFile)
    # Second, built a connection by open func with reading 'r' mode 
    # and store the connection to a var: csv_con
    csv_con = open(csv_path,'r')
    # Third, use the connection to read lines of the file on the disk
    # and store the contents as a list of strings in a Python var: database
    database = csv_con.readlines()


    # Build STRs list from the first line of the database 
    STRs = []
    # Breakdown the first string object separated by ',' into a list of strings: obj 
    obj = database[0].split(',')
    len_obj = len(obj)
    # Append the desired data to the list var: STRs
    for i in range(1, len_obj,1):
        STRs.append(obj[i])
    # The last string object should be edited
    # Replace '/n' with '' (an empty string)
    STRs[len(STRs) - 1] = STRs[len(STRs) - 1].replace('\n','')

    # return values in the form of tuple
    return database, STRs


def strSeq(txtFile):
    # open the DNA sequence (*.txt) and read its contents into memory
    txt_path = "/Users/peteryo/Dev/CS50_probs/set_6/dnaDir/dna/{}".format(txtFile)
    txt_con = open(txt_path, 'r')
    sequence = txt_con.read()

    return sequence


def matchDNA(database, STRs, sequence):
    # Assign the counts of each STRs into a dict 
    count = {}

    # Replace each STR with an iteration integer
    # Then, count the occurence of each integer and search the maximum value in the count dict 
    for i in range(len(STRs)):
        # Avoid the no occurence
        if STRs[i] not in sequence:
            continue

        # Replace STRs with a new nums, which is the iterator: i
        new = '{}'.format(i)

        # Due to string is an immutable data (a tuple)
        # make sure to assign the returned string to a var
        copy = sequence.replace(STRs[i], new)

        # beginning and ending index of the next for-loop
        # To save the iteration time, 
        # the index start with the first-appeared index of STRs in the sequence
        # end with the last-appeared index
        beg = copy.index(new)
        end = copy.rindex(new) + 1

        # Initiate the value of key (which is STRs) as an empty list 
        # Initiate the empty list with an int 0
        count[STRs[i]] = []
        count[STRs[i]].append(0)

        # Initiate the index of the list: ind
        ind = 0

        for u in range(beg, end, 1):
            # If the num is found in the iteration, Update the list in a dict
            if copy[u] == new:
                count[STRs[i]][ind] += 1

                # Avoid the iteration out of the range of string index
                if (u + 1) == len(copy):
                    continue

                # If the next char in the sequence is not the desired num
                # append an int 0 as a new entry to the list
                if copy[u + 1] != copy[u]:
                    count[STRs[i]].append(0)
                    ind += 1

    # Count the max and assign to a list of stings
    # Use string type to compare the name in the database
    rep = []
    for i in STRs:
        if i in count:
            rep.append(str(max(count[i])))
        # Avoid the zero occurence
        else:
            rep.append('0')
    
    # join the list of string into a single string separated with ','
    rep = ','.join(rep)

    # match the name in the database
    for i in range(1, len(database), 1):
        dnaId = database[i].split(',', 1)
        dnaId[1] = dnaId[1].replace('\n', '')
        if  rep == dnaId[1]:
            print(dnaId[0])
            exit(0)

    print("No match")
    exit(1)


main()