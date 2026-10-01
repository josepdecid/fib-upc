int: n;

set of int: NOTE = 1..n;
set of int: ORDER = 1..n;

set of int: NOTE1 = 1..n-1;
set of int: ORDER1 = 1..n-1;

array[ORDER] of var NOTE: order;
array[ORDER1] of var NOTE1: diffs;
array[NOTE] of var ORDER: posn;
array[NOTE1] of var ORDER1: dposn;

constraint forall(i in ORDER1)(diffs[i] = abs(order[i] - order[i + 1]));
constraint abs(posn[1] - posn[n]) = 1;

include "inverse.mzn";
constraint inverse(order, posn);
constraint inverse(diffs, dposn);

solve satisfy;

int: d = ceil(ln(n + 1) / ln(10.0));
string: spaces = concat([" " | j in 1..d]);
output [show_int(d, order[i]) ++ spaces | i in ORDER]
    ++ ["\n", spaces]
    ++ [show_int(d, diffs[i]) ++ spaces | i in ORDER1];