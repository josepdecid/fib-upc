function [errAbs, errRel] = ex3(x, xTilde)
% Calculate absolute and relative error of x and xTilde

errAbs = x - xTilde;
errRel = errAbs / x;
end

