import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import FuncFormatter

# --- CONFIGURATION ---
CSV_FILE = 'farm_results.csv'

# 1. Load Actual Data
try:
    # Read CSV, skipping the first 2 header lines
    column_names = [
        'N', 
        'Linear_1', 'Linear_N8', 'Linear_N4', 'Linear_N2',
        'Binary_1', 'Binary_N8', 'Binary_N4', 'Binary_N2',
        'Jump_1', 'Jump_N8', 'Jump_N4', 'Jump_N2'
    ]
    df = pd.read_csv(CSV_FILE, delimiter=';', skiprows=2, header=None, names=column_names)
    
    # Ensure numeric
    for col in df.columns:
        df[col] = pd.to_numeric(df[col], errors='coerce')
        
except FileNotFoundError:
    print(f"Error: '{CSV_FILE}' not found. Please run main.cpp first.")
    exit()

# 2. Calculate Theoretical Data
# We generate a new DataFrame based on the N values from the CSV
theo_df = pd.DataFrame({'N': df['N']})

# Helper to calculate complexity
def calc_linear(n, k): return n + k
def calc_binary(n, k): return np.log2(n) + k
def calc_jump(n, k):   return np.sqrt(n) + k

# Generate columns for each K scenario
# K values: 1, N/8, N/4, N/2
theo_df['Linear_1'] = calc_linear(theo_df['N'], 1)
theo_df['Linear_N8'] = calc_linear(theo_df['N'], theo_df['N']/8)
theo_df['Linear_N4'] = calc_linear(theo_df['N'], theo_df['N']/4)
theo_df['Linear_N2'] = calc_linear(theo_df['N'], theo_df['N']/2)

theo_df['Binary_1'] = calc_binary(theo_df['N'], 1)
theo_df['Binary_N8'] = calc_binary(theo_df['N'], theo_df['N']/8)
theo_df['Binary_N4'] = calc_binary(theo_df['N'], theo_df['N']/4)
theo_df['Binary_N2'] = calc_binary(theo_df['N'], theo_df['N']/2)

theo_df['Jump_1'] = calc_jump(theo_df['N'], 1)
theo_df['Jump_N8'] = calc_jump(theo_df['N'], theo_df['N']/8)
theo_df['Jump_N4'] = calc_jump(theo_df['N'], theo_df['N']/4)
theo_df['Jump_N2'] = calc_jump(theo_df['N'], theo_df['N']/2)

# 3. Plotting Setup
fig, axes = plt.subplots(2, 3, figsize=(18, 10), sharex=True)
labels = ['K=1', 'K=N/8', 'K=N/4', 'K=N/2']
markers = ['o', 's', '^', 'd']

# X-Axis Formatter (2^x)
def format_func(value, tick_number):
    if value <= 0: return ""
    exp = np.log2(value)
    return r'$2^{{{:.0f}}}$'.format(exp)

def plot_group(ax_idx, col_prefix, data_source, title, y_label):
    ax = axes[ax_idx]
    suffixes = ['_1', '_N8', '_N4', '_N2']
    
    for i, suffix in enumerate(suffixes):
        col_name = col_prefix + suffix
        ax.plot(data_source['N'], data_source[col_name], 
                marker=markers[i], label=labels[i], linewidth=2)

    ax.set_title(title, fontsize=12, fontweight='bold')
    if ax_idx[1] == 0: # Only first column gets Y label
        ax.set_ylabel(y_label, fontsize=10)
    
    ax.set_xscale('log', base=2)
    ax.set_xticks(df['N']) # Force ticks for all N
    ax.xaxis.set_major_formatter(FuncFormatter(format_func))
    ax.grid(True, which="major", linestyle='-', alpha=0.4)
    ax.legend()


# --- ROW 1: ACTUAL RESULTS (Time in ms) ---
plot_group((0, 0), 'Linear', df, 'Actual: Linear Search', 'Time (ms)')
plot_group((0, 1), 'Binary', df, 'Actual: Binary Search', '')
plot_group((0, 2), 'Jump',   df, 'Actual: Jump Search', '')

# --- ROW 2: THEORETICAL RESULTS (Complexity Score) ---
plot_group((1, 0), 'Linear', theo_df, 'Theoretical: O(N + K)', 'Complexity Ops')
plot_group((1, 1), 'Binary', theo_df, 'Theoretical: O(log N + K)', '')
plot_group((1, 2), 'Jump',   theo_df, 'Theoretical: O(√N + K)', '')
# Final Layout Adjustments
plt.tight_layout()
plt.show()