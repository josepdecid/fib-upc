%% Principal Bisection
%  Thursday 8th March 2018

%% Plot
f = @(x) x.^6 - x - 1;
t = 1:0.05:1.4;
plot(t, t.^6, t, t + 1), grid, title('equació');

%% Iterations Newton
a = 1;
b = 1.2;
tol = 0.05;
root = my_bisec(f, a, b, tol, 5);
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