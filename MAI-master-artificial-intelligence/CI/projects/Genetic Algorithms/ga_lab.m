%% Plot function
plotobjective(@rastriginsfcn,[-5 5; -5 5]);



%% Optimizer
optimtool('ga') 

%% From command line
[x fval exitflag] = ga(@rastriginsfcn, 2)
