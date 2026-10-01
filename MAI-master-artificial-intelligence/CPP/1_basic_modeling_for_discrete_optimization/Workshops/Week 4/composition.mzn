int: n;

set of int: NOTE = 1..n;
set of int: ORDER = 1..n;

set of int: NOTE1 = 1..n-1;
set of int: ORDER1 = 1..n-1;

array[ORDER] of var NOTE: order;
array[ORDER1] of var NOTE1: diffs;

constraint forall(i in ORDER1)(diffs[i] = abs(order[i] - order[i + 1]));

include "alldifferent.mzn";
constraint alldifferent(order);
constraint alldifferent(diffs);

solve satisfy;

int: d = ceil(ln(n + 1) / ln(10.0));
string: spaces = concat([" " | j in 1..d]);
output [show_int(d, order[i]) ++ spaces | i in ORDER]
    ++ ["\n", spaces]
    ++ [show_int(d, diffs[i]) ++ spaces | i in ORDER1];