int: n;  % number of soldiers
int: CAPITAIN = 1;
set of int: SOLDIER = 1..n;
set of int: POS = 1..n;
array[SOLDIER] of int: height;
int: cols;    % number of columns of soldiers
int: delta;   % height delta allowed

array[POS] of var SOLDIER: soldier;
array[SOLDIER] of var POS: position;

% Bidirectional mapping soldier <-> position;
include "inverse.mzn";
constraint inverse(soldier, position);

% Capitain is in the first position
constraint position[CAPITAIN] = 1;

% It's not necessary to build a matrix, we can offset by the #cols and check that positions precede
constraint forall(s1, s2 in 2..n where s1 + cols = s2)(position[s1] < position[s2]);

% Calculate the height different between consecutive soldiers
array[2..n-1] of var int: hdif;
constraint forall(s in 2..n-1)(hdif[s] = abs(height[soldier[s]] - height[soldier[s + 1]]));

% The objective is the to get the minimum value that exceed the delta difference
var int: obj;
constraint obj = min(s in 2..n-1)(if hdif[s] > delta then s else n endif);

% After some experiments these are the combination of search configurations that seem to work better.
% As we want to get the minimum difference value following the parade order it has sense that the best results are obtained using this configuration.

solve
:: int_search(soldier, input_order, indomain_min, complete)
maximize obj;

output ["obj=\(obj);\n"] ++ ["pos=\(position);\n"];