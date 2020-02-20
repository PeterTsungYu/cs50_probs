import csv

path = '/Users/peteryo/Dev/CS50_probs/Set_6/dnaDir/dna/databases/small.csv'

# If csvfile is a file object, it should be opened with newline=''.
# It is the default dialect parameter for a *.csv file.
with open(path, newline='') as csvfile:
    # delimiter is gonna separate the line into objects. Default is delimeter = ','. Should return as a list of strings.
    # if delimiter = ' ', a space, then the line will not be separated. Should return as a list of a string. 
    dnareader = csv.reader(csvfile, delimiter = ' ')
    for row in dnareader:
        # row is a list of strings
        print(row)
        # .join() method could be applied on a list object; return as a single string
        print(';'.join(row))
""" 
['name,AGATC,AATG,TATC']
name,AGATC,AATG,TATC
['Alice,2,8,3']
Alice,2,8,3
['Bob,4,1,5']
Bob,4,1,5
['Charlie,3,2,5']
Charlie,3,2,5
"""


with open(path, newline='') as csvfile:
    dnareader = csv.DictReader(csvfile)
    for row in dnareader:
        print(row['name'], row['AGATC'], row['AATG'], row['TATC'])

""" 
Alice 2 8 3
Bob 4 1 5
Charlie 3 2 5 
"""

csv_con = open(path,'r')
database = csv_con.readlines()
print(database)
# output: ['name,AGATC,AATG,TATC\n', 'Alice,2,8,3\n', 'Bob,4,1,5\n', 'Charlie,3,2,5\n']


