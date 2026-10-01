% Preparing a banquet in the least time
enum COOK; % the set of cooks available
enum DISH; % the set of all dishes to prepare
int: no_tasks; % total number of tasks
set of int: TASK = 1..no_tasks;
array[DISH] of set of TASK: steps; % steps to making a dish
array[TASK, COOK] of int: time; % amount of time to complete task by cook

int: maxt = sum(array1d(time));
set of int: TIME = 0..maxt;
array[TASK] of var TIME:    start;    % start time for task
array[TASK] of var TIME:    duration; % duration time for task
array[TASK] of var TIME:    end;      % end time for task
array[TASK] of var COOK:    cook;     % cook for task
var TIME: obj;

% Calcualte duration and end arrays from start and time variables.
% Duration of zero means that is not feasible.
constraint forall(t in TASK)(duration[t] = time[t, cook[t]] /\ duration[t] != 0);
constraint forall(t in TASK)(end[t] = start[t] + duration[t]);

% Steps of the same dish must be ordered and can't overlap.
constraint forall(d in DISH, t1, t2 in steps[d] where t1 < t2)(
  end[t1] <= start[t2]);

% Steps from the same cook can't overlap (order is not important).
constraint forall(t1, t2 in TASK where t1 < t2 /\ cook[t1] = cook[t2])(
  end[t1] <= start[t2] \/ end[t2] <= start[t1]);

constraint obj = max(end);


% After some experiments these are the combination of search and restart configurations that seem to work better.
% It has sense as we choose random cooks to fit without any specific order and then we aim to have the minimum duration to end as soon as possible.
% Luby allows us to explore a lot more paths without going very deep, which gave better results than high values as 10, 100 or the default 250.

solve
:: seq_search([
  int_search(cook, smallest, indomain_random, complete),
  int_search(duration, first_fail, indomain_min, complete)
])
:: restart_luby(1)
minimize obj;

output
["s = ["]        ++ [show(start[t]) ++ if t != no_tasks then ", " else "" endif | t in TASK] ++
["];\nc = ["]    ++ [show(cook[t])  ++ if t != no_tasks then ", " else "" endif | t in TASK] ++
["];\nobj = " ++ show(obj) ++ ";"];