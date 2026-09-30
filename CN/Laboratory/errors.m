%% Example script errors
% Absoulute, relative and percent errors
format compact
x = input(' x value: '); % pi
y = input(' y value: '); % 22/7

ea = abs(x - y); disp(ea);
er = ea / abs(x); disp(er);
erp = er * 100; disp(erp);