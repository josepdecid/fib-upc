function [root, tab] = recur(x0, eta)
% Receives the formula, initial point and eta threshhold.
% Calculates the recurrency with the formula from x0.
f = @(x) 5 - 5/(exp(1)^x);
xn = f(x0);
xprev = x0;

t = zeros(0, 4);

k = 1;
while abs(xn - xprev) >= eta
    t(k, :) = [k, xn, f(xn), xn - xprev];
    
    xprev = xn;
    xn = f(xprev);
    k = k + 1;
end

t(k, :) = [k, xn, f(xn), xn - xprev]; 

root = xn;
tab = array2table(t);
tab.Properties.VariableNames = {'n', 'xn', 'fxn', 'Dxn'};
end

