function [root, tab] = my_newton(f, df, d2f, a, b, eta)
% Receives the function, first and second derivatinve, interval and threshold eta.
% Calculates the equation root with the Newton-Raphson method.
if sign(f(a)) == sign(d2f(a))
    xprev = a;
else
    xprev = b;
end

t = zeros(0, 4);
xn = xprev - f(xprev)/df(xprev);

k = 1;
while max(abs(xn - xprev), abs(f(xn))) >= eta
   t(k, :) = [k, xn, f(xn), xn - xprev]; 
    
   xprev = xn;
   xn = xprev - f(xprev)/df(xprev);
   k = k + 1;
end

root = xn;
tab = array2table(t);
tab.Properties.VariableNames = {'n', 'xn', 'fxn', 'Dxn'};
end

