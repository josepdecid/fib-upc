function [root, tab] = my_bisec(f, a, b, eta)
% Receives the equation, initial interval and threshold eta.
% Calculates the equation root with the bisection method.
n = ceil(log(abs(b - a)/eta)/log(2));
t = zeros(n, 6);

for k = 1:n
    alpha = (a + b)/2;
    tolx = abs((b - a)/2);
   
    t(k, :) = [k, a, b, alpha, f(alpha), tolx];
    
    if sign(f(a)) ~= sign(f(alpha))
        b = alpha;
    else
        a = alpha;
    end
end

root = alpha;
tab = array2table(t);
tab.Properties.VariableNames = {'n', 'an', 'bn', 'xn', 'fxn', 'err'};
end

