enum NEGOTIATOR;
NEGOTIATOR: dummy; 

int: l; % minimum party size
int: u; % maximum party size
int: m; % minimum joint ability

array[NEGOTIATOR] of int: honor;
array[NEGOTIATOR,NEGOTIATOR] of int: joint;

array[1..u] of var NEGOTIATOR: party;

constraint forall(i in 1..u-1)(party[i] >= party[i + 1] + (party[i] != dummy));

% constraint sum(i in 1..u)(party[i] != dummy) >= 1;
constraint forall(i in 1..l)(party[i] != dummy);

constraint sum(i, j in 1..u where i < j)(joint[party[i], party[j]]) >= m;

var int: obj = min(i in 1..u)(honor[party[i]]);
solve maximize min(i in 1..u)(honor[party[i]]);