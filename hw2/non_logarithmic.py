import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter

# --- 1. SETUP & DATA LOADING ---
CSV_FILE = 'farm_results.csv'

# Explicit column names to match the CSV structure
column_names = [
    'N', 
    'Linear_1', 'Linear_N8', 'Linear_N4', 'Linear_N2',
    'Binary_1', 'Binary_N8', 'Binary_N4', 'Binary_N2',
    'Jump_1', 'Jump_N8', 'Jump_N4', 'Jump_N2'
]

try:
    # Read CSV, skipping the first 2 header lines
    df = pd.read_csv(CSV_FILE, delimiter=';', skiprows=2, header=None, names=column_names)
except FileNotFoundError:
    print(f"Error: '{CSV_FILE}' not found. Please run main.cpp first.")
    exit()

# Ensure all data is numeric
for col in df.columns:
    df[col] = pd.to_numeric(df[col], errors='coerce')

# --- 2. CALCULATE THEORETICAL VALUES ---
# We create a new dataframe to store theoretical complexity scores
theo_df = pd.DataFrame({'N': df['N']})

# Helper formulas for complexity
# Note: We add 'K' to all because the collection phase takes O(K)
def calc_linear(n, k): return n + k            # O(N + K)
def calc_binary(n, k): return np.log2(n) + k   # O(log N + K)
def calc_jump(n, k):   return np.sqrt(n) + k   # O(sqrt(N) + K)

# Define K values for calculation
k_1  = 1
k_n8 = theo_df['N'] / 8
k_n4 = theo_df['N'] / 4
k_n2 = theo_df['N'] / 2

# Linear Theoretical
theo_df['Linear_1']  = calc_linear(theo_df['N'], k_1)
theo_df['Linear_N8'] = calc_linear(theo_df['N'], k_n8)
theo_df['Linear_N4'] = calc_linear(theo_df['N'], k_n4)
theo_df['Linear_N2'] = calc_linear(theo_df['N'], k_n2)

# Binary Theoretical
theo_df['Binary_1']  = calc_binary(theo_df['N'], k_1)
theo_df['Binary_N8'] = calc_binary(theo_df['N'], k_n8)
theo_df['Binary_N4'] = calc_binary(theo_df['N'], k_n4)
theo_df['Binary_N2'] = calc_binary(theo_df['N'], k_n2)

# Jump Theoretical
theo_df['Jump_1']  = calc_jump(theo_df['N'], k_1)
theo_df['Jump_N8'] = calc_jump(theo_df['N'], k_n8)
theo_df['Jump_N4'] = calc_jump(theo_df['N'], k_n4)
theo_df['Jump_N2'] = calc_jump(theo_df['N'], k_n2)

# --- 3. PLOTTING ---
# Create a figure with 2 rows and 3 columns
fig, axes = plt.subplots(2, 3, figsize=(18, 10), sharex=True)

# Labels and Markers
labels = ['K=1', 'K=N/8', 'K=N/4', 'K=N/2']
markers = ['o', 's', '^', 'd']


# Function to format X-axis ticks as 2^x
def format_func(value, tick_number):
    if value <= 0: return ""
    exp = np.log2(value)
    return r'$2^{{{:.0f}}}$'.format(exp)


# Helper function to plot a single subplot
def plot_data(ax, data_source, col_prefix, title, y_label=None):
    suffixes = ['_1', '_N8', '_N4', '_N2']
    
    for i, suffix in enumerate(suffixes):
        col_name = col_prefix + suffix
        ax.plot(data_source['N'], data_source[col_name], 
                marker=markers[i], label=labels[i], linewidth=2, markersize=6)

    ax.set_title(title, fontsize=12, fontweight='bold')
    if y_label:
        ax.set_ylabel(y_label, fontsize=10, fontweight='bold')
    
    # Log Scale Logic
    ax.set_xscale('log', base=2)
    ax.set_xticks(df['N']) # Force a tick for every N in the dataset
    ax.xaxis.set_major_formatter(FuncFormatter(format_func))
    
    ax.grid(True, which="major", linestyle='--', alpha=0.6)
    ax.legend(fontsize=9)


# --- ROW 1: ACTUAL RUNTIME ---
plot_data(axes[0, 0], df, 'Linear', 'Actual: Linear Search', 'Time (ms)')
plot_data(axes[0, 1], df, 'Binary', 'Actual: Binary Search')
plot_data(axes[0, 2], df, 'Jump',   'Actual: Jump Search')


# --- ROW 2: THEORETICAL COMPLEXITY ---
plot_data(axes[1, 0], theo_df, 'Linear', 'Theoretical: O(N + K)', 'Operations (Count)')
plot_data(axes[1, 1], theo_df, 'Binary', 'Theoretical: O(log N + K)')
plot_data(axes[1, 2], theo_df, 'Jump',   'Theoretical: O(√N + K)')


# Final Layout
axes[1, 0].set_xlabel('N (Sheep Count)', fontsize=10, fontweight='bold')
axes[1, 1].set_xlabel('N (Sheep Count)', fontsize=10, fontweight='bold')
axes[1, 2].set_xlabel('N (Sheep Count)', fontsize=10, fontweight='bold')

plt.suptitle('Farm Simulator: Actual Runtime vs. Theoretical Complexity', fontsize=16, y=0.98)
plt.tight_layout(rect=[0, 0.03, 1, 0.96]) 

plt.show()