int: T; % maximum time allowed;
set of int: TIME = 1..T;
set of int: TIME0 = 0..T;

int: E; % weight of elephant in STONES;
set of int: STONE = 0..E;

int: G; % number of guards
set of int: GUARD = 1..G;
array[GUARD] of STONE: easy;
array[GUARD] of STONE: hard;
array[GUARD] of TIME: tired;

GUARD: p; % maximum people on pier;
GUARD: b; % maximum people on boat;

set of int: ACT = -1..E; % -1 = goto bank, 0 = wait, > 0 carry stones
int: wait = 0;
int: to_bank = -1;
array[GUARD,TIME] of var ACT: act;        % action at time t
var TIME: end;                            % end time;

enum LOC = { Boat, Bank };
array[GUARD, TIME0] of var LOC: location;

% all guards start at the bank
constraint forall(g in GUARD)(location[g, 0] = Bank);

% if guard is carrying stones it should be in the bank
% if guard returns to the bank, he must be in the boat previously
constraint forall(t in TIME, g in GUARD)((act[g, t] > 0 -> (location[g, t - 1] = Bank /\ location[g, t] = Boat))
                                      /\ (act[g, t] = to_bank -> (location[g, t - 1] = Boat /\ location[g, t] = Bank))
                                      /\ (act[g, t] = wait -> (location[g, t] = location[g, t - 1])));
                                      
% all guards move in the same direction
constraint forall(t in TIME, g1 in GUARD, g2 in GUARD)(act[t, g1] * act[t, g2] >= 0);

% one guard can carry at most hard_g stones
constraint forall(t in TIME, g in GUARD)(act[g, t] <= hard[g]);
% if a guard carries more than easy_g stones, for the next tired_g steps it won't carry anything
constraint forall(t in TIME, g in GUARD)((act[g, t] > easy[g]) ->
                                         (forall(tp in t+1..t+1+tired[g])(tp <= T /\ act[g, tp] <= 0)));

% at the end there must be at least E stones moved
constraint sum(t in 1..end, g in GUARD)(act[g, t]) >= E;

% after end, they stand still.
constraint forall(t in end+1..T, g in GUARD)(act[g, t] = wait);

solve minimize end;