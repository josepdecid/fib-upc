% Beauty Trap
% Create the most magnificient feast 
enum DISH;
enum TASTE = {spicy, sour, salty, sweet, umame, bland};
enum TEMP = {hot, cold, warm};
%int: ndish;
%set of int: DISH = 1..ndish;
%set of int: TASTE = 1..6;
%int: spicy = 1; int: sour = 2; int: salty = 3; int: sweet = 4; int: umame = 5; int: bland = 6;
%set of int: TEMP = 1..3;
%int: hot = 1; int: cold = 2; int: warm = 3;


array[DISH] of TASTE: taste;
array[DISH] of TEMP: temp;
array[DISH] of bool: heavy;
array[DISH] of int: value;

int: len; % length of banquet
set of int: COURSE = 1..len;

array[COURSE] of var DISH: dish;

include "alldifferent.mzn";
constraint alldifferent(dish);

constraint taste[dish[1]] = salty;
constraint taste[dish[len]] = sweet;

constraint forall(d in 1..len-1)(taste[dish[d]] != taste[dish[d + 1]]);
constraint forall(d in 1..len-1)(taste[dish[d]] = spicy -> taste[dish[d + 1]] in { bland, sweet });
constraint forall(d in 1..len-1)(taste[dish[d]] = sour -> taste[dish[d + 1]] in { bland, umame });
constraint forall(d in 1..len-1)(taste[dish[d]] = sweet -> taste[dish[d + 1]] in { bland, salty, sour });

constraint forall(d in 1..len-1)(temp[dish[d]] = hot -> temp[dish[d + 1]] != cold);

constraint forall(d in 1..len-2)(heavy[dish[d]] /\ heavy[dish[d + 1]] -> not heavy[dish[d + 2]]);

var int: obj;
constraint obj = sum(d in dish)(value[d])
               + sum(d in 1..len-1)(taste[dish[d]] != taste[dish[d + 1]])
               + sum(d in 1..len-1)(temp[dish[d]] != temp[dish[d + 1]])
               + sum(d in 1..len-1)(heavy[dish[d]] != heavy[dish[d + 1]]);

solve maximize obj;