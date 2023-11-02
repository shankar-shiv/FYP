import pandas as pd
from io import StringIO

# Sample CSV data
csv_data = """
0.826923  0.581731  0.307692  0.125000  0.000000  0.125000  0.230769
0.971256  0.851740  0.390318  0.071104  0.021180  0.110439  0.163389
0.123456  0.654321  0.789123  0.456789  0.098765  0.123456  0.135790
"""

# Read CSV data into a pandas DataFrame
df = pd.read_csv(StringIO(csv_data), header=None, delim_whitespace=True)

# Calculate differences between adjacent rows
differences = df.diff().fillna(0)

# Print the differences
for i, (index, row) in enumerate(differences.iterrows(), start=1):
    print(f"Row {i} - Row {i+1}")
    print(row)
    print()

# Note: The first row contains differences relative to the second row,
# the second row contains differences relative to the third row, and so on.
