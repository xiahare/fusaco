# Read input values for n (size of the grid) and u (number of updates)
n, u = map(int, input().split())

# Initialize a 2D list (grid) of size n x n with False values
v = [[False for _ in range(n)] for _ in range(n)]

# Populate the grid based on input characters
for i in range(n):
    row = input().strip()
    for j in range(n):
        v[i][j] = (row[j] == '#')  # Set to True if the character is '#', otherwise False

# Define a lambda function to calculate the minimum operations for a cell and its symmetric counterparts
min_ops = lambda x, y: 2 - abs(2 - (v[x][y] + v[n-1-x][y] + v[x][n-1-y] + v[n-1-x][n-1-y]))

# Calculate the total minimum operations for the entire grid
m = n // 2  # Only need to iterate through half the grid due to symmetry
total_min_ops = 0
for i in range(m):
    for j in range(m):
        total_min_ops += min_ops(i, j)

# Print the total minimum operations
print(total_min_ops)

# Process each update
for _ in range(u):
    x0, y0 = map(int, input().split())  # Read the coordinates (1-indexed)
    x0 -= 1  # Convert to 0-indexed
    y0 -= 1

    # Calculate the original and current minimum operations for the cell and its symmetric counterparts
    org = min_ops(x0, y0)
    v[x0][y0] = not v[x0][y0]  # Toggle the cell value
    cur = min_ops(x0, y0)

    # Update the total minimum operations
    total_min_ops += cur - org

    # Print the updated total minimum operations
    print(total_min_ops)