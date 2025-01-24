% Specify the file path
file_path = 'i_and_t_values.txt';

% Read the data using readtable
data_table = readtable(file_path, 'Delimiter', ' ');

% Convert table to array
data = table2array(data_table);

% Extract the data from the array
% Assuming your data is numeric
i_values = data(:, 1);
t_values = data(:, 2)/1000;

filename = ['I2T','.mat']; % Descriptive name timestamp
save(filename);

% Set default figure properties
set(0,'DefaultAxesFontSize',8); 
set(0,'DefaultFigureColor','w');
set(0,'defaulttextinterpreter','latex');
set(0, 'DefaultAxesFontName', 'times');

% Create a figure with specified size
figure('Units', 'centimeters', 'Position', [0, 0, 8.89, 6]);

% Plot with logarithmic scale on y-axis
plot(i_values, t_values, 'LineWidth', 1);
xlabel('Current in A','Interpreter','latex');
ylabel('Trip-time in S (log scale)','Interpreter','latex');
title('I$^{2}$t trip curve','Interpreter','latex');
hold on;

% Highlight the range from 10A to 20A
highlight_range = i_values >= 25.5 & i_values <= 32.99;
plot(i_values(highlight_range), t_values(highlight_range), 'r', 'LineWidth', 1);

legend('Experimental values', 'Calculated values');

% Export the figure
%filename = ['I2T','.pdf']; % Descriptive name timestamp and .png file format
%export_fig (filename, '-m3', '-nocrop');
