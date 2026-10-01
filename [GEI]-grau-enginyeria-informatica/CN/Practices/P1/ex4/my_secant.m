function [root, tab] = my_secant(f, x0, x1, eta)
% Receives the function, two initial values and threshold eta.
% Calculates the equation root with the Secant method.
t = zeros(0, 4);
xn = x1 - f(x1) * (x1 - x0)/(f(x1) - f(x0));

k = 1;
while max(abs(xn - x1), abs(f(xn))) >= eta
    t(k, :) = [k, xn, f(xn), xn - x1];
    
    x0 = x1; x1 = xn;
    xn = x1 - f(x1) * (x1 - x0)/(f(x1) - f(x0));
    
    k = k + 1;
end

t(k, :) = [k, xn, f(xn), xn - x1];

root = xn;
tab = array2table(t);
tab.Properties.VariableNames = {'n', 'xn', 'fxn', 'Dxn'};
end

