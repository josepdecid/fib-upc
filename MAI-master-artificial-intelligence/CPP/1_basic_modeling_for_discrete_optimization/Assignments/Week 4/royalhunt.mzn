int: n; % number of court members
set of int: COURT = 1..n;
set of int: COURT_WOUT_EMP = 2..n;
set of int: DCOURT = 0..n;
array[COURT] of int: rank;
array[COURT] of int: ability;

int: dummy = 0;
int: emperor = 1;

int: m; % number of horses
set of int: HORSE = 1..m;
set of int: DHORSE = 0..m;
array[HORSE] of int: beauty;
array[HORSE] of int: speed;

array[COURT,HORSE] of int: enjoy;

% We allow to assign Dummy horses and riders using dummy variable 0
array[HORSE] of var DCOURT: riders;
array[COURT] of var DHORSE: horses;


% As it isn't an exact matching we can't do the inverse global constraint,
% because both arrays have different size.
include "alldifferent_except_0.mzn";
constraint alldifferent_except_0(riders);
constraint alldifferent_except_0(horses);
constraint forall(i in COURT, j in HORSE)(horses[i] = j <-> riders[j] = i);

% Emperor enjoys the most
constraint forall(i in COURT_WOUT_EMP where horses[i] != dummy)(enjoy[emperor, horses[emperor]] > enjoy[i, horses[i]]);

% All members ride if there are available horses
constraint count(i in COURT)(horses[i] != 0) = min(n, m);

% Non-negative enjoy matches
constraint forall(i in riders where horses[i] != dummy)(enjoy[i, horses[i]] >= 0);

% Rank constraints
constraint forall(i, j in COURT)(
                   (rank[i] > rank[j] /\ horses[j] != dummy) -> (beauty[horses[i]] >= beauty[horses[j]] /\ horses[i] != dummy)
           );

% Objective and penalty for speed constraints
var int: penalty = 100 * count(i, j in HORSE)(
                              speed[i] > speed[j] /\ riders[i] != dummy /\
                              (riders[j] = dummy \/ (riders[i] != dummy /\ riders[j] != dummy /\ ability[riders[i]] < ability[riders[j]]))
                         );
             
var int: obj = sum(i in COURT where horses[i] != dummy)(enjoy[i, horses[i]]) - penalty;
                                      
solve maximize obj;

output ["horse = \(horses);" ++ "\n" ++ "obj = \(obj);"];