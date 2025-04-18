import csv
import sys


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <csv_file> <text_file>")
        sys.exit(1)

    # Read database file into a variable
    db = {}
    with open(sys.argv[1]) as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            db[row["name"]] = row
            db[row["name"]].pop("name")
            
    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequence_file:
        sequence = sequence_file.read().strip()
    
    # Find longest match of each STR in DNA sequence
    longests = {}
    for s in reader.fieldnames:
        if s != "name":
            longests[s] = longest_match(sequence, s)

    # Check database for matching profile
    for person, seqs in db.items():
        found = True
        for s in seqs:
            if int(db[person][s]) != longests[s]:
                found = False
        if found:
            print(person)
            break
    else:
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
