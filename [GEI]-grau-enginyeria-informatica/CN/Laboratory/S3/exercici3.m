%% Exercice 3 - Lab3
%  Thursday 8th March 2018
clear

%% Plot
f = @(x) x.^6 - x - 1;
df = @(x) exp(x) + 1;
t = -4:0.05:4;
plot(t, exp(t), t, 2 - t), grid, title('equation');

%% FZero Matlab
format long g
alpha = fzero(f, 0.4);
disp(alpha);
format

%% Iterations Newton
b = 1.2;
tol = 0.05;
root = my_bisec(f, df, b, tol, 5);
disp(root);

%% Iterations Bisection
tol = 0.005;
if f(a)*f(b) < 0
   root = my_bisec(f, a, b, tol, 5);
   disp(root);
else
   disp('Bolzano theorem is not satisfied');
end

%% Iterations Secant
a = 1;
b = 1.2;
tol = 0.0000005;
root = my_secant(f, a, b, tol, 5);
disp(root);