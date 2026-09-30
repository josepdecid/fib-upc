function [ root ] = my_bisec(f, a, b, tol, M)
% Bisection method
%   f: function, a: data, b: data, option f(a)*f(b) < 0,
%   epsilon: error level, M: iteration level
   
k = 0;
tolx = abs(b - a);
tolf = max(abs(f([a, b])));
era = max(tolx, tolf);

while (k < M && era > tol)
    x = (a + b)/2;
    disp([k, a, x, b, f(x), tolf, tolx])
    if sign(f(x)) == sign(f(b))
        b = x;
    else
        a = x;
    end
    
    k = k + 1;
    tolx = abs(b - a);
    tolf = max(abs(f([a, b])));
    era = max(tolx, tolf);
end

root = x;

end

