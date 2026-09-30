%% Generate matrices
A = [3 1 ; 0 4];
B = [1 2 ; -2 6];
C = [2 -5 ; 3 4];

%% Check equalties and display results
a = isequal((A*B)*C, A*(B*C));
b = isequal(A*(B+C), A*B + A*C);
c = isequal((A*B)', B'*A');

disp(a);
disp(b);
disp(c);