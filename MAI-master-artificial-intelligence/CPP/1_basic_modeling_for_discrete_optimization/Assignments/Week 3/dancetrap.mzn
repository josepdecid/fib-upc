% Beauty Trap
% Perform the most seductive dance

enum LEGS = {spin, leap, waltz, curtsey, prep, stand};
enum ARMS = {beckon, out, up, wrapped, neutral};
enum FACE = {smile, wink, batt, think, glow, blank};

int: maxlen;
set of int: STEP = 1..maxlen;
array[LEGS] of int: maxlegs;
array[ARMS] of int: maxarms;
array[FACE] of int: maxface;
constraint assert(maxlegs[stand] >= maxlen, "maxlegs[stand] smaller than maxlen");
constraint assert(maxarms[neutral] >= maxlen, "maxarms[neutral] smaller than maxlen");
constraint assert(maxface[blank] >= maxlen, "maxface[blank] smaller than maxlen");
array[LEGS,ARMS] of int: dance_value;
array[ARMS,FACE] of int: entice_value;
constraint assert(dance_value[stand,neutral] = 0, "incorrect dance_value array");
constraint assert(entice_value[neutral,blank] = 0, "incorrect entice_value array");
int: boredom; % how bored each step make the viewer

var STEP: len;
array[STEP] of var LEGS: legs;
array[STEP] of var ARMS: arms;
array[STEP] of var FACE: face;

include "regular.mzn";
   
%% Flow constraints

constraint regular(legs, 8, 6, t_legs, 1, {1});
array[1..8, LEGS] of 0..8: t_legs =
  [| 2, 0, 4, 7, 8, 1
   | 0, 0, 0, 7, 8, 1
   | 2, 0, 4, 7, 8, 1
   | 2, 0, 5, 7, 8, 1
   | 2, 0, 6, 7, 8, 1
   | 2, 0, 0, 7, 8, 1
   | 2, 0, 4, 7, 0, 1
   | 2, 3, 4, 7, 8, 1 |];
% To simplify the automata, we extract the stand between waltz and curtsey as an external constraint
constraint forall(i in 1..len-1)(legs[i] = waltz -> forall(j in i+1..len)(legs[j] = curtsey -> exists(k in i+1..j-1)(legs[k] = stand)));

constraint regular(arms, 5, 5, t_arms, 1, {1});
array[1..5, ARMS] of 0..5: t_arms =
  [| 0, 3, 4, 5, 1
   | 0, 3, 4, 5, 1
   | 2, 0, 4, 0, 1
   | 2, 3, 0, 0, 1
   | 0, 3, 4, 0, 1 |];

constraint forall(i in 1..len-1)(face[i] != blank -> face[i] != face[i + 1]);
constraint forall(i in 1..len-1)(face[i] in {smile, batt} -> face[i + 1] != think);
   
% From len until the end everything is null movement
constraint forall(i in len+1..maxlen)(legs[i] = stand);
constraint forall(i in len+1..maxlen)(arms[i] = neutral);
constraint forall(i in len+1..maxlen)(face[i] = blank);

% Less than maximum allowed movements of each type
constraint forall(i in LEGS)(sum([1 | j in 1..len where legs[j] = i]) <= maxlegs[i]);
constraint forall(i in ARMS)(sum([1 | j in 1..len where arms[j] = i]) <= maxarms[i]);
constraint forall(i in FACE)(sum([1 | j in 1..len where face[j] = i]) <= maxface[i]);

% Combination constraints
constraint forall(i in 1..len)(dance_value[legs[i], arms[i]] != -1);
constraint forall(i in 1..len)(entice_value[arms[i], face[i]] != -1);

var int: calc_dance_value = sum(i in 1..len)(dance_value[legs[i], arms[i]]);
var int: calc_entice_value = sum(i in 1..len)(entice_value[arms[i], face[i]]);
var int: obj = calc_dance_value + calc_entice_value - (boredom * len);
               
solve maximize obj;

output ["len = \(len);\n", "legs = \(legs);\n", "arms = \(arms);\n", "face = \(face);\n", "obj = \(obj);"]