import csv
from sys import argv, exit


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    str_file = open(argv[2], "r")
    new = str_file.readline()

    with open(argv[1], "r") as csv_file:
        reader = csv.reader(csv_file)
        #dict_csv = csv.DictReader(csv_file)

        # make dictionary
        sequence = list(csv_file.readline().split(","))
        sequence[len(sequence) - 1] = sequence[len(sequence) - 1].replace("\n", "")  # remove the last \n character
        dictionary = {}
        for i in range(len(sequence)):  # create dictionary
            dictionary[sequence[i]] = 0
            #ictionary.pop("name", "0")

        #comp = {}
        # for i in range(len(sequence)): #create dictionary
        #    comp[sequence[i]] = 0

        data = []
        for line in csv_file:
            data_line = line.rstrip().split(',')
            data.append(data_line)

        for key in dictionary:
            lenght = len(key)
            s = 0
            i = 0
            while i <= len(new):
                counter = 0
                while new[i:(i + lenght)] == key:
                    counter += 1
                    i += len(key)

                if counter > dictionary[key]:
                    dictionary[key] = counter
                    counter = 0

                i += 1
        # print(dictionary)

        comp_list = []
        for key in dictionary:
            comp_list.append(str(dictionary[key]))

        comp_list.pop(0)
        for i in data:
            last = i[1:(len(data)+1)]
            if comp_list == last:
                print(i[0])
                exit(0)

        print("No match")
        print(dictionary)
        
        
main()