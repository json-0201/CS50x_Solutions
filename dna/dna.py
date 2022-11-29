import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit()

    # TODO: Read database file into a variable
    db = []

    with open(sys.argv[1], "r") as f:
        reader = csv.DictReader(f)  # Reader -> object file for each row
        db = list(reader)   # List of Dictionaries
    # print(db)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as f:
        seq = f.read()  # seq -> string variable

    # TODO: Find longest match of each STR in DNA sequence
    STR = [list(db[0].keys())[i] for i in range(1, len(db[0]))]
    # print(STR)

    STR_match = {}
    for i in range(len(STR)):
        # longest_match returns int
        counter = longest_match(seq, STR[i])
        STR_match[STR[i]] = counter
    # print(STR_match)

    # TODO: Check database for matching profiles
    # For every suspect
    for i in range(len(db)):

        # Count reset for each suspect
        count = 0

        # For every STR
        for j in range(len(STR)):
            if STR_match[STR[j]] == int(db[i][STR[j]]):
                count += 1

            # If count equals len(STR), every STR has equal number of longest run
            if count == len(STR):
                print(db[i]["name"])
                sys.exit()

    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)   # number of characters
    sequence_length = len(sequence)         # number of characters

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
