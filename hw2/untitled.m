%% EXPERIMENTAL RESULTS PLOTTING CODE

% 1. Load the data from the CSV file
try
    data = readmatrix('farm_results.csv', 'Delimiter', ';', 'NumHeaderLines', 2);
catch
    disp('Error: Could not read farm_results.csv.');
    disp('Please ensure the file is in the current MATLAB folder.');
    return;
end

% 2. Extract N values (first column)
N_values = data(:, 1);

% Columns in the CSV:
% 1: N
% 2-5: Linear Search
% 6-9: Binary Search
% 10-13: Jump Search
Linear_data = data(:, 2:5);
Binary_data = data(:, 6:9);
Jump_data   = data(:, 10:13);

K_labels = {'K=1', 'K=N/8', 'K=N/4', 'K=N/2'};

% 3. Plotting Setup
figure('Name', 'Experimental Algorithm Efficiency');
set(gcf, 'Position', [100, 100, 1200, 500]);

%% --- Subplot 1: Linear Search ---
subplot(1, 3, 1);
plot(N_values, Linear_data, 'LineWidth', 2);
title('Linear Search Experimental Runtime');
xlabel('Number of Sheep (N)');
ylabel('Average Time (ms)');
legend(K_labels, 'Location', 'northwest');
grid on;

set(gca, 'XScale', 'log');   % log N
set(gca, 'YScale', 'log');   % log Time
set(gca, 'FontSize', 10);

%% --- Subplot 2: Binary Search ---
subplot(1, 3, 2);
plot(N_values, Binary_data, 'LineWidth', 2);
title('Binary Search Experimental Runtime');
xlabel('Number of Sheep (N)');
ylabel('Average Time (ms)');
legend(K_labels, 'Location', 'northwest');
grid on;

set(gca, 'XScale', 'log');
set(gca, 'YScale', 'log');
set(gca, 'FontSize', 10);

%% --- Subplot 3: Jump Search ---
subplot(1, 3, 3);
plot(N_values, Jump_data, 'LineWidth', 2);
title('Jump Search Experimental Runtime');
xlabel('Number of Sheep (N)');
ylabel('Average Time (ms)');
legend(K_labels, 'Location', 'northwest');
grid on;

set(gca, 'XScale', 'log');
set(gca, 'YScale', 'log');
set(gca, 'FontSize', 10);

sgtitle('Runtime Comparisons Based On Search Algorithms Using Logarithmic Scale');