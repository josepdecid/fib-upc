%% Exercice 6 - list Lab2
%  Wednesday 7th March 2018
%% Sensible to initial conditions

r = 1:10;
p = poly(r);
disp(p');
rs = roots(p);
format long g
q = p;
q(2) = q(2) + 2^(-13);
disp(q');
rs2 = roots(q);