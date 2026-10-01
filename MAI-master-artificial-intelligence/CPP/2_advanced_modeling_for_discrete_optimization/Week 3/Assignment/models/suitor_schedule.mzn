% scheduling suitors
enum SUITOR;
SUITOR: LiuBei; % which suitor is LiuBei
int: n; % number of meetings
set of int: MEETING = 1..n;
array[MEETING] of SUITOR: suitor;

enum ROOM = { Red, Gold, Blue };
array[SUITOR,ROOM] of int: mintime;
array[SUITOR,ROOM] of int: maxtime;
constraint forall(s in SUITOR, r in ROOM)
                 (assert(mintime[s,r] >= 1 /\ maxtime[s,r] >= mintime[s,r],
                  "error in mintime/maxtime at [\(s),\(r)]\n"));

array[ROOM,ROOM] of int: move;
constraint forall(r in ROOM)(assert(move[r,r] = 0,"move[\(r),\(r)] != 0\n"));

int: ndays; % number of days
set of int: DAY = 1..ndays;
int: earliest; % time for earliest meeting start
int: latest;  % time for end of latest meeting

int: lessontime; % time for kung fu lesson;
int: minsep;     % minimum time between consecutive kung fu lessons

array[ROOM] of int: usedstart;  % time others use each room each day
array[ROOM] of int: useddur;    % durations of others use

enum STAGE = {A,B,C};
STAGE: stage;

set of int: TIME = 0..24*ndays;

array[MEETING] of var TIME: start;
array[MEETING] of var TIME: dur;    % duration in false schedule
array[MEETING] of var ROOM: room;
set of int: KUNGFU = 1..n;
array[KUNGFU] of var int: kungfu;  % start time for each lesson
   % unused lessons have start times after 24*ndays

%%%%%%%%%%%%%%
%% SOLUTION %%
%%%%%%%%%%%%%%

set of int: MEETING0 = 0..n;
array[MEETING] of var bool: has_kungfu;
array[KUNGFU] of var MEETING0: meeting_assigned;

% Avoid permutations of the result swapping same suitor order
constraint forall(m1, m2 in MEETING where suitor[m1] = suitor[m2] /\ m1 < m2)(start[m1] < start[m2]);

% There are no overlappings among meetings
include "disjunctive.mzn";
constraint disjunctive(start, dur);   

% All meetings should start after earliest time and finish before latest time every day
constraint forall(m in MEETING)(
  start[m] mod 24 >= earliest /\
  (start[m] + dur[m]) mod 24 <= latest /\
  (start[m] mod 24) + dur[m] < 24
);
 
% Any meeting should not disturb other usages of the rooms 
constraint forall(m in MEETING)(
  let { var int: start_other = usedstart[room[m]],
        var int: dur_other   = useddur  [room[m]]; } in
    (start[m] + dur[m]) mod 24 <= start_other \/ start_other + dur_other <= start[m] mod 24);

% There is enough time to move between rooms
constraint forall(m1, m2 in MEETING where start[m1] < start[m2])(start[m1] + dur[m1] + (stage in {B, C}) * move[room[m1], room[m2]] <= start[m2]);
  
% Every meeting must be longer than mintime and shorter than maxtime.
% If there is a kungfu lesson it should be longer than mintime + lessontime
constraint forall(m in MEETING)(
  dur[m] >= mintime[suitor[m], room[m]] + has_kungfu[m] * lessontime /\
  dur[m] <= maxtime[suitor[m], room[m]]
);

% Reduce range of kungfu lessons
% Max possible value is when all are unassigned considering min separation and lesson times.
constraint forall(k in KUNGFU) (kungfu[k] > 0 /\ kungfu[k] <= 24 * ndays + n * (minsep + lessontime));

% A and B stages ignore kungfu (> max time)                  
constraint if stage in {A, B}
           then forall(k in KUNGFU)(kungfu[k] > 24 * ndays /\ meeting_assigned[k] = 0) /\
                forall(m in MEETING)(has_kungfu[m] = false)
           endif;
           
constraint if stage = C
           then forall(m in MEETING)(has_kungfu[m] = exists(k in KUNGFU)(meeting_assigned[k] = m))
           endif;

% Kungfu lessons must align with the end of the meeting
% Kth meeting is assigned to the Mth meeting
constraint forall(k in KUNGFU where kungfu[k] <= 24 * ndays)(
  stage = C -> exists(m in MEETING)(
    meeting_assigned[k] = m /\
    kungfu[k] + lessontime = start[m] + dur[m]
  )
);

% Kungfu array is ordered
% There must be some spacing between kungfu lessons
constraint forall(k in 1..n-1)(kungfu[k + 1] - (kungfu[k] + lessontime) >= minsep);

var int: obj;
constraint obj = sum([100 | k in KUNGFU where kungfu[k] <= 24 * ndays])
               + sum(m in MEETING where suitor[m] = LiuBei)(dur[m] - has_kungfu[m] * lessontime);              

solve maximize obj;

output
["start = ["]      ++ [show_int(2, start[m]) ++ if m != n then ", " else "" endif | m in MEETING]  ++
["];\ndur  = ["]   ++ [show_int(2, dur[m]) ++  if m != n then ", " else "" endif | m in MEETING] ++
["];\nroom = ["]   ++ [show(room[m]) ++  if m != n then ", " else "" endif | m in MEETING] ++
["];\nkungfu = ["] ++ [show(kungfu[k]) ++  if k != n then ", " else "" endif | k in KUNGFU] ++
["];\nobj = "      ++ show(obj) ++ ";"];