import csv
import sys

def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # Read database file into a variable
    database = []
    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        dna_sequence = file.read()

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    str_sequences = list(database[0].keys())[1:]  # Get the STRs from the first row (except the name)

    for str_seq in str_sequences:
        str_counts[str_seq] = longest_match(dna_sequence, str_seq)

    # Check database for matching profiles
    for person in database:
        match = True
        for str_seq in str_sequences:
            if int(person[str_seq]) != str_counts[str_seq]:
                match = False
                break

        if match:
            print(person['name'])
            return

    print("No match")


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
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # Return longest run found
    return longest_run


if __name__ == "__main__":
    main()
