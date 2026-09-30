e = exp(1);
f = @(x) (5 - x) .* e.^x - 5;
x = -10:0.1:5.1;
y = f(x);

figure, grid, hold on
plot(x, y); hold off

pause;

figure, grid, hold on

% Bisection 

[root, tab] = my_bisec(f, 4, 6, .5e-6);
disp(root);

a = table2array(tab(:, 2));
b = table2array(tab(:, 3));
dif = (b - a) ./ 2;
plot(1:length(dif), log(abs(dif)));

% Secant

[root, tab] = my_secant(f, 4, 6, .5e-6);
disp(root);

dif = table2array(tab(:, 4));
xn = table2array(tab(:, 2));
plot(1:length(xn), log(abs(dif ./ xn)));

%  Newton

df = @(x) e^x * (4 - x);
d2f = @(x) e^x * (3 - x);
[root, tab] = my_newton(f, df, d2f, 4, 6, .5e-6);
disp(root);

dif = table2array(tab(:, 4));
xn = table2array(tab(:, 2));
plot(1:length(xn), log(abs(dif ./ xn)));

hold off