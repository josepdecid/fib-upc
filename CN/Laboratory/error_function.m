function [ ea, er, erp ] = error_function(x, y)
    ea = abs(x - y);
    er = ea / abs(x);
    erp = er * 100;
end