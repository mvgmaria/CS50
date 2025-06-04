import csv
from sys import argv


def main():

    if len(argv) != 3:
        print("Please input the csv and text file for the DNA identification")

    with open(argv[1], "r") as file:
        reader_db = csv.DictReader(file)
        field_names = reader_db.fieldnames[1:]

        with open(argv[2], "r") as nother_file:
            reader_seq = nother_file.read()

        # for each person in the db
        for row in reader_db:
            for field in field_names:
                longest_run = longest_match(reader_seq, field)
                if str(longest_run) == row[field]:
                    match = True
                else:
                    match = False
                    break
            if match == True:
                print(row["name"])
                break
        if match == False:
            print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

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
