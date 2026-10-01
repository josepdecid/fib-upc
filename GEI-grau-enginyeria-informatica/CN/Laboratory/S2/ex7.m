%% Exercice 7 - list Lab2
%  Wednesday 7th March 2018
%% Sensible to initial conditions

A = [2 -4 ; -2.988 6.001];
b = [1 ; 2];
x_sol = A/b;

B = inv(A);
disp(det(B));

%% 

A = [2 -4 ; -2.988 6];
x_sol2 = A/b;

B = inv(A);
disp(det(B));