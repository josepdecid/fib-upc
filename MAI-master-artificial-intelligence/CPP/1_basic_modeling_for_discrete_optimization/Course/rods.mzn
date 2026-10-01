include "alldifferent.mzn";

set of int: DIGIT = 1..9;
array[DIGIT] of int: rods = [1, 2, 3, 4, 5, 2, 3, 4, 5];

% Messed up digits
var DIGIT: M1;
var DIGIT: M2;
var DIGIT: M3;
var DIGIT: M4;
var DIGIT: M5;

constraint alldifferent([M1, M2, M3, M4, M5]);
constraint rods[M1] + rods[M2] + rods[M3] + rods[M4] + rods[M5] = 12;
constraint 2303 + M1*10 + 980 + M2*1000 + M3 = 301 + M4*1000 + M5*10;

solve satisfy;