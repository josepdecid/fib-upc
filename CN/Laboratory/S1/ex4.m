function [d, t] = ex4(x, xTilde)
% Calculate correct decimal digits and correct significative digits

errAbs = x - xTilde;
errRel = errAbs / x;

d = floor(log10(0.5 / abs(errAbs)));
t = floor(log10(0.5 / abs(errRel)));
end

