%% Generate random matrix of size sumDigits(dni)
dni = '53771416S';
numbers = str2double(num2cell(dni(1:length(dni)-1)));
n = fold(@(acc, x) acc + x, numbers);

A = rand(n, n);

%% Obtain inverse transpose and diagonal
Ainv = inv(A);
Atra = A';
Adia = diag(A);

%% Remove columns 2 and 4
A(:, 2) = [];
A(:, 4) = [];

%% Power each element by 3
A = A .^ 3;

%% Square root of each element
A = sqrt(A);

%% Mean by rows
mu = mean(A, 2);

%% Standard deviation
sigma = std(A, 0, 2);