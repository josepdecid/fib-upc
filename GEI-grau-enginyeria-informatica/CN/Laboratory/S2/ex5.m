%% Exercice 5 - list Lab2
%  Wednesday 7th March 2018

f = @(x) sqrt(x.^2 + 1) - 1;
g = @(x) x.^2 ./ (sqrt(x.^2 + 1) + 1);

n = 1:15;
t = 8.^(-n);

y1 = f(t);
y2 = g(t);

[n ; t ; y1 ; y2]'