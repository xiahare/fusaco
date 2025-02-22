from bisect import bisect_left

# Read the number of elements
n = int(input())

# Read the list of numbers as a single line of space-separated values
numbers = list(map(int, input().split()))

# Use a dictionary to count occurrences of each number
m = {}
for a in numbers:
    if a in m:
        m[a] += 1
    else:
        m[a] = 1

# Create a sorted list of unique numbers
v = sorted(m.keys())

# Iterate through all possible values from 0 to n
for i in range(n + 1):
    # Find the number of elements in v that are less than i
    exists_before_i = bisect_left(v, i)
    
    # Calculate the number of "blanks" before i
    blanks_i = i - exists_before_i
    
    # Get the count of the current number i in the map (default to 0 if not present)
    cnt_i = m.get(i, 0)
    
    # Print the maximum of blanks_i and cnt_i
    print(max(blanks_i, cnt_i))
