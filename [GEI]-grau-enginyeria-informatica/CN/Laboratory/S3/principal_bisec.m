%% Principal Bisection
%  Thursday 8th March 2018

%% Plot
f = @(x) x.^6 - x - 1;
t = 1:0.05:1.4;
plot(t, t.^6, t, t + 1), grid, title('equació');

%% Iterations
a = 1;
b = 1.2;
tol = 0.05;
root = my_bisec(f, a, b, tol, 5);