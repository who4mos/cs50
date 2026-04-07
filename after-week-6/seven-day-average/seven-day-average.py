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


# Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    previous_cases = {}

    for row in reader:
        state = row["state"]
        cumulative_cases = int(row["cases"])

        if state not in new_cases:
            new_cases[state] = []

        if state not in previous_cases:
            previous_cases[state] = 0
            today_cases = cumulative_cases
        else:
            today_cases = cumulative_cases - previous_cases[state]

        previous_cases[state] = cumulative_cases

        new_cases[state].append(today_cases)            
        if len(new_cases[state]) > 14:
            new_cases[state].pop(0)

    return new_cases


# Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        first_week_avg = sum(new_cases[state][:7]) / 7
        second_week_avg = sum(new_cases[state][7:]) / 7

        print(f"{state} had a 7-day average of {round(second_week_avg)}", end=" ")
        
        try:
            percent = (second_week_avg - first_week_avg) / first_week_avg
            if percent > 0:
                print(f"and an increase of {round(percent*100)}%")
            elif percent < 0:
                print(f"and a decrease of {round(abs(percent)*100)}%")
            else:
                print("and no change")
        except ZeroDivisionError:
            if second_week_avg > 0:
                print(f"and an increase from 0 cases")
            else:
                print("and no change")

main()
