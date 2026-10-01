int: n;
set of int: TASK = 1..n;
array[TASK] of int:  d;  % length of task

int: m;
set of int: PREC = 1..m;
array[PREC] of TASK:  pre;  % task pre[i] must finish before post[t] starts
array[PREC] of TASK:  post; % 

int: o; 
set of int: DISJ = 1..o;
array[DISJ] of set of TASK: disj; % sets of tasks which cant overlap in time

int: maxt = sum(t in TASK)(d[t]);

array[int] of int: s; % start time
array[TASK] of int: e = [ if i in index_set(s) then s[i] else 0 endif + d[i] | i in TASK]; 
int: makespan;

function bool: check(bool: b, string: s) = 
                     if b then true else trace_stdout("ERROR: " ++ s, false) endif; 

function bool: check_int(int: x, set of int: vals, string: name) =
               check(x in vals, "integer \(name) is not in values \(vals)\n");

function bool: check_int_array(array[int] of int: x, int: length, set of int: vals, string: name) =
               check(length(x) = length, "array \(name) is not of length \(length)\n") /\
               forall(i in index_set(x)) 
                     (check(x[i] in vals, "\(name)[\(i)] = \(x[i]) is not in values \(vals)\n"));  


output [ if
             check_int_array(s, n, 0..maxt, "s") /\
             forall(i in PREC)
                 (check(e[pre[i]] <= s[post[i]],
                        "precedence \(i) that task \(pre[i]) is before " ++
                        "task \(post[i]) doesnt hold\n")) /\
             forall(d in DISJ)
                   (forall(t1, t2 in disj[d] where t1 <t2)
                          (check(e[t1] <= s[t2] \/ e[t2] <= s[t1],
                                 "Disjoint tasks \(t1) and \(t2) overlap\n"))) /\
             check(makespan = max(e), "Given makespan = \(makespan) does not agree with calculated \(max(e))\n")
         then
             "CORRECT: all constraints hold\n"
         else
             "INCORRECT\n"
         endif ];


solve satisfy;
