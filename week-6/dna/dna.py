import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print(f"Usage: python {sys.argv[0]} <db> <sequence>")
        sys.exit(1)


    # Read database file into a variable
    db_rows = []
    try:
        with open(sys.argv[1]) as db_file:
            reader = csv.DictReader(db_file)

            # save strs 
            if reader.fieldnames is None:
                print("csv file doesn't have a header row")
                sys.exit(1)
            strs = [k for k in reader.fieldnames if k != "name"]
            
            for row in reader:
                db_rows.append(row)
    except FileNotFoundError:
        print("Unable to open csv")
        sys.exit(1)

    # Read DNA sequence file into a variable
    try:
        with open(sys.argv[2]) as seq_file:
            sequence = seq_file.read()
    except FileNotFoundError:
        print("Unable to open sequence file")
        sys.exit(1)
    
    # Find longest match of each STR in DNA sequence
    longest_strs = {s: longest_match(sequence, s) for s in strs}

    # Check database for matching profiles
    for person in db_rows:
        match = True
        for s in strs:
            if int(person[s]) != longest_strs[s]:
                match = False
                break

        if match:
            print(person["name"])
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

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
