int: T; % maximum time allowed;
set of int: TIME = 1..T;
int: G; % number of guards
int: F; 
int: W;

array[TIME] of var -F..F: move_food;      % move food +ve bank to boat, -ve boat to bank
array[TIME] of var -W..W: move_water;     % move water +ve bank to boat, -ve boat to bank
var TIME: end;                            % end time;

set of int: TIME0 = 0..T;
array[TIME0] of var 0..F: fboat;
array[TIME0] of var 0..W: wboat;

enum POS = { Bank, Boat };
array[TIME0] of var POS: pos;

predicate move(var 0..F: f_here,  var 0..W: w_here) = 
               let { var 0..F: f_there = F - f_here,
                     var 0..W: w_there = W - w_here; } in
               (w_there = f_there /\ f_there > f_here /\ w_there > w_here);
               
constraint pos[0] = Bank;
constraint fboat[0] = 0;
constraint wboat[0] = 0;

constraint forall(t in TIME)(fboat[t] = move_food[t] + fboat[t - 1]);
constraint forall(t in TIME)(wboat[t] = move_water[t] + wboat[t - 1]);

constraint forall(t in TIME)(abs(move_food[t]) + abs(move_water[t]) <= G);

constraint forall(t in TIME)(move_food[t] * move_water[t] >= 0);

array[POS] of POS: opp = [Boat, Bank];
predicate elephant(var POS: now, var 0..F: f_here, var 0..W: w_here, var POS: next) =
                   next = [now, opp[now]][move(f_here, w_here) + 1] /\
                   (f_here = 0 <-> w_here = 0);
                   
constraint forall(t in TIME)
                   (let { var 0..F: f_here = [F - fboat[t - 1], fboat[t - 1]][pos[t - 1]],
                          var 0..W: w_here = [W - wboat[t - 1], wboat[t - 1]][pos[t - 1]]; } in
                   elephant(pos[t - 1], f_here, w_here, pos[t]));
                   
constraint forall(t in end..T)(move_water[t] = 0 /\ move_food[t] = 0);
constraint pos[end] = Boat /\ fboat[end] = 0 /\ wboat[end] = 0;

solve minimize end;