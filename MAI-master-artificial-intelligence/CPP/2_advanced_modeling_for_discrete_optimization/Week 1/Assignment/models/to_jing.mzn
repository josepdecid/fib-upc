% Liu Bei forsees that Yuan Shiu will be defeated by Cao Cao
% He needs to find a route to safety in Jin province before the defeat
% But Cao Cao's soldiers are everywhere

int: nrow;
set of int: ROW = 1..nrow;
set of int: ROW0 = 0..nrow;

int: ncol;
set of int: COL = 1..ncol;
set of int: COL0 = 0..ncol;

int: dummy = 0;

% Plains, Mountain, Forest, City, River
enum TERRAIN = { P, M, F, C, R };
array[TERRAIN] of int: delay;
int: timelimit;

array[ROW,COL] of TERRAIN: terrain;
array[ROW,COL] of int: soldier;
array[ROW,COL] of bool: Jin;

int: start_row;
int: start_col;

int: maxstep;
set of int: STEP = 1..maxstep;
set of int: STEP0 = 0..maxstep;

var STEP: steps;
array[STEP] of var ROW0: visited_rows; % which step do we visit position or 0 if not visited
array[STEP] of var COL0: visited_cols; % which step do we visit position or 0 if not visited

% start at start position
constraint visited_rows[1] = start_row;
constraint visited_cols[1] = start_col;

% reach Jin province
constraint exists(i in 1..steps)(Jin[visited_rows[i], visited_cols[i]]);

% visit at most one city
constraint sum(i in 1..steps)(terrain[visited_rows[i], visited_cols[i]] = C) <= 1;

% cant enter Mountain
constraint not exists(i in 1..steps)(terrain[visited_rows[i], visited_cols[i]] = M);

% steps form a path
constraint forall(i in 1..steps-1)(abs(visited_rows[i] - visited_rows[i + 1]) + abs(visited_cols[i] - visited_cols[i + 1]) = 1);
                                   
% after steps all 0
constraint forall(i in steps+1..maxstep)(visited_rows[i] = dummy /\ visited_cols[i] = dummy);

% not too much delay
constraint time <= timelimit;
var int: time = sum(i in 1..steps)(delay[terrain[visited_rows[i], visited_cols[i]]]);

% minimize the number of soldiers traversed
solve minimize obj;
var int: obj = sum(i in 1..steps)(soldier[visited_rows[i], visited_cols[i]]);


array[TERRAIN] of string: ter = [".", "#", "^", "C", "~"];
array[ROW,COL] of var STEP0: visit;
constraint forall(i in 1..steps)(visit[visited_rows[i], visited_cols[i]] = i);

output
       ["%"] ++
       [ " " ++ ter[fix(terrain[r,c])] ++ if c = ncol then "\n%" else "" endif
       | r in ROW, c in COL ]
       ++ ["\n%"] ++
       [ if soldier[r,c] > 0 then show_int(2,soldier[r,c]) else " ." endif
         ++ if c = ncol then "\n%" else "" endif
       | r in ROW, c in COL ]
       ++ ["\n"] ++
       ["%"] ++
       [ if fix(visit[r,c]) > 0 then show_int(2,visit[r,c]) else " ." endif
         ++ if c = ncol then "\n%" else "" endif
       | r in ROW, c in COL ]
       ++ ["\nvisit = array2d(ROW,COL,\(visit));\nsteps = \(steps);\ntime = \(time);\nobj = \(obj);"]
       ;
