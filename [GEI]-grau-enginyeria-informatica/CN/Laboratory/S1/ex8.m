%% Create matrices
A = [4 2 ; 2 1];
B = [-2 -1 ; 4 2];

%% Display result of false equalty
AB = A*B;
BA = B*A;

disp(isequal(AB, BA));