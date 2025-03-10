import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    cases = {}
    previous_cases = {}
    
    for row in reader:
        state = row["state"]
        curr_case_count = int(row["cases"])

        if state not in cases:
            cases[state] = []
        else:
            cases[state].append(curr_case_count - previous_cases.setdefault(state, 0))
        
        if len(cases[state]) > 14:
            cases[state].pop(0)

        previous_cases[state] = curr_case_count

    return cases

# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        if state not in new_cases:
            print(f"{state} not in dict!")
            continue

        this_week = sum(new_cases[state][-7:]) / 7
        previous_week = sum(new_cases[state][:7]) / 7

        print(f"{state} had a 7-day average of {round(this_week)}", end=" ")
        print(f"{round(previous_week)}")
        try:
            percent = ((this_week - previous_week) / previous_week) * 100
        except ZeroDivisionError:
            print(".")

        if percent >= 0:
            print(f"and an increase of {percent:.0f}%.")
        else:
            print(f"and a decrease of {-percent:.0f}%.")
            
main()
