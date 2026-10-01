% assignment 2
% select a set of raiding warrior
enum WARRIOR;
WARRIOR: dummy; 
enum CLAN; % the clan they belong too

int: l; % minimum raid party size
int: u; % maximum raid party size
int: m; % limit of hatreds

array[WARRIOR] of int: strength;
array[WARRIOR] of CLAN: clan;    

array[CLAN,CLAN] of 0..1: hates;

% List of warriors that will participate in the raid 
array[1..u] of var WARRIOR: raid;
% Objective function to maximize
var int: raid_strength = sum(i in 1..u)(strength[raid[i]]);

% Ensure that there aren't multiple array representations for a single set
% Allow multiple dummy warriors in an array of, at most, u warriors.
constraint forall(i in 1..u-1)(raid[i] >= raid[i+1] + (raid[i] != dummy));
constraint sum(i in 1..l)(raid[i] != dummy) >= l;
                               
% There are at most m pairs of warriors which clans hate each other
constraint sum(i, j in 1..u where i < j)
              (hates[clan[raid[i]], clan[raid[j]]]) <= m;

solve maximize raid_strength;

output ["raid = {"]
    ++ [if fix(raid[i]) != dummy then show(raid[i]) ++ if i < u /\ fix(raid[i+1]) != dummy then ", " else "" endif else "" endif | i in 1..u ]
    ++ ["};\nobj = \(raid_strength)"];