var 0..10: x;

% If we were unable to use the `mod` function,
% we could define another variable y and add
% a new constraint such that 4 * y = x;
constraint x mod 4 = 0;

solve minimize (x - 7) * (x - 7);